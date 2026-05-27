#include <windows.h>
#include <iostream>
#include <string>

#define PIPE_NAME L"\\\\.\\pipe\\CopyLine"
#define BUFFER_SIZE 512

std::string sendCommand(const std::string& cmd){
    HANDLE hPipe = CreateFileW(
        PIPE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0,NULL,
        OPEN_EXISTING,
        0,NULL
    );

    if(hPipe == INVALID_HANDLE_VALUE){
        return "Error: CopyLine Daemon Is Not Running";
    }

    DWORD bytesWritten;
    WriteFile(hPipe, cmd.c_str(),cmd.size(),&bytesWritten,NULL);

    char buffer[BUFFER_SIZE];
    DWORD bytesRead;
    ReadFile(hPipe,buffer,BUFFER_SIZE -1 ,&bytesRead,NULL);
    buffer[bytesRead] = '\0';

    CloseHandle(hPipe);
    return std::string(buffer);
}

std::string buildCommand(int argc,char* argv[]){
    std::string cmd = "";
    for(int i = 1; i < argc; i++){
        if(i > 1) cmd += " ";
        cmd += argv[i];
    }

    return cmd;
}

void captureKeybind(const std::string& action){
    std::cout<<"Press The Key Combination"<< action <<"Key Combination, Then Press ENTER To Confirm\n";
    SetConsoleCtrlHandler(NULL, TRUE);

    std::string captured = "";
    bool ctrl = false, shift = false , alt = false;
    int mainKey = 0;

    while(true){
        ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
        shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
        alt = GetAsyncKeyState(VK_MENU) & 0x8000;

        if(GetAsyncKeyState(VK_RETURN) & 0x8000){
            if(captured != "") break;
        }
        
        for(int k='A';k<='Z';k++){
            if(GetAsyncKeyState(k) &0x8000){
                mainKey = k;
            }
        }
        
        for(int k='0';k<='9';k++){
            if(GetAsyncKeyState(k) &0x8000){
                mainKey = k;
            }
        }

        if(mainKey !=0){
            captured = "";
            if(ctrl) captured += "Ctrl+";
            if(shift) captured += "Shift+";
            if(alt) captured += "Alt+";
            captured += (char)mainKey;
            std::cout<<"\rCaptured: "<<captured <<"   ";
            std::flush(std::cout);
            mainKey=0;
        }
        Sleep(50);
    }
    std::string cmd = "set keybind "+ action + " "+ captured;
    std::cout << sendCommand(cmd)<< "\n";
    SetConsoleCtrlHandler(NULL, FALSE);
}

void runSetup(){
    std::cout<<"Copyline Setup\n";
    std::cout<<"----------\n\n";
    captureKeybind("copy");
    captureKeybind("paste");
    captureKeybind("toggle");
    std::cout<<"\nSetup Completed!\n";
}

int main(int argc, char* argv[]){
    if(argc < 2){
        std::cout<<"Usage: copyline <commands>\n";
        std::cout<<"Commands:\n";
        std::cout<<" toggle\n";
        std::cout<<" queue show\n";
        std::cout<<" queue clear\n";
        std::cout<<" set paste style\n";
        std::cout<<" set keybind copy <keys>\n";
        std::cout<<" set keybind paste <keys>\n";
        std::cout<<" set keybind toggle <keys>\n";

        return 0;
    }

    std::string cmd = buildCommand(argc,argv);

    if(cmd == "set paste style"){
        std::cout<< "Choose paste style:\n";
        std::cout<<"[1] newline\n";
        std::cout<<"[2] sequential\n";
        std::cout<<"[3] single\n";
        int choice;
        std::cin>>choice;
        if(choice == 1) cmd = "set paste style newline";
        else if(choice == 2) cmd = "set paste style sequential";
        else if(choice == 3) cmd = "set paste style single";
        else{
            std::cout<<"Invalid Choice";
            return 1;
        }
    }
    
    if(cmd == "setup"){
        runSetup();
        return 0;
    }

    std::cout << sendCommand(cmd) << "\n";
    return 0;
}