#pragma once
#include "TelemetryMessage.hpp"
#include <array>
#include <mutex>

//A thread-safe, circular FIFO queue that stores pointers to messages rather than copying the messages themselves.
class RingBufferQueue
{
    private:
    std::array<TelemetryMessage*,QUEUE_CAPACITY> buffer;
    int head;
    int tail;
    std::mutex queueMutex;
    public:
    // Initializes head and tail to 0.
    RingBufferQueue();
    // Adds a message pointer to the queue. Returns false if the queue is full.
    bool enqueue(TelemetryMessage* msg);
    // Removes and returns a message pointer from the queue. Returns nullptr if the queue is empty.
    TelemetryMessage* dequeue();
    // Checks if the queue is empty. Returns true if empty, false otherwise.
    bool isEmpty();
};