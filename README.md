# Tactical Telemetry-Dispatcher
## Overview
A high-performance, multi-threaded C++17 telemetry management system designed for real-time embedded environments. The system orchestrates data flow from multiple tactical sensors (Thermal, GPS, IMU) using a prioritized dispatching architecture to ensure critical data delivery under heavy load.
## Key Features
### 1 . Strict Priority Scheduling: Implements a pre-allocated MemoryPool to eliminate runtime fragmentation and ensure $O(1)$ allocation/deallocation.
### 2. Strict Priority Scheduling: A dedicated Dispatcher manages three distinct priority levels (High, Medium, Low), ensuring mission-critical packets are transmitted first.
### 3. Thread-Safe Concurrency: Leverages std::mutex, std::atomic, and thread-safe RingBufferQueues for seamless producer-consumer synchronization.
### 4. Asynchronous Sensor Loops: Each sensor operates on an independent execution thread with unique sampling frequencies and sleep intervals
## System Components 
### 1. MemoryPool -	Manages a fixed-size block of TelemetryMessage objects to prevent heap overhead.
### 2. RingBufferQueue -Provides a thread-safe, circular buffer for inter-thread communication.
### 3. SensorBase - Abstract base class handling thread lifecycle and data population.
### 4. Dispatcher - Extracts messages from queues in priority order and simulates hardware transmission.
