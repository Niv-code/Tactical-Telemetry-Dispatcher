#pragma once
#include "TelemetryMessage.hpp"
#include "Types.hpp"
#include <array>
#include <bitset> 
#include <mutex>  

class MemoryPool 
{
private:
    std::array<TelemetryMessage, POOL_SIZE> messages;
    // A boolean array for tracking: 1 = free, 0 = occupied
    std::bitset<POOL_SIZE> freeList; 
    // Mutex for thread safety
    std::mutex poolMutex; 

public:
    // Initializes the freeList to indicate all messages are free.
    MemoryPool();
    // Returns a pointer to a free message if available, or nullptr if the pool is exhausted.
    TelemetryMessage* allocate();
    // Marks the message as free again. It should also reset the message's content to default values to prevent data leakage.
    void deallocate(TelemetryMessage* msg);
};