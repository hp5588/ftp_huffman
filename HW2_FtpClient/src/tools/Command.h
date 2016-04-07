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


    int extractCommand(string fullString, vector<string> &commands);

};


#endif //FTPCLIENT_COMMAND_H
