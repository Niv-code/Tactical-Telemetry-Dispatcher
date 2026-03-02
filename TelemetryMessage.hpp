#pragma once
#include "Types.hpp"
#include <array>

struct TelemetryMessage {
    uint64_t timestamp;
    Priority priority;
    SensorType type;
    std::array<uint8_t, MAX_PAYLOAD_SIZE> payload;

    
    void reset() {
        timestamp = 0;
        priority = Priority::LOW;      
        type = SensorType::IMU;        
        payload.fill(0);               
    }
};