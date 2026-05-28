#include "tray.h"
#include <shellapi.h>

NOTIFYICONDATAA nid = {};

void initTray(HWND hwnd, HINSTANCE hInstance){
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON |NIF_MESSAGE | NIF_TIP;
    nid.uCallbackMessage = WM_TRAY;
    nid.hIcon = LoadIcon(NULL,IDI_APPLICATION);
    strcpy(nid.szTip,"CopyLine - OFF");

    Shell_NotifyIconA(NIM_ADD,&nid);
}

void updateTrayTooltip(const char* text){
    strcpy(nid.szTip,text);
    Shell_NotifyIconA(NIM_MODIFY,&nid);
}

void removeTray(){
    Shell_NotifyIconA(NIM_DELETE,&nid);
}