#ifndef TRAY_H
#define TRAY_H

#include <windows.h>

#define WM_TRAY (WM_USER + 1)

void initTray(HWND hwnd, HINSTANCE hInstance);
void updateTrayTooltip(const char* Text);
void removeTray();
void showTrayBalloon(const char* title,const char* message);


#endif