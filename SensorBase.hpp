#pragma once
#include "TelemetryMessage.hpp"
#include "Types.hpp"    
#include "MemoryPool.hpp"
#include "RingBufferQueue.hpp"
#include <atomic>
#include <thread>

class SensorBase
{
    protected:
    MemoryPool& pool;
    RingBufferQueue& targetQueue;
    Priority priorityLevel;
    SensorType type;
    std::atomic<bool> running;
    std::thread worker;
    void sendData();

    public:
    // Constructor to initialize references and variables, and sets running = false.
    SensorBase(MemoryPool& p, RingBufferQueue& q, Priority prio, SensorType t);
    // Starts the sensor's worker thread, which runs the loop() function.
    void start();
    // Virtual destructor to ensure proper cleanup in derived classes
    virtual ~SensorBase();
    // Safely stops the sensor's worker thread.
    void stop();
    //Pure Virtual Function
    virtual void loop() = 0; 
};   