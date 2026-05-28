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

            if(ctrl == appConfig.toggleKey.ctrl &&
                shift == appConfig.toggleKey.shift &&
                alt == appConfig.toggleKey.alt &&
                key->vkCode == appConfig.toggleKey.vkCode){
                    onToggle();
                }

            if(ctrl == appConfig.pasteKey.ctrl &&
                shift == appConfig.pasteKey.shift &&
                alt == appConfig.pasteKey.alt &&
                key->vkCode == appConfig.pasteKey.vkCode){
                    onPaste();
                }
                
            if(ctrl == appConfig.pasteStyleKey.ctrl &&
                shift == appConfig.pasteStyleKey.shift &&
                alt == appConfig.pasteStyleKey.alt &&
                key->vkCode == appConfig.pasteStyleKey.vkCode){
                    onSwitchPasteStyle();
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

