#include <windows.h>
#include <vector>

int keyTrigger(const std::vector<int>& keys){
    for(int key: keys){
        if(!(GetAsyncKeyState(key) & 0x8000)){
            return 0;
        }
    }
    return 1;
}

int copyKeyTrigger(const std::vector<int>& keys){
   return keyTrigger(keys);
}

int pasteKeyTrigger(const std::vector<int>& keys){
   return keyTrigger(keys);
}
