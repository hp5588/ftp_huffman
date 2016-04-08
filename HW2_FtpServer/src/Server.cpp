//
// Created by brian on 2016/3/27.
//

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <regex>
#include <thread>
#include <fstream>
#include "Server.h"
#include "tools/Command.h"
#include <Huffman.h>

int status = 1;
string Address;
uint16_t Port;
//bool running=1;
vector<int> socketVector;

void signalHandle(int sig){
    switch (sig){
        case SIGTRAP:{
            cout << "pid:"<< getpid() <<"  "+ Address +":" + to_string(Port) << endl;
            break;
        }
        case SIGINT:{
            status = -1;
            for(int socket : socketVector){
                close(socket);
                cout << "socket: " << socket << " will be closed" << endl;
            }
            exit(0);

//            socketVector.clear();
//            cout << "pid:"<< getpid() <<"  "+ Address +":" + to_string(Port) <<" will be CLOSED now" << endl;
//            running = 0;
            break;

        }
        case SIGKILL:{
            cout << "kill signal received" <<endl;

            break;
        }
    }
//    cout << "signal receive" << sig <<endl;

}

/*use default port 21 when 0 given*/
Server::Server(string serverIP, uint16_t portToListen) {
    this->ip = serverIP;
    if (portToListen==0){
        this->port = 21;
    }else {
        this->port = portToListen;
    }

//    this->init();
}

bool Server::run() {

    this->init();
    /*interrupts handle*/
    signal(SIGTRAP,signalHandle);
    signal(SIGINT,signalHandle);
    signal(SIGKILL,signalHandle);


    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ip.c_str());
    address.sin_port = htons(port);

    /*bind*/
    if (bind(socketFD,(struct sockaddr *)&address,sizeof(address))<0){
        cout << "bind failed" <<endl;
        return -1;
    }

    /*listen*/
    if (listen(socketFD,SOMAXCONN)<0){
        cout << "listen failed" <<endl;
        return -1;
    }

    /*print connection info*/
    cout << "Listening on: " << ip.c_str() << ":" << port <<endl;

    socketVector.push_back(socketFD);


    /*accept*/
    bool run =1;

    Address = this->ip;
    Port = this->port;


    while (status>0 ) {
        /*accept connection */
        sockaddr clientAddr;
        socklen_t addrLenght = 4;
        int acceptedPD = accept(socketFD, &clientAddr, &addrLenght);

        socketVector.push_back(acceptedPD);

        if (acceptedPD < 0) {
            cout << "accept fail" << endl;
            cout << "socket error num: " << errno << endl;
            continue;
        }
        cout << "new client connected" <<endl;

        /*send hello message*/
//        cout << "send welcome message" <<endl;
        this->writeResponse(acceptedPD,welcomeMessage);

        /*while loop*/
        ThreadData threadData;
        threadData.socketFD = acceptedPD;

        this->handlerThread(threadData);


        /*remove after client disconnect*/
        close(acceptedPD);
        socketVector.erase(find(socketVector.begin(),socketVector.end(),acceptedPD));

        cout << "waiting for new client..." <<endl;

    }
    cout << "server is down" << endl;





    return false;
}

bool Server::init() {
    socketFD = socket(AF_INET,SOCK_STREAM,0);
    return false;
}

void Server::handlerThread(ThreadData parameter) {
    while (1){
        int status = Server::clientHandler(parameter.socketFD);
        if ( status == 10||status == -1){
            cout << "connection ended with status " <<status << endl;
            return;
        }
    }
}

int Server::readRequest(int socketPD, string &request) {
    if (socketPD<0){
        cout << "socket error" << endl;
        cout << "errno: " << errno <<endl;
    }

    char buffer[200];
    memset(buffer,0,sizeof(buffer));
    int length = read(socketPD,buffer,sizeof(buffer));
    if (length < 1){
        cout << "request read fail length " << length <<endl;
        cout << "errno: " << errno <<endl;
        return -1;
    }
    request = string(buffer);
    cout << "[Client]: "<< request <<endl;
    return length;
}

int Server::writeResponse(int socketPD, string response) {
    if (socketPD<0){
        cout << "socket error" << endl;
        cout << "errno: " << errno <<endl;
    }
    int length = write(socketPD,response.c_str(),response.length());
    if (length < 1){
        cout << "response write fail with length " << length <<endl;
        return -1;
    }

    cout << "[Server]: "<< response <<endl;

    return length;
}

