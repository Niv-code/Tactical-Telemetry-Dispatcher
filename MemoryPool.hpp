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
    std::bitset<POOL_SIZE> freeList; // A boolean array for tracking: 1 = free, 0 = occupied
    std::mutex poolMutex; // Mutex for thread safety

public:
    MemoryPool();// Initializes the freeList to indicate all messages are free.
    TelemetryMessage* allocate();// Returns a pointer to a free message if available, or nullptr if the pool is exhausted.
    void deallocate(TelemetryMessage* msg);// Marks the message as free again. It should also reset the message's content to default values to prevent data leakage.
};