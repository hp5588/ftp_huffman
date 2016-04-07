#include <iostream>
#include <string.h>
#include "src/FTPClient.h"
#include "src/FTP.h"
#include "src/tools/Command.h"
#include "src/huffman/Huffman.h"
#include <unistd.h>
#include <sys/socket.h>
#include <cinttypes>
#include <fcntl.h>
#include <algorithm>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <regex>
#include <fstream>

//#define DEFAULT_LOCAL_IP "192.168.11.4"
//#define DEFAULT_LOCAL_IP "192.168.1.22"
#define DEFAULT_LOCAL_IP "127.0.0.1"
//#define DEFAULT_IP "192.168.1.200"
//#define DEFAULT_IP "192.168.1.102"
#define DEFAULT_IP "127.0.0.1"
//#define DEFAULT_IP "192.168.11.3"
//#define DEFAULT_IP "ks-machining.com"

#define DEFAULT_FILE_PATH "file.txt"

#define DEFAULT_PORT 8000
#define DEFAULT_LOCAL_PORT 2030
//#define DEFAULT_USER "print"
#define DEFAULT_PASSWORD "99798"
#define DEFAULT_USER "brian"
//#define DEFAULT_PASSWORD "99798"

using namespace std;


int findStringInArray(char *array[],uint8_t length, string usrCommand){
    for (int i = 0; i < length; ++i) {
        if (strstr (array[i], usrCommand.data()) != 0){
            return i;
        }
    }
    return -1;
}

int main() {

    /*default*/
    FTPClient client(DEFAULT_IP, DEFAULT_PORT);
//    FTPClient client("140.117.164.52", 21);
//    FTPClient client("127.0.0.1", 9999);
    if (client.init()<0){
        cout << "socket initial error"<< endl;
        return 0;
    }


    cout << "B013012011 FTP FTPClient" << endl;

    char *cmdList[] = {
            "quit",
            "connect",
            "disconnect",
            "login",
            "upload",
            "encode",
            "decode"

    };


    string ip = DEFAULT_IP;
    string port = string(DEFAULT_IP);

    bool on = 1;
    while (on){
        cout<< "ftp>" << endl;
        string cmd;
        getline(cin,cmd);

        Command command;
        vector<string> cmds;
        command.extractCommand(cmd,cmds);


//        cout << cmds <<endl;


        int function = findStringInArray(cmdList,sizeof(cmdList)/sizeof(*cmdList),cmds.at(0));

        switch (function){
            case 0:{
                on = 0;
                break;
            }

            case 1:{
//                get user set ip and port
                if (cmds.size()==3){
//                    user give two parameter
//                    set ip and port
                    ip = cmds.at(1);
                    port = cmds.at(2);

                    /*resert ip and port*/
                    client.setIP(ip);
                    const char *start = port.c_str();
                    char *end;
                    uint16_t port = strtoimax(start,&end,0);
                    client.setPort(port);

                    /*TODO: disconnect from server*/

                } else if (cmds.size()==1){
                    /*no extra command then use default value*/
                    /*value already set in the initial condition*/

                } else{
                    /*error command*/
                    cout << "parameter error" <<endl;
                    break;
                }

                /*connect to FTP server*/
                if (client.connectToServer()<0){
                    cout << "server connect fail" << endl;
                    break;
                }

                string response;

                client.readResponse(response,500);

                client.sendCmd(FTP_CMD_USER, DEFAULT_USER);
                client.readResponse(response,500);

                client.sendCmd(FTP_CMD_PASS, DEFAULT_PASSWORD);
                client.readResponse(response,500);

                client.checkResponse(response)<0;

                break;
            }
            case 2:{
                /*disconnect*/
                if(client.disconnect()<0){
                    cout << "socket close fail" <<endl;
                }
                break;
            }

            case 3:{
                /*login*/

                break;
            }

            case 4:{
                string filePath = DEFAULT_FILE_PATH;
                string localIP = DEFAULT_IP;



                if (cmds.size()== 2){
                    /*file appended*/
                    filePath = cmds.at(1);
                }
                string encFilePath = filePath + ".enc";
                string treeFilePath = filePath+ ".tree";

                /*encoded*/
                Huffman codex(filePath,encFilePath,treeFilePath);
                codex.encode();

                system(string("shasum "+ filePath).c_str());

                client.uploadFile(encFilePath, localIP);
                client.uploadFile(treeFilePath, localIP);

                /*tell server to decode file*/
                client.sendCmd(FTP_CMD_DECODE,filePath);



                break;
            }
            case 5:{
                Huffman huffman(DEFAULT_FILE_PATH,"output.enc","tree.txt");
                huffman.encode();
                break;
            }

            case 6:{
                Huffman huffman("output.enc","decoded.txt","tree.txt");
                huffman.decode();
                break;
            }

            default:{
                cout<<"Command not found"<<endl;

                break;
            }
        }
//        cmdMap.find(cmd);

//        switch (cmd){
//            case "quit":{
//
//            }
//        }


    }

    return 0;
}


