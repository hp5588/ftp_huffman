//
// Created by brian on 3/23/16.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include "FTPClient.h"
#include "FTP.h"
#include <arpa/inet.h>
#include <ostream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstring>
#include <ifaddrs.h>
#include <regex>
#include <fstream>


FTPClient::FTPClient(string ip, uint16_t port) {
    this->ip=ip;
    this->port=port;
}

int FTPClient::init() {
    /*open a tcp socket*/
    socketFD = socket(AF_INET,SOCK_STREAM,0);


    if (socketFD<0){
        return -1;
    }

//    cout << fcntl(socketFD,O_SYNC)<<endl;

    return 0;
}


int FTPClient::connectToServer() {
    this->init();
    if (socketFD<0)
        return -1;

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.data());
    address.sin_port = htons(port);

    int status = connect(socketFD, (struct sockaddr *)&address,sizeof(address));

    if(status<0)
        return -1;

    cout << "connection established"<<endl;

    return 0;
}

int FTPClient::disconnect() {
    if (close(socketFD)<0){
        return -1;
    }
    return 0;
}


int FTPClient::sendCmd(string cmd, string payload) {
    string fullCMD = cmd.append(" ").append(payload).append("\n");

//    int status = write (socketFD, "brian",strlen("brian"));
    int status = write (socketFD, fullCMD.data(), fullCMD.length());
    cout << "[Client]:" <<fullCMD <<endl;

    if (status<0){
        return -1;
    }
    return 0;
}

int FTPClient::readResponse(string &data, uint16_t length) {
    char buffer[length];
    int status;

    /*clean buffer*/
    memset(buffer,0,sizeof(buffer));
    status = read(socketFD, buffer,length);

    if (status<0){
        return -1;
    }
    data = string(buffer);

    cout << "[Server]:" << data << endl;
    return 0;
}

int FTPClient::checkResponse(string response) {
    uint64_t  position = response.find("2");
    uint64_t  msgPosistion = response.find(" ");
    if (position!=0){
        cout << "server message: "<< &response[++msgPosistion] <<endl;
        return -1;
    }
    return 0;
}

void FTPClient::setIP(string ip) {
    this->ip = ip;

}

void FTPClient::setPort(uint16_t port) {
    this->port = port;
}

int FTPClient::uploadFile(string fileName, string fromLocalIP) {
    /*variables*/
    string response;
    string filePath = fileName;
    string localIP(fromLocalIP);/*tell server where to connect*/


    /*set server to binary mode*/
    this->sendCmd(FTP_CMD_MODE_BIN,"");
    this->readResponse(response,100);

    /*generate random port to listen later*/
    srand (time(NULL));
    uint16_t randomPort = rand() % 100 + 2000; /*range from 2000-2100*/
    ifaddrs *addr;
    getifaddrs(&addr);

    /*TODO: implement auto ip detection*/
    /*get current local ip*/
//                char ipStrBuff[INET_ADDRSTRLEN];
//                while(addr){
//                    if (string(addr->ifa_name).find("en1")<0){
//                        /*do nothing*/
//                    } else {
//                        /*the interface we want*/
//                        sockaddr_in *ipv4Add = (sockaddr_in *) (addr->ifa_addr);
//                        inet_ntop(AF_INET, &ipv4Add->sin_addr, ipStrBuff, INET_ADDRSTRLEN);
//                        break;
//                    }
//                    addr++;
//                }
//                string localIP(ipStrBuff);



    /*open a socket for server to retrieve data*/
    int listeningSocketFD = socket(AF_INET,SOCK_STREAM,0);

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    if (setsockopt (listeningSocketFD, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0);

    if (setsockopt (listeningSocketFD, SOL_SOCKET, SO_SNDTIMEO, (char *)&timeout,
                    sizeof(timeout)) < 0);


    /*TODO: check if port and socket is available*/
    /*bind*/
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(randomPort);
    if (bind(listeningSocketFD,(struct sockaddr *)&address,sizeof(address))<0){
        cout << "bind failed" <<endl;
    }

    /*listen*/
    if (listen(listeningSocketFD,SOMAXCONN)<0){
        cout << "listen failed" <<endl;
    }

    /*print connection info*/
    cout << "Listening on: " << localIP << ":" << randomPort <<endl;


    /*address and random port string composing*/
    string ipAndPort;
    localIP = regex_replace(localIP,regex("[.]"),string(","));

    char buff[10];
    sprintf(buff,"%d,%d",(randomPort & 0xFF00) >> 8 ,randomPort&0x00FF);
    ipAndPort.append(localIP).append(",").append(buff);


    /*request server to transfer file using following client ip and port*/
    this->sendCmd(FTP_CMD_PORT,ipAndPort);
    this->readResponse(response,500);



    /*ready to accept remote server's connection and send data*/
    sockaddr remoteAddr;
    uint32_t addrLength = 4;/*ipv4->4 bytes*/

    cout << "waiting for server to connect..." << endl;

    int pid = fork();

    if (pid<0){
        cout << "fork fail" << endl;
    } else if(pid == 0){
        /*child process*/
        usleep(1000000);
        this->sendCmd(FTP_CMD_STOR,filePath);
        if(this->readResponse(response,500)<0){
            return -1;
        }
        exit(0);
    } else{

        /*tell server the file name path*/
        int dataSocketFD = accept(listeningSocketFD,&remoteAddr,&addrLength);
        if (dataSocketFD<0){
            cout << "accept failed" << endl;
            cout << "errno: " <<errno <<endl;
            return -1;
        }
        cout << "connection accepted" <<endl;

        wait(pid);

        cout << "start to transfer" << endl;

        /*read file and send*/
        char buffer[100];
        memset(buffer,0,sizeof(buffer));


        ifstream file;
        file.open(filePath,std::ios::binary);
        if(file.fail()){
            cout << "fail to open file" << endl;
            return -1;
        }

        /*print SHA1*/
        cout << "file SHA1: "<< endl;
        system((string("shasum ").append(filePath)).c_str());

        cout << "data transferring...."<<endl;
        while (!file.eof()){
            file.read(buffer, sizeof(buffer));
            write(dataSocketFD ,buffer, file.gcount());
            memset(buffer,0,sizeof(buffer));
        }

        /*clear eof and fail flag*/
        file.clear();

        cout << "closing socket" <<endl;
        close(dataSocketFD);

        /*read the response from server*/
        this->readResponse(response,500);

        cout << "transfer finished" << endl;


    }
    return 0;
}

bool FTPClient::socketIsConnected(int socketFD) {
    int error_code = this->getErrorCode(socketFD);
    cout << "socket error code "<<error_code <<endl;
    if (error_code==EPIPE){
        cout << "socket is broken" <<endl;
        return false;
    }
    return true;
}


int FTPClient::getErrorCode(int socketFD) {
    int error_code;
    socklen_t error_code_size = sizeof(error_code);
    getsockopt(socketFD, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);

//    cout << "error_code" << error_code;
    return error_code;

}






