#include "sseclient.h"

#include <cstdlib>
#include <gtest/gtest.h>
#include <string>
#include <unistd.h>
#include <iostream>

void on_message(eventsource::Event *e) {
  std::cout << "rcvd: " << e->data << std::endl;
  free(e);
}

void on_error(eventsource::Event *e) {
  std::cout << "error: " << e->data << std::endl;
  free(e);
}

void on_disconnect(eventsource::Event *e) {
  std::cout << "disconnected: " << e->data << std::endl;
  free(e);
}

void on_open(eventsource::Event *e) {

  std::cout << "Open: " << e->data << std::endl;
  free(e);
}

TEST(SSEClientTest, BasicInit) {
  std::string url("http://192.168.10.235:8000/events");
  eventsource::EventSource evt(url);

  evt.init();
  evt.add_event_listner(eventsource::EventType::MESSAGE, on_message, false);
  evt.add_event_listner(eventsource::EventType::ERROR, on_error, false);
  evt.add_event_listner(eventsource::EventType::OPEN, on_open, false);
  evt.add_event_listner(eventsource::EventType::DISCONNECT, on_disconnect, false);
  evt.connect_sse();

  sleep (10);
  evt.disconnect_sse();
  evt.wait_for_sse_close();
}
