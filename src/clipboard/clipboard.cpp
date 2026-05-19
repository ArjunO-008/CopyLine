#include "clipboard.h"
#include<windows.h>
#include<iostream>



int clipBoardCopy(){

    if(!OpenClipboard(NULL)){
        std::cout<<"Failed To Load ClipBoard\n";
        return 1;
    }

    if(!IsClipboardFormatAvailable(CF_UNICODETEXT)){
        std::cout<<"ClipBoard Dosent Not Contain Text\n";
        CloseClipboard();
        return 1;
    }

    HANDLE hData = GetClipboardData(CF_UNICODETEXT);
    if(hData == NULL){
        std::cout<<"Failed To Get ClipBoard Data\n";
        CloseClipboard();
        return 1;
    }

    wchar_t* clipBoardText = static_cast<wchar_t*>(GlobalLock(hData));
    if(clipBoardText == NULL){
        std::cout<<"Failed To Lock ClipBoard Data\n";
        CloseClipboard();
        return 1;
    }

    std::wstring ws(clipBoardText);
    GlobalUnlock(hData);
    CloseClipboard();

    std::string text(ws.begin(),ws.end());
    
    
    return 0;   

}
int clipBoardPaste(){
   

}