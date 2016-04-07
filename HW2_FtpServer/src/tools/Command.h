//
// Created by brian on 3/25/16.
//

#ifndef FTPCLIENT_COMMAND_H
#define FTPCLIENT_COMMAND_H
#include <vector>
#include <string>

using namespace std;

class Command {


public:
    /*manager*/




    /*tools*/
    int extractCommand(string fullString, vector<string> &commands);
    int extractFtpRequest(string fullString, vector<string> &commands);
    int extractFtpResponse(string fullString, vector<string> &commands);
    int commadLookUp(string searchCommand, vector<string> commandList);


private:
    int currentCmdIndex = -1;
};


#endif //FTPCLIENT_COMMAND_H
