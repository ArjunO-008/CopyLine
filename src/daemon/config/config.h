#ifndef CONFIG_H
#define CONFIG_H

#include<string>
#include<windows.h>

struct KeyBind{
    bool ctrl;
    bool alt;
    bool shift;
    int vkCode;
};

struct Config {
    std::string pasteKeyBind;
    std::string toggleKeyBind;
    std::string pasteStyleKeyBind;
    std::string pasteStyle;

    KeyBind pasteKey;
    KeyBind toggleKey;
    KeyBind pasteStyleKey;
};

std::string getConfigPath();
Config loadConfig();
void saveConfig(const Config& config);
KeyBind parseKeybind(const std::string& keybind);


#endif
