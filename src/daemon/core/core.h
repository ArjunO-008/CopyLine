#ifndef CORE_H
#define CORE_H

#include<windows.h>
#include "../config/config.h"

int startApp(HINSTANCE hInstance);
void onToggle();
void onPaste();
void onSwitchPasteStyle();

extern Config appConfig;

#endif