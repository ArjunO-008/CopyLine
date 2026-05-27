#include <windows.h>
#include "input.h"
#include "../core/core.h"

HHOOK KeyboardHook = NULL;

LRESULT CALLBACK KeyBoardProc(int nCode, WPARAM wParam,LPARAM lParam){
    if(nCode == HC_ACTION){
        KBDLLHOOKSTRUCT* key = (KBDLLHOOKSTRUCT*)lParam;

        if(wParam == WM_KEYDOWN){
            bool ctrl = GetAsyncKeyState(VK_CONTROL) & 0x8000;
            bool shift = GetAsyncKeyState(VK_SHIFT) & 0x8000;
            bool alt = GetAsyncKeyState(VK_MENU) & 0x8000;

            if(ctrl == appConfig.togglKey.ctrl &&
                shift == appConfig.togglKey.shift &&
                alt == appConfig.togglKey.alt &&
                key->vkCode == appConfig.togglKey.vkCode){
                    onToggle();
                }

            if(ctrl == appConfig.pasteKey.ctrl &&
                shift == appConfig.pasteKey.shift &&
                alt == appConfig.pasteKey.alt &&
                key->vkCode == appConfig.pasteKey.vkCode){
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

