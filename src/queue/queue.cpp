#include <deque>
#include <string>

std::deque<std::string> copyQueue;

void pushToQueue(std::string clipBoardtext){

   if(copyQueue.empty() || clipBoardtext != copyQueue.back()){
        copyQueue.push_back(clipBoardtext);
    }
}


std::deque<std::string> getQueue(){
    return copyQueue;
}