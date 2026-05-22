#ifndef QUEUE_h
#define QUEUE_H

#include <string>
#include <deque>


void pushToQueue(std::string clipBoardtext);
void removeQueueElement();
std::deque<std::string> getQueue();

#endif