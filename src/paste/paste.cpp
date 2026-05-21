#include<string>
#include "../queue/queue.h"
#include "../clipboard/clipboard.h"

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

}
