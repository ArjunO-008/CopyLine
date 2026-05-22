#include "windows.h"
#include "../input/input.h"
#include "../clipboard/clipboard.h"
#include "../paste/paste.h"

bool isCopyLineToggledOn = true;

int startApp(){

    while (isCopyLineToggledOn){
       
        if(copyKeyTrigger({VK_LCONTROL,'C'})){
            clipBoardCopy();
            Sleep(500);
        }
        if(copyKeyTrigger({VK_LCONTROL,'V'})){
            newLineAllPaste();            
        }
        Sleep(100);
    }
    
    return 0;
}