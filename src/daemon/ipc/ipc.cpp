#include <windows.h>
#include <string>
#include <iostream>
#include "ipc.h"
#include "../queue/queue.h"
#include "../paste/paste.h"

#define PIPE_NAME L"\\\\.\\pipe\\CopyLine"
#define BUFFER_SIZE 512

extern bool isActive();
void onToggle();

std::string handleCommand(const std::string& cmd){
    if(cmd == "toggle"){
        onToggle();
        return isActive ? "CopyLine: ON" : "CopyLine: OFF";
    }

    if(cmd == "queue clear"){
        clearQueue();
        return "Queue Cleared";
    }

    if(cmd == "queue show"){
        auto q = getQueue();
        if(q.empty()) return "Queue is Empty";

        std::string result = "";
        int i = 1;
        for(const std::string& s:q){
            result += "["+ std::to_string(i++) + "]" + s + "\n";
        }
        return result;
    }

    if(cmd == "set paste style newline"){
        return "Paste Style Set To NewLine";
    }

    if(cmd == "set paste style sequential"){
        return "Paste Style Set To Sequential";
    }

    return "Unkown Command";
}

void startPipeServer(){
    while(true){
        HANDLE hPipe = CreateNamedPipeW(
            PIPE_NAME,
            PIPE_ACCESS_DUPLEX,
            PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            1,BUFFER_SIZE,BUFFER_SIZE,0,NULL
        );

        if(hPipe == INVALID_HANDLE_VALUE) return;

        ConnectNamedPipe(hPipe,NULL);

        char buffer[BUFFER_SIZE];
        DWORD bytesRead;
        if(ReadFile(hPipe,buffer,BUFFER_SIZE - 1,&bytesRead,NULL)){
            buffer[bytesRead] = '\0';
            std::string cmd(buffer);

            std::string response = handleCommand(cmd);
            DWORD bytesWritten;
            WriteFile(hPipe,response.c_str(),response.size(),&bytesWritten,NULL);
        }

        DisconnectNamedPipe(hPipe);
        CloseHandle(hPipe);
    }
}