#include "SensorBase.hpp"
#include <thread>
#include <iostream>

SensorBase::SensorBase(MemoryPool& p, RingBufferQueue& q, Priority prio, SensorType t) 
: pool(p) , targetQueue(q) , priorityLevel(prio) , type(t) , running(false) {}

SensorBase::~SensorBase() {stop();}

void SensorBase::start()
{
    if (running) return;
    running = true;
    worker = std::thread(&SensorBase::loop, this);
}
void SensorBase::stop()
{
    if(!running)
        return;
    running = false;
    if(worker.joinable())
        worker.join();
}
void SensorBase::sendData()
{
    if(pool.allocate())
    {
        TelemetryMessage* msg = pool.allocate();
        if (msg == nullptr)
        {
            std::cout << "[ERROR] Memory Pool Exhausted - Cannot allocate message for " << (int)type << std::endl;
            return;
        }
        msg->timestamp = std::chrono::system_clock::now().time_since_epoch().count();
        msg->type = this->type;
        msg->priority = this->priorityLevel;
        if(!targetQueue.enqueue(msg))
        {
            pool.deallocate(msg);
            std::cout << "[WARNING] Queue Full - Dropped Message from Sensor " << (int)type << std::endl;
        }
    }
}
