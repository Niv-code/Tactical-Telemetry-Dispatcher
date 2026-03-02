#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// Headers של התשתית
#include "MemoryPool.hpp"
#include "RingBufferQueue.hpp"
#include "Dispatcher.hpp"
#include "SensorBase.hpp" 
#include "Types.hpp"

// Headers של החיישנים הספציפיים
#include "ThermalSensor.hpp"
#include "GpsSensor.hpp"
#include "ImuSensor.hpp"
#define VERSION 1
int main() {
    std::cout << "--- Tactical Telemetry System Starting ---" << std::endl;
    MemoryPool pool;

    
    RingBufferQueue highQueue;
    RingBufferQueue mediumQueue;
    RingBufferQueue lowQueue;

    Dispatcher dispatcher(highQueue, mediumQueue, lowQueue, pool);

    ThermalSensor thermal(pool, highQueue);
    GpsSensor gps(pool, mediumQueue);
    ImuSensor imu(pool, lowQueue);

    std::cout << "[MAIN] Starting Dispatcher..." << std::endl;
    dispatcher.start();

    std::cout << "[MAIN] Starting Sensors..." << std::endl;
    thermal.start();
    gps.start();
    imu.start();

    std::cout << "[MAIN] System is running. Monitoring telemetry flow..." << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(30));

    std::cout << "\n[MAIN] Shutting down system..." << std::endl;
    
    thermal.stop();
    gps.stop();
    imu.stop();
    
    dispatcher.stop();

    std::cout << "--- System Shutdown Complete ---" << std::endl;
    return 0;
}