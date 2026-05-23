#include <windows.h>
#include <vector>

bool triggeredKeyPressed = false;

int keyTrigger(const std::vector<int>& keys){

    bool current = true;

    for(int key: keys){
        if(!(GetAsyncKeyState(key) & 0x8000)){
            current = false;
        }
    }

    if(current && !triggeredKeyPressed){
        triggeredKeyPressed = true;
        return 1;
    }
    if(!current){
        triggeredKeyPressed = false;
    }

    return 0;
}

int copyKeyTrigger(const std::vector<int>& keys){
   return keyTrigger(keys);
}

int pasteKeyTrigger(const std::vector<int>& keys){
   return keyTrigger(keys);
}