/*return -1 when client request to say quit*/
int Server::clientHandler(int socketFD) {
    Command command;

    string request;

    /*read request*/
    if ( this->readRequest(socketFD,request) < 0){
        this->getErrorCode(socketFD);
        return -1;
    }

    /*handle request*/
    vector<string> clientCommand;
    command.extractFtpRequest(request, clientCommand);
    int index = command.commadLookUp(clientCommand.at(0),ftpCommandList);

//    cout << "[debug]" <<clientCommand.at(0) <<"(" << clientCommand.at(0).length() <<")"<<endl;

    switch (index){
        case 0:{
            /*FTP_CMD_MODE_BIN*/
            /*TODO currently all in binary mode*/
            this->writeResponse(socketFD,this->composeResponse(202,"all in binary"));
            break;
        }
        case 1:{
            /*FTP_CMD_PORT*/
            string clientAddr;
            uint16_t clientPort;
            this->extractIpAndPortFromFtpString(clientCommand.at(1),clientAddr,clientPort);
            if (port >0 || clientAddr.length()>0){
                this->clientPort = clientPort;
                this->clientIP = clientAddr;
                /*TODO debug use*/
//                cout << "server set client: " << clientAddr<<":" << clientPort <<endl;
            } else{
                /*send error message to client*/
                return -1;
            }
            this->writeResponse(socketFD,this->composeResponse(202,"port set"));
            break;
        }
        case 2:{
            /*FTP_CMD_STOR*/
            /*get this file name to write*/
            string fileName  = clientCommand.at(1);

            /*check if ip and port are set*/
            if (this->clientIP.length()>0&&this->port>0){
                /*open socket*/
                int newDataSocketFD = socket(AF_INET,SOCK_STREAM,0);

                /*open file to write*/ /*binary*/
                ofstream file;
                file.open(fileName,ios::binary);
                if (!file.is_open()) {
                    cout << "file open error" << endl;
                    return -1;
                }

                /*tell client that i am ready for file transfer*/
                string message  = string("ready for file: ").append(fileName).append(" to transfer");
                this->writeResponse(socketFD,this->composeResponse(200,message));

                /*connect*/
                sockaddr_in address;
                address.sin_family = AF_INET;
                address.sin_addr.s_addr = inet_addr(clientIP.data());
                address.sin_port = htons(clientPort);
                int status = connect(newDataSocketFD, (struct sockaddr *)&address,sizeof(address));
                if (status<0){
                    cout << "connect failed" <<endl;
                    return -1;
                }
//                cout << "connected to client starting to receive data" <<endl;

                /*write the file*/
                char buffer[100];
                memset(buffer,0,sizeof(buffer));
                while (this->socketIsConnected(newDataSocketFD)){
                    int numRead = read(newDataSocketFD,buffer,sizeof(buffer));
                    if (numRead>0)
                        file.write(buffer,numRead);
                    else
                        break;

                    memset(buffer,0,sizeof(buffer));
                }

                /*close file*/
                file.close();

                /*gernate hash to verify*/
                system(string("shasum ").append(fileName).c_str());

                /*close data socket*/
                close(newDataSocketFD);

                /*tell client we have finish transfer*/
                this->writeResponse(socketFD,"data transfer complete :)");


            } else{
                /*tell client that port is not set yet*/
                return -1;

            }

            break;}
        case 3:{
            /*FTP_CMD_QUIT*/
            /*say goodbye*/
            this->writeResponse(socketFD,this->composeResponse(200,"goodbye asshole"));
            /*close the socket*/
            close(socketFD);
            return 10;

            break;
        }
        case 4:{
            /*FTP_CMD_USER*/
            /*allow anyway*/
            this->writeResponse(socketFD,this->composeResponse(331,"require password (all pass)"));
            break;
        }
        case 5:{
            /*FTP_CMD_PASS*/
            /*allow anyway*/
            this->writeResponse(socketFD,this->composeResponse(202,"ohh u are now inside :D"));
            break;

        }
        case 6:{
            /*FTP_CMD_DECODE*/
            string filePath = clientCommand.at(1);
            string encPath = filePath + ".enc";
            string treePath = filePath + ".tree";

            Huffman codex(encPath,filePath,treePath);
            codex.decode();

            /*print shasum*/
            this->hash(filePath);

            cout << "decode complete" <<endl;


            break;
        }
        default:{
            this->writeResponse(socketFD,this->composeResponse(500,"ich verstehe nicht!!!!"));
            break;
        }

    }

    return 0;
}

int Server::extractIpAndPortFromFtpString(string addrPort, string &ip, uint16_t &port) {
    string temp = regex_replace(addrPort,regex("[,]"),string("."));
    uint8_t count=0;
    uint16_t endIndex = (uint16_t) (temp.length() );
    for (int i = 0; i < temp.length(); ++i) {
        if(temp[i]=='.'){
            count++;
            if (count == 4){
                ip = string(&temp[0],&temp[i]);
                string portString = string(&temp[i+1], &temp[endIndex]);
                portString = regex_replace(portString,regex("[/.]"),string(" "));

                vector<string> ports;
                Command command;
                command.extractCommand(portString,ports);

//                cout << "[debug]" << portString << endl;
//                cout << "[debug]" << ports.at(0) << ports.at(1) <<endl;
                uint8_t portH = (uint8_t) stoi(ports.at(0));
                uint8_t portL = (uint8_t) stoi(ports.at(1));
                port = portH << 8 | portL;

            }
        }
    }
    return 0;
}

string Server::composeResponse(int statusCode, string response){
    return string(to_string(statusCode)).append(" ").append(response);

}

bool Server::socketIsConnected(int socketFD) {
    int error_code = this->getErrorCode(socketFD);
    if (error_code==EPIPE){
        cout << "socket is broken" <<endl;
        return false;
    }
    return true;
}

void Server::setIp(string ip) {
    this->ip = ip;

}

void Server::setPort(uint16_t port) {
    this->port = port;

}

int Server::getErrorCode(int socketFD) {
    int error_code;
    socklen_t error_code_size = sizeof(error_code);
    getsockopt(socketFD, SOL_SOCKET, SO_ERROR, &error_code, &error_code_size);

//    cout << "error_code" << error_code;
    return error_code;

}

void Server::hash(string filePath) {
    string cmd  = "shasum "+filePath;
    system(cmd.c_str());

}



























