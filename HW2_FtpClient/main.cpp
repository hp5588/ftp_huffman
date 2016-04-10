#include <iostream>
#include <string.h>
#include "src/FTPClient.h"
#include "src/FTP.h"
#include "src/tools/Command.h"
#include <Huffman.h>
#include <unistd.h>
#include <sys/socket.h>
#include <cinttypes>
#include <fcntl.h>
#include <algorithm>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <regex>
#include <fstream>
#include <iomanip>


#define DEFAULT_IP "127.0.0.1"


#define DEFAULT_FILE_PATH "file.txt"

#define DEFAULT_PORT 8000


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


    cout << "----B013012011 FTP Client----" << endl;

    vector<pair<string,string>> commandList = {
            {"connect [server ip] [port]",  "connect to server with specified ip and port"},
            {"encode [file path]",          "encode a file (file,file.enc,file.tree)"},
            {"decode [file path]",          "decode a file (file,file.enc,file.tree)"},
            {"login [user] [password]",     "login into server using user and password"},
            {"quit",                        "end this client"},
            {"help",                        "show this help"}

    };




    string ip = DEFAULT_IP;
    string port = string(DEFAULT_IP);

    bool on = 1;
    while (on){
        cout<< "client >";
        string cmdLine;
        getline(cin,cmdLine);

        Command command;
        vector<string> cmds;
        command.extractCommand(cmdLine,cmds);




//        int function = findStringInArray(cmdList,sizeof(cmdList)/sizeof(*cmdList),cmds.at(0));

        string cmd = cmds.at(0);
        if (cmd.compare("quit")==0){
            on = 0;
        } else if(cmd.compare("connect")==0){
            /*connect*/

            if (client.disconnect()<0){
                continue;
            }

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



                string response;
                client.readResponse(response,500);

            } else if (cmds.size()==1){

                /*no extra command then use default value*/
                /*value already set in the initial condition*/

            } else{
                /*error command*/
                cout << "parameter error" <<endl;
                continue;
            }

            /*connect to FTP server*/
            if (client.connectToServer()<0){
                cout << "server connect fail" << endl;
                continue;
            }


        }else if(cmd.compare("login")==0){
            /*login*/

            if (cmds.size()!=3){
                cout << "parameters either missing or too long" <<endl;
                continue;
            }

            string user = cmds.at(1);
            string password = cmds.at(2);

            string response;

            client.sendCmd(FTP_CMD_USER, user);
            client.readResponse(response,500);

            client.sendCmd(FTP_CMD_PASS, password);
            client.readResponse(response,500);

        }else if(cmd.compare("upload")==0){
            string filePath = DEFAULT_FILE_PATH;
            string localIP = DEFAULT_IP;

            if (cmds.size()== 2){
                /*file appended*/
                filePath = cmds.at(1);
            }

            string encFilePath = filePath + ".enc";
            string treeFilePath = filePath+ ".tree";

            system(string("shasum "+ filePath).c_str());

            /*encoded*/
            Huffman codex(filePath,encFilePath,treeFilePath);
            codex.encode();

            /*upload tree and encoded file*/
            client.uploadFile(encFilePath, localIP);
            client.uploadFile(treeFilePath, localIP);

            /*tell server to decode file*/
            client.sendCmd(FTP_CMD_DECODE,filePath);

        }else if(cmd.compare("encode")==0){

            if (cmds.size()!=2){
                cout << "parameters either missing or too long" <<endl;
                continue;
            }

            string path =cmds.at(1);

            Huffman huffman(path,
                            path + ".enc",
                            path + "tree");
            huffman.encode();

        }else if(cmd.compare("decode")==0){
            if (cmds.size()!=2){
                cout << "parameters either missing or too long" <<endl;
                continue;
            }
            string path =cmds.at(1);

            Huffman huffman(path + ".enc",
                            path,
                            path + ".tree");

            huffman.decode();

        }else if(cmd.compare("help")==0){
            cout << "////////// help //////////" <<endl;
            uint8_t longestLength = 0;
            for (int j = 0; j < commandList.size(); ++j) {
                if (commandList.at(j).first.length()>longestLength)
                    longestLength = commandList.at(j).first.length();
            }
            for (int i = 0; i < commandList.size(); ++i) {
                cout << " " << setw(longestLength+2) << std::left <<setfill('-')<< commandList.at(i).first  << commandList.at(i).second << endl;
            }

        }else{
            cout << "command not found" <<endl;
        }


    }

    return 0;
}


