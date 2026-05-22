#include "clipboard.h"
#include "../queue/queue.h"
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

    pushToQueue(text);

    return 0;   
}

int setClipBoardText(std::string text){
    if(!OpenClipboard(NULL)){
        return 1;
    }
    EmptyClipboard();

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE,text.size() + 1);

    char* memoryPointer = static_cast<char*>(GlobalLock(hMem));
    
    strcpy(memoryPointer,text.c_str());

    GlobalUnlock(hMem);

    SetClipboardData(CF_UNICODETEXT,hMem);

    CloseClipboard();

    return 0;


}