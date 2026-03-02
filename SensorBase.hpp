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
    SensorBase(MemoryPool& p, RingBufferQueue& q, Priority prio, SensorType t);// Constructor to initialize references and variables, and sets running = false.
    void start();// Starts the sensor's worker thread, which runs the loop() function.
    virtual ~SensorBase();// Virtual destructor to ensure proper cleanup in derived classes
    void stop();// Safely stops the sensor's worker thread.
    virtual void loop() = 0; //Pure Virtual Function
};   