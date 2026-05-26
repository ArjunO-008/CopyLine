#include "windows.h"
#include "core.h"
#include "../clipboard/clipboard.h"
#include "../input/input.h"
#include "../paste/paste.h"
#include "../queue/queue.h"
#include "../ipc/ipc.h"
#include <thread>
#include <iostream>

HWND hwnd;

bool isActive = true;
bool ignoredNextUpdate = false;

void onToggle(){
    isActive = !isActive;
}

void onPaste(){
    if(isActive){
        ignoredNextUpdate = true;
        pasteAll();
        clearQueue();
    }
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
    }
    return DefWindowProc(hwnd,uMsg,wParam,lParam);
}

int startApp(HINSTANCE hInstance){

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
    return 0;

}
