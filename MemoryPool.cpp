#include "TelemetryMessage.hpp"
#include "Types.hpp"
#include <array>
#include <bitset> 
#include <mutex>
#include "MemoryPool.hpp"

MemoryPool::MemoryPool()
{
    freeList.set(); //Initializes all bits in the freeList to 1 (free) 
}
TelemetryMessage* MemoryPool::allocate()
{
    std::lock_guard<std::mutex> lock(poolMutex);//locks the mutex
    for(size_t i = 0; i < POOL_SIZE; i++)
    {
        if(freeList.test(i))
        {
            freeList.set(i,0); //index is occupied
            return &messages[i];//return pointer to the messege
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
    size_t index = msg - &messages[0]; // Calculate the message's index within the array
    if(index < POOL_SIZE)
        freeList.set(index,1);// Mark the bit in the freeList back to 1 (free)
}