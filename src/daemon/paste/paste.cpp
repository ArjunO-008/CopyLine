#include<string>
#include "paste.h"
#include "../queue/queue.h"
#include "../clipboard/clipboard.h"

PasteStyle currentPasteStyle = NEWLINE;

void pasteAll(){
    if(currentPasteStyle == NEWLINE) newLineAllPaste();
    else if(currentPasteStyle == SEQUENTIAL) sequentialAllPaste();
    else if(currentPasteStyle == SINGLE) singleElementPaste();
}

int newLineAllPaste(){
    std::string text ="";

    for(std::string str:getQueue()){
        text += str + "\n";
    }

    return setClipBoardText(text);

}

int sequentialAllPaste(){
    std::string text ="";

    for(std::string str:getQueue()){
        text += str + " ";
    }

    return setClipBoardText(text);

}

int singleElementPaste(){
    if(!getQueue().empty()){
        std::string text = getQueue().front();
        removeQueueElement();
        return setClipBoardText(text);
    }
    return setClipBoardText("");
}
