#pragma once
#include "TelemetryMessage.hpp"
#include "Types.hpp"    
#include "SensorBase.hpp"
#include "MemoryPool.hpp"
#include <random>
#include "RingBufferQueue.hpp"

class ThermalSensor: public SensorBase
{
    public:
    ThermalSensor(MemoryPool& p, RingBufferQueue& q) 
        : SensorBase(p, q, Priority::HIGH, SensorType::THERMAL) {}
    void loop() override 
    {
        // Random number generator for sleep intervals
        std::default_random_engine generator;
        // Random interval between 5 and 15 seconds
        std::uniform_int_distribution<int> distribution(5, 15);
        while (running) 
        {
            // Generate a random sleep interval
            int seconds = distribution(generator);
            // Sleep for the random interval
            std::this_thread::sleep_for(std::chrono::seconds(seconds));
            //send heat data message to the queue
            sendData(); 
        }
    }
};


