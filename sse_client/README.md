# SSE Client Library

A lightweight Server-Sent Events (SSE) client library written in C++ (C++17).

## Project Description

This library provides utilities to connect to SSE endpoints and receive real-time events from servers. It includes support for event listeners and custom exception handling.

## Features

- Connect to SSE endpoints using HTTP/TCP
- Type-specific event listeners (MESSAGE, ERROR, OPEN, DISCONNECT)
- Real-time connection state tracking (CLOSED, CONNECTING, OPEN)
- Thread-safe event handling with background receive task
- Custom exception handling for SSE errors
- Event struct with metadata (data, source, event_type)

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
#include "sseclient.h"

// Define event handlers
void on_message(eventsource::Event *e) {
  std::cout << "Message: " << e->data << std::endl;
  free(e);
}

void on_error(eventsource::Event *e) {
  std::cout << "Error: " << e->data << std::endl;
  free(e);
}

void on_open(eventsource::Event *e) {
  std::cout << "Connection opened" << std::endl;
  free(e);
}

void on_disconnect(eventsource::Event *e) {
  std::cout << "Connection disconnected" << std::endl;
  free(e);
}

// Create and configure event source
eventsource::EventSource source(url);
source.init();

// Register type-specific event listeners
source.add_event_listner(eventsource::EventType::MESSAGE, on_message, false);
source.add_event_listner(eventsource::EventType::ERROR, on_error, false);
source.add_event_listner(eventsource::EventType::OPEN, on_open, false);
source.add_event_listner(eventsource::EventType::DISCONNECT, on_disconnect, false);

// Connect and listen for events
source.connect_sse();

// Check connection state
if(source.get_readystate() == eventsource::ReadyState::OPEN) {
  // Connected and receiving events
}

// Wait for connection to close
source.wait_for_sse_close();
```

### API Reference

**Enums:**
- `ReadyState`: Connection state (CLOSED, CONNECTING, OPEN)
- `EventType`: Event type (OPEN, MESSAGE, ERROR, DISCONNECT)

**Methods:**
- `EventSource(std::string &url)` - Constructor with SSE endpoint URL
- `bool init()` - Initialize the event source
- `bool add_event_listner(EventType type, event_cb listner, bool force_overwrite)` - Register event listener for specific event type
- `void connect_sse()` - Establish SSE connection
- `void disconnect_sse()` - Close SSE connection
- `bool session_active()` - Check if session is active
- `ReadyState get_readystate()` - Get current connection state
- `void wait_for_sse_close()` - Wait for connection to close (blocking)
