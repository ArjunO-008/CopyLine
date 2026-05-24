#include <windows.h>
#include "input.h"

HHOOK KeyboardHook = NULL;

LRESULT CALLBACK KeyBoardProc(int nCode, WPARAM wParam,LPARAM lParam){
    if(nCode == HC_ACTION){
        KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;

        if(wParam == WM_KEYDOWN){
            bool ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
            bool shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;

            if(ctrl && key->vkCode == 'L'){
                onToggle();
            }

            if(ctrl && shift && key->vkCode == 'V'){
                onPaste();
            }
        }
    }
    return CallNextHookEx(KeyboardHook,nCode,wParam,lParam);
}

void registerHook(){
    KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL,KeyBoardProc,NULL,0);
}

void unregisterHook(){
    if(KeyboardHook){
        UnhookWindowsHookEx(KeyboardHook);
        KeyboardHook = NULL;
    }
}

