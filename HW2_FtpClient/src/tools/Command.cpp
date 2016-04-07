//
// Created by brian on 3/25/16.
//

#include <iostream>
#include "Command.h"

int Command::extractCommand(string fullString, vector<string> &commands) {
    if (fullString.length()>0) {
        while (1) {
            int pos = (int) fullString.find(" ");
            if (pos < 0) {
                /*push the last command*/
                commands.push_back(string(&fullString[0]));
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

