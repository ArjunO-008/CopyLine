#include <deque>
#include <string>

std::deque<std::string> copyQueue;

void pushToQueue(std::string clipBoardtext){
    copyQueue.push_back(clipBoardtext);
}
