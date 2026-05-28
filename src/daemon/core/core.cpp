#include "windows.h"
#include "core.h"
#include "../ipc/ipc.h"
#include "../clipboard/clipboard.h"
#include "../input/input.h"
#include "../paste/paste.h"
#include "../queue/queue.h"
#include "../tray/tray.h"
#include <thread>
#include <iostream>

HWND hwnd;
Config appConfig;

bool isActive = false;
bool ignoredNextUpdate = false;


void onToggle(){
    isActive = !isActive;
    updateTrayTooltip(isActive ? "CopyLine - ON" : "CopyLine - OFF");
    showTrayBalloon("CopyLine", isActive ? "Turned - ON" : "Turned - OFF");
}

void onPaste(){
    if(isActive){
        ignoredNextUpdate = true;
        pasteAll();
        clearQueue();
    }
}

void onSwitchPasteStyle(){
    if(currentPasteStyle == NEWLINE){
        currentPasteStyle = SEQUENTIAL;
        showTrayBalloon("CopyLine","Paste Style: Sequential");
        appConfig.pasteStyle = "sequential";
    }else if(currentPasteStyle == SEQUENTIAL){
        currentPasteStyle = SINGLE;
        showTrayBalloon("CopyLine","Paste Style: Single");
        appConfig.pasteStyle = "single";
    }else{
        currentPasteStyle = NEWLINE;
        showTrayBalloon("CopyLine","Paste Style: Newline");
        appConfig.pasteStyle = "newline";
    }
    saveConfig(appConfig);
}

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch(uMsg){
        case WM_CLIPBOARDUPDATE:
            if(ignoredNextUpdate){
                ignoredNextUpdate = false;
                return 0;
            }
            if(isActive){
                clipBoardCopy();
            }
            return 0;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_TRAY:
            if(lParam == WM_RBUTTONUP){
                POINT pt;
                GetCursorPos(&pt);

                HMENU menu = CreatePopupMenu();
                AppendMenuA(menu,MF_STRING,1,isActive ? "Turn OFF": "Turn ON");
                AppendMenuA(menu,MF_SEPARATOR,0,NULL);
                AppendMenuA(menu, MF_STRING,2,"Quit");

                SetForegroundWindow(hwnd);
                int choice = TrackPopupMenu(menu,TPM_RETURNCMD,pt.x,pt.y,0,hwnd,NULL);
                DestroyMenu(menu);
                if(choice == 1) onToggle();
                if(choice == 2) PostQuitMessage(0);
            }
            return 0;
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int startApp(HINSTANCE hInstance){
    appConfig = loadConfig();

    if(appConfig.pasteStyle == "sequential") currentPasteStyle = SEQUENTIAL;
    else if(appConfig.pasteStyle == "single") currentPasteStyle = SINGLE;
    else currentPasteStyle = NEWLINE;

    WNDCLASSW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"CopyLineDaemon";
    RegisterClassW(&wc);

    hwnd = CreateWindowExW(
        0, L"CopyLineDaemon", L"CopyLine",
        0,0,0,0,0,
        HWND_MESSAGE,
        NULL,hInstance,NULL
    );

    initTray(hwnd,hInstance);
    if(!hwnd) return 1;

    AddClipboardFormatListener(hwnd);

    MSG msg;
    registerHook();

    std::thread pipeThread(startPipeServer);
    pipeThread.detach();
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    unregisterHook();
    RemoveClipboardFormatListener(hwnd);
    removeTray();
    return 0;

}
