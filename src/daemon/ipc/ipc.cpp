#include <windows.h>
#include <string>
#include <iostream>
#include <sstream>
#include "ipc.h"
#include "../queue/queue.h"
#include "../paste/paste.h"
#include "../config/config.h"
#include "../core/core.h"

#define PIPE_NAME L"\\\\.\\pipe\\CopyLine"
#define BUFFER_SIZE 512

extern Config appConfig;
extern bool isActive;
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
        currentPasteStyle = NEWLINE;
        appConfig.pasteStyle = "newline";
        saveConfig(appConfig);
        return "Paste Style Set To NewLine";
    }

    if(cmd == "set paste style sequential"){
        currentPasteStyle = SEQUENTIAL;
        appConfig.pasteStyle = "sequential";
        saveConfig(appConfig);
        return "Paste Style Set To Sequential";
    }

    if(cmd == "set paste style single"){
        currentPasteStyle = SINGLE;
        appConfig.pasteStyle = "single";
        saveConfig(appConfig);
        return "Paste Style Set To Single";
    }

    if(cmd.substr(0,11) == "set keybind"){
        std::istringstream ss(cmd);
        std::string set, keybind, action, keys;
        ss>> set >> keybind >> action >> keys;

        if(action == "paste"){
          appConfig.pasteKeyBind = keys;
          appConfig.pasteKey = parseKeybind(keys);  
        } 
        if(action == "toggle"){
          appConfig.toggleKeyBind = keys;
          appConfig.toggleKey = parseKeybind(keys);  
        } 
        if(action == "pastestyle"){
            appConfig.pasteStyleKeyBind = keys;
            appConfig.pasteStyleKey = parseKeybind(keys);
        }

        saveConfig(appConfig);
        return "Keybind for "+ action + " Set To "+ keys +".";

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