#ifndef CORE_H
#define CORE_H

#include<windows.h>
#include "../config/config.h"

int startApp(HINSTANCE hInstance);
void onToggle();
void onPaste();

extern Config appConfig;

#endif