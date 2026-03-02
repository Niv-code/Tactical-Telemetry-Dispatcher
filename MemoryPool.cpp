#include "TelemetryMessage.hpp"
#include "Types.hpp"
#include <array>
#include <bitset> 
#include <mutex>
#include "MemoryPool.hpp"

MemoryPool::MemoryPool()
{
    freeList.set(); 
}
TelemetryMessage* MemoryPool::allocate()
{
    std::lock_guard<std::mutex> lock(poolMutex);
    for(size_t i = 0; i < POOL_SIZE; i++)
    {
        if(freeList.test(i))
        {
            freeList.set(i,0); 
            return &messages[i];
        }
    }
    return nullptr;
}
void MemoryPool::deallocate(TelemetryMessage* msg)
{
    if (msg == nullptr) 
        return;
    std::lock_guard<std::mutex> lock(poolMutex);
    msg->reset();
    size_t index = msg - &messages[0]; 
    if(index < POOL_SIZE)
        freeList.set(index,1);
}