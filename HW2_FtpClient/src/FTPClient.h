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

    /*active FTP*/

    FTPClient(string ip, uint16_t port);
    int init();
    int connectToServer();
    int disconnect();
    int uploadFile(string fileName, string fromLocalIP);/*port is by random*/

    /*setter*/
    void setIP(string ip);
    void setPort(uint16_t port);

    /*getter*/
    int getSocketFD() const {
        return socketFD;
    }

    /*tools*/
    int sendCmd(string cmd, string payload);
    int readResponse(string &data, uint16_t length);

    int getErrorCode(int socketFD);
    bool socketIsConnected(int socketFD);


    int checkResponse(string response);
};

#endif //FTPCLIENT_CLIENT_H
