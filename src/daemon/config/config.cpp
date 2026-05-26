#include "config.h"
#include<windows.h>
#include<string>
#include<iostream>

std::string getConfigPath(){
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL,exePath,MAX_PATH);

    std::string path(exePath);

    size_t lastSlash = path.find_last_of("\\/");
    path = path.substr(0,lastSlash);
    lastSlash = path.find_last_of("\\/");
    path = path.substr(0,lastSlash);

    return path + "\\config\\config.ini";
}

Config loadConfig(){
    Config config;
    std::string iniPath = getConfigPath();
    const char* path = iniPath.c_str();

    char buffer[256];

    GetPrivateProfileStringA("keybindings","copy","Ctrl+Shift+C",buffer,256,path);
    config.copyKeyBind = buffer;

    GetPrivateProfileStringA("keybindings","paste","Ctrl+Shift+V",buffer,256,path);
    config.pasteKeyBind = buffer;

    GetPrivateProfileStringA("keybindings","toggle","Ctrl+L",buffer,256,path);
    config.toggleKeyBind = buffer;

    GetPrivateProfileStringA("paste","style","newline",buffer,256,path);
    config.pasteStyle = buffer;

    return config;
}

void saveConfig(const Config& config){
    std::string iniPath = getConfigPath();
    const char* path = iniPath.c_str();

    WritePrivateProfileStringA("keybindings","copy",config.copyKeyBind.c_str(),path);
    WritePrivateProfileStringA("keybindings","paste",config.pasteKeyBind.c_str(),path);
    WritePrivateProfileStringA("keybindings","toggle",config.toggleKeyBind.c_str(),path);
    WritePrivateProfileStringA("paste","style",config.pasteStyle.c_str(),path);
}