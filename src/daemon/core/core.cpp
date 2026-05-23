#include "windows.h"
#include "core.h"
#include "../clipboard/clipboard.h"

HWND hwnd;

LRESULT CALLBACK WindowProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam){
    switch(uMsg){
        case WM_CLIPBOARDUPDATE:
            clipBoardCopy();
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
    while(GetMessage(&msg,NULL,0,0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    RemoveClipboardFormatListener(hwnd);
    return 0;

}