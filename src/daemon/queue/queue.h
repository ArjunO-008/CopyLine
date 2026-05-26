#ifndef QUEUE_H
#define QUEUE_H

#include <string>
#include <deque>


void pushToQueue(std::string clipBoardtext);
void removeQueueElement();
void clearQueue();
std::deque<std::string> getQueue();

#endif