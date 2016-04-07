//
// Created by brian on 2016/3/27.
//

#ifndef HW2_FTPSERVER_SERVER_H
#define HW2_FTPSERVER_SERVER_H

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <list>
#include "FTP.h"

using namespace std;

struct ThreadData{
    int socketFD;

};


class Server {
public:
    Server(string serverIP, uint16_t portToListen);

    /*setter*/
    void setIp(string ip);
    void setPort(uint16_t port);


    bool run();
private:
    string welcomeMessage = "server written by Brian Kao :D\n";

    vector<string> ftpCommandList = {
            FTP_CMD_MODE_BIN,
            FTP_CMD_PORT,
            FTP_CMD_STOR,
            FTP_CMD_QUIT,
            FTP_CMD_USER,
            FTP_CMD_PASS,/*5*/
            FTP_CMD_DECODE
    };

    /*socket info*/
    string ip;
    uint16_t port;

    /*socket file descriptor*/
    int socketFD = -1;

    /*data transfer ip and port*/
    string clientIP ;
    uint16_t clientPort = -1;


    bool init();



    /*handler*/
    void handlerThread(ThreadData parameter);
    int readRequest(int socketPD, string &request);
    int writeResponse(int socketPD, string response);
    int clientHandler(int socketFD);


    /*tools*/
    bool socketIsConnected(int socketFD);
    string composeResponse(int statusCode, string response);
    int extractIpAndPortFromFtpString(string addrPort, string &ip, uint16_t &port);
    int getErrorCode(int socketFD);
    void hash(string filePath);





};


#endif //HW2_FTPSERVER_SERVER_H
