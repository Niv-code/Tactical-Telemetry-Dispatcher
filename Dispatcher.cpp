#include "Dispatcher.hpp"
#include "iostream"


Dispatcher::Dispatcher(RingBufferQueue& h, RingBufferQueue& m, RingBufferQueue& l, MemoryPool& p)
: highQueue(h), mediumQueue(m) , lowQueue(l) , pool(p) , running(false){}

void Dispatcher::start()
{
    if (running) return;
    running = true;
    worker = std::thread(&Dispatcher::processLoop, this);
}

void Dispatcher::stop()
{
    if(!running)
        return;
    running = false;
    if(worker.joinable())
        worker.join();
}

void Dispatcher::transmit(TelemetryMessage* msg)
{
    if (msg == nullptr) 
        return;
    std::cout << "[TRANSMIT] Sent message type " << (int)msg->type 
    << " with priority " << (int)msg->priority << std::endl;
    pool.deallocate(msg);  
}

void Dispatcher::processLoop()
{
    while(running)
    {
        TelemetryMessage* msg = nullptr;
        if(!highQueue.isEmpty())
        {
            msg = highQueue.dequeue();
        }
        else if(!mediumQueue.isEmpty())
        {
            msg = mediumQueue.dequeue();
        }
        else if(!lowQueue.isEmpty())
        {
            msg = lowQueue.dequeue();
        }
        if (msg != nullptr) 
            transmit(msg);
        else 
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}