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
    void loop() override // Implements the main loop for the thermal sensor, which generates and sends data at random intervals between 5 to 15 seconds. 
    {
        std::default_random_engine generator;// Random number generator for sleep intervals
        std::uniform_int_distribution<int> distribution(5, 15);// Random interval between 5 and 15 seconds
        while (running) 
        {
            int seconds = distribution(generator);// Generate a random sleep interval
            std::this_thread::sleep_for(std::chrono::seconds(seconds));// Sleep for the random interval
            sendData(); //send heat data message to the queue
        }
    }
};


