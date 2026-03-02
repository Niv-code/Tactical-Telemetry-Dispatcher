#pragma once
#include "TelemetryMessage.hpp"
#include "Types.hpp"    
#include "SensorBase.hpp"
#include "MemoryPool.hpp"
#include "RingBufferQueue.hpp"

class Dispatcher
{
private:
    RingBufferQueue& highQueue;
    RingBufferQueue& mediumQueue;
    RingBufferQueue& lowQueue;
    MemoryPool& pool;
    std::atomic<bool> running;
    std::thread worker;
public:
    Dispatcher(RingBufferQueue& h, RingBufferQueue& m, RingBufferQueue& l, MemoryPool& p);
    void start();
    void stop();
    void processLoop();
    void transmit(TelemetryMessage* msg);
};


