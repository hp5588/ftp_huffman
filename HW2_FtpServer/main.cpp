#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <bits/signum.h>
#include <signal.h>
#include <wait.h>
#include "src/tools/Command.h"
#include "src/Server.h"
#include <algorithm>
#include <sys/wait.h>
#include <cstdlib>


using namespace std;

#define DEFAULT_SERVER_IP "127.0.0.1"
#define DEFAULT_SERVER_PORT 8000


vector<int> pidList;


void help(vector<pair<string,string>> commandList);
void childDieHandle(int sig);


int main() {

    cout << "----B013012011 FTP Server----" << endl;
    vector<pair<string,string>> commandList = {
            {"run [server ip] [port]",  "open a new server with ip and port provided"},
            {"stop [pid]",              "stop a server by specifying its pid (status can tell)"},
            {"status",                  "the server which are running now"},
            {"quit",                    "end all servers and quit program"},
            {"help",                    "show this help"}
    };


    Command cmdManager;


    bool on = 1;
    while (on){
        /*default parameters*/
        Server server(DEFAULT_SERVER_IP,DEFAULT_SERVER_PORT);

        string cmd;
        cout << "server >" <<endl;
        getline(cin,cmd);


        /*deal with user command*/
        vector<string> cmds;
        cmdManager.extractCommand(cmd,cmds);

        signal(SIGCHLD,childDieHandle);



        if ( cmds.at(0).compare("run")==0){
            if (cmds.size()==1 || cmds.size()==3) {

                int pid = fork();
                if (pid < 0) {
                    cout << "fork failed" << endl;
                } else if (pid == 0) {
                    if (cmds.size() == 1) {
                        /*run server*/
                        server.run();
                    } else if (cmds.size() == 3) {
                        server.setIp(cmds.at(1));
                        server.setPort(stoi(cmds.at(2)));
                        server.run();
                    }
                    exit(0);

                } else {
                    pidList.push_back(pid);
                    continue;
                }
            }else{
                cout << "command parameter error" <<endl;
            }
        }else if (cmds.at(0).compare("stop") ==0 ){
            int pidUser = stoi(cmds.at(1));
            for (int pid : pidList){
                if (pid == pidUser){
                    kill(pid,SIGINT);

                    int status;
                    waitpid(pid,&status,0);

                    std::vector<int>::iterator p = std::find(pidList.begin(), pidList.end(), pid);
                    pidList.erase(p, p + 1);
                }
            }
        }else if (cmds.at(0).compare("status") ==0 ){
            cout << pidList.size() << " process running" <<endl;
            for (int pid :pidList){
                kill(pid,SIGTRAP);
            }
        }else if (cmds.at(0).compare("quit") ==0 ){
            for (int pid : pidList){
                kill(pid,SIGKILL);
            }
            cout << "server closing.....  goodbye~~~" <<endl;
            on = 0;
            return 0;
        }else if (cmds.at(0).compare("help") ==0 ){

            help(commandList);

            continue;
        }else{
            cout << "command not found" << endl;
        }

    }
    return 0;

}

void childDieHandle(int sig) {
/*    if (SIGCHLD == sig) {
        for (int pid : pidList) {
            int status;
            waitpid(pid, &status, WNOHANG);
            if (WIFSIGNALED(status)) {
                std::vector<int>::iterator p = std::find(pidList.begin(), pidList.end(), pid);
                pidList.erase(p, p + 1);
                cout << "pid " << pid << " die" << endl;
            }
//            cout << "status :" << status << endl;
            cout << pid << " status:" << status << endl;
        }
    }*/
}

void help(vector<pair<string,string>> commandList) {
    cout << "////////// help //////////" <<endl;

    uint8_t longestLength;

    for (int j = 0; j < commandList.size(); ++j) {
        if (commandList.at(j).first.length() > longestLength)
            longestLength = commandList.at(j).first.length();
    }
    for (int i = 0; i < commandList.size(); ++i) {
        cout << " " << setw(longestLength+2) << std::left <<setfill('-')<< commandList.at(i).first  << commandList.at(i).second << endl;
    }
    cout<<endl;

}