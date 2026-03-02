#pragma once
#include <cstdint> 

// --- Constants ---
constexpr int MAX_PAYLOAD_SIZE = 256;
constexpr int POOL_SIZE = 1000;
constexpr int QUEUE_CAPACITY = 100;
// --- Enums ---
enum class Priority {
    HIGH,
    MEDIUM,
    LOW
};
enum class SensorType {
    THERMAL,
    GPS,
    IMU
};