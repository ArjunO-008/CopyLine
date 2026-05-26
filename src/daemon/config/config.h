#ifndef CONFIG_h
#define CONFIG_H

#include<string>
#include<windows.h>

struct Config {
    std::string copyKeyBind;
    std::string pasteKeyBind;
    std::string toggleKeyBind;
    std::string pasteStyle;
};

std::string getConfigPath();
Config loadConfig();
void saveConfig(const Config& config);

#endif
