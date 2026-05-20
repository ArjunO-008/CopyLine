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

    std::string pastingText = "";

    // for(std::string str: copyQueue){
    //     pastingText += str + "\n";
    // }
   
    if(!OpenClipboard(NULL)){
        std::cout<<"Failed To Open Clipboard\n";
        return 1;
    }

    EmptyClipboard();

    HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE,(pastingText.size()+1));
    char* memoryPointer = static_cast<char*>(GlobalLock(hMem));

    strcpy(memoryPointer,pastingText.c_str());
    GlobalUnlock(hMem);
    SetClipboardData(CF_TEXT,hMem);
    CloseClipboard();

    return 0;

}