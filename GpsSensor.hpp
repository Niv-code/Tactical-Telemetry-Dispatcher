#pragma once
#include "TelemetryMessage.hpp"
#include "Types.hpp"    
#include "SensorBase.hpp"
#include "MemoryPool.hpp"
#include "RingBufferQueue.hpp"

class GpsSensor:public SensorBase
{
public:
    GpsSensor(MemoryPool& p, RingBufferQueue& q)
    : SensorBase(p,q,Priority::MEDIUM,SensorType::GPS){}
    void loop() override
    {
        while (running) 
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            sendData();
        }
    }
};