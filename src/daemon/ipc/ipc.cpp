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