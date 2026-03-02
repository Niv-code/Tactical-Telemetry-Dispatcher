#pragma once
#include "TelemetryMessage.hpp"
#include <array>
#include <mutex>

//A thread-safe, circular FIFO queue that stores pointers to messages rather than copying the messages themselves.
class RingBufferQueue
{
    private:
    std::array<TelemetryMessage*,QUEUE_CAPACITY> buffer;// Circular buffer to hold pointers to messages
    int head;
    int tail;
    std::mutex queueMutex;// Mutex for thread safety
    public:
    RingBufferQueue();// Initializes head and tail to 0.
    bool enqueue(TelemetryMessage* msg);// Adds a message pointer to the queue. Returns false if the queue is full.
    TelemetryMessage* dequeue();// Removes and returns a message pointer from the queue. Returns nullptr if the queue is empty.
    bool isEmpty();// Checks if the queue is empty. Returns true if empty, false otherwise.
};