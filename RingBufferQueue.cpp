#include "RingBufferQueue.hpp"
#include "TelemetryMessage.hpp"
#include "Types.hpp"

RingBufferQueue::RingBufferQueue() {head = 0, tail = 0;}

bool RingBufferQueue::enqueue(TelemetryMessage* msg)// Adds a message pointer to the queue. Returns false if the queue is full.
{
    if (msg == nullptr)
        return false;
    std::lock_guard<std::mutex> lock(queueMutex);
    if((tail + 1) % QUEUE_CAPACITY == head)
        return false; // Queue is full
    buffer[tail] = msg;
    tail = (tail + 1) % QUEUE_CAPACITY;
    return true;
}

TelemetryMessage* RingBufferQueue::dequeue()// Removes and returns a message pointer from the queue. Returns nullptr if the queue is empty.
{
    std::lock_guard<std::mutex> lock(queueMutex);
    if(head == tail)
        return nullptr;
    TelemetryMessage* msg = buffer[head];
    head = (head + 1) % QUEUE_CAPACITY;
    return msg;
}

bool RingBufferQueue::isEmpty()// Checks if the queue is empty. Returns true if empty, false otherwise.
{
    return head == tail;
}