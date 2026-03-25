# SSE Client Library

A lightweight Server-Sent Events (SSE) client library written in C++ (C++17).

## Project Description

This library provides utilities to connect to SSE endpoints and receive real-time events from servers. It includes support for event listeners and custom exception handling.

## Features

- Connect to SSE endpoints
- Register event listeners
- Thread-safe event handling
- Custom exception handling for SSE errors

## Building the project

```
> cd sse_client/build

> cmake ..
> make

// Run test
> ctest --output-on-failure

// Clean the project
> make clean      # Remove built objects
> make clean-all  # Remove entire build directory
```

## Usage

```cpp
eventsource::EventSource source(url);
source.init();
source.register_for_event([](std::string &event) {
  // Handle event
});
source.connect_sse();
// wait till all messages are received
source.disconnect_sse();
```
