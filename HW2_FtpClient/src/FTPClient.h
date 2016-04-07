//
// Created by brian on 3/23/16.
//

#ifndef FTPCLIENT_CLIENT_H
#define FTPCLIENT_CLIENT_H

#include <string>

using namespace std;

struct Server{
    uint16_t status;
};

class FTPClient {
private:


    /*socket variables*/
    int socketFD =-1;
    string ip;
    uint16_t port;

    /*server info*/
    Server server;


public:

    FTPClient(string ip, uint16_t port);
    int init();
    int connectToServer();
    int disconnect();
    int uploadFile(string fileName, string fromLocalIP);

    /*setter*/
    void setIP(string ip);
    void setPort(uint16_t port);


    int sendCmd(string cmd, string payload);
    int readResponse(string &data, uint16_t length);

    int checkResponse(string response);
private:
};

#endif //FTPCLIENT_CLIENT_H
