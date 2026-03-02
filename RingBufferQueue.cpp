#include "RingBufferQueue.hpp"
#include "TelemetryMessage.hpp"
#include "Types.hpp"

RingBufferQueue::RingBufferQueue() {head = 0, tail = 0;}
// Adds a message pointer to the queue. Returns false if the queue is full.
bool RingBufferQueue::enqueue(TelemetryMessage* msg)
{
    if (msg == nullptr)
        return false;
    std::lock_guard<std::mutex> lock(queueMutex);
    if((tail + 1) % QUEUE_CAPACITY == head)
        return false; 
    buffer[tail] = msg;
    tail = (tail + 1) % QUEUE_CAPACITY;
    return true;
}
// Removes and returns a message pointer from the queue. Returns nullptr if the queue is empty.
TelemetryMessage* RingBufferQueue::dequeue()
{
    std::lock_guard<std::mutex> lock(queueMutex);
    if(head == tail)
        return nullptr;
    TelemetryMessage* msg = buffer[head];
    head = (head + 1) % QUEUE_CAPACITY;
    return msg;
}
// Checks if the queue is empty. Returns true if empty, false otherwise.
bool RingBufferQueue::isEmpty()
{
    return head == tail;
}