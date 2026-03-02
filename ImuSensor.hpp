#pragma once
#include "TelemetryMessage.hpp"
#include "Types.hpp"    
#include "SensorBase.hpp"
#include "MemoryPool.hpp"
#include "RingBufferQueue.hpp"

class ImuSensor : public SensorBase
{
public:
    ImuSensor(MemoryPool& p, RingBufferQueue& q)
    : SensorBase(p, q, Priority::LOW, SensorType::IMU){}
    void loop() override
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        sendData();
    }
};


