# Multi-threaded File Management System

## Description
A C++ application that provides a thread-safe file management system with concurrent operations and variable manipulation capabilities. The application monitors system resources and manages thread allocation for various file operations while maintaining thread safety through mutex locks.

## Purpose
- Demonstrate concurrent programming concepts using C++ threads
- Provide safe file operations with thread management
- Monitor and log system activities
- Handle basic variable operations in a thread-safe manner
- Showcase proper resource management and synchronization

## Features
- File Operations:
    - Create new text files
    - Delete existing files
    - Search content within files
    - Read file contents
- Variable Operations:
    - Increment
    - Decrement
    - Print
    - Multiply (by 2)
- Thread Management:
    - Dynamic thread allocation
    - Resource monitoring
    - Thread-safe operations
- System Logging:
    - Automatic operation logging
    - Timestamp-based entries
    - Thread activity monitoring

## Inputs
1. File Operations:
    - File name
    - File path
    - Search terms (for search operation)

2. Menu Selection:
    - Operation choice (1-9)
    - 1: Create File
    - 2: Delete File
    - 3: Search in File
    - 4: Read File
    - 5: Increment Variable
    - 6: Decrement Variable
    - 7: Print Variable
    - 8: Multiply Variable
    - 9: Exit

## Outputs
1. Console Output:
    - Operation status messages
    - Current variable value
    - Available thread count
    - File operation results
    - Search results
    - Error messages

2. File System:
    - Created/Modified text files
    - System log file (`thread_monitor.log`)

3. Log File Contents:
    - Timestamp for each operation
    - Thread status updates
    - Operation completion status
    - Resource availability updates

## Technical Requirements
- C++ compiler with C++11 support or higher
- Support for standard threading library
- File system access permissions
- Environment with USERPROFILE variable set

## Thread Safety
The application implements thread safety through multiple mutex locks:
- `ioMutex`: Protects console I/O operations
- `fileMutex`: Ensures atomic file operations
- `variableMutex`: Guards shared variable access
- `logMutex`: Protects log file writes
- `userThreadsMutex`: Protects the thread counter that tracks available system threads