//
// Created by brian on 3/25/16.
//

#include <iostream>
#include <regex>
#include "Command.h"

int Command::extractCommand(string fullString, vector<string> &commands) {
    if (fullString.length()>0) {
        while (1) {
            int pos = (int) fullString.find(" ");
            if (pos < 0) {
                /*push the last command*/
                commands.push_back(string(&fullString[0],fullString.length()));
                break;
            }
            /*push a command back*/
            string temp = string(&fullString[0], (&fullString[pos]) - (&fullString[0]));
            commands.push_back(temp);

            /*cut the read part*/
            fullString = string(&fullString[pos]+1);



        }
    }


//    for (int i = 0; i < cmd.length(); ++i) {
//        if (cmd[i] == ' '){
//            pArray[++pCount] = (&cmd[i])+1;
//        }
//    }

    return 0;
}

int Command::commadLookUp(string searchCommand, vector<string> commandList) {
    for (int i = 0; i < commandList.size(); ++i) {
        if (commandList.at(i).compare(searchCommand)==0){
            return i;
        }
    }
    return -1;
}

int Command::extractFtpResponse(string fullString, vector<string> &commands) {
    int pos = (int) fullString.find(" ");
    uint32_t endPos = (uint32_t) (fullString.length() - 1);
    commands.push_back(string(&fullString[0],&fullString[pos-1]));
    int statusCode = stoi(commands.at(0));
    if (statusCode<1){
        cout<< "not an ftp response" << endl;
        return -1;
    }

    commands.push_back(string(&fullString[pos++],&fullString[endPos-1]));
    return statusCode;
}

int Command::extractFtpRequest(string fullString, vector<string> &commands) {

    extractCommand(fullString,commands);

    /*clean the last command*/
    string cmd = commands.at(commands.size()-1);
    cmd = regex_replace(cmd,regex("[\n]"),string(""));
    commands.pop_back();
    commands.push_back(cmd);



    return 0;
}







