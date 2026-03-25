#include "sseclient.h"

#include <gtest/gtest.h>
#include <string>
#include <unistd.h>
#include <iostream>

void events_recv(std::string &str) {
  std::cout << "rcvd: " << str << std::endl;
}

TEST(SSEClientTest, BasicInit) {
  std::string url("http://192.168.10.235:8000/events");
  eventsource::EventSource evt(url);

  evt.init();
  evt.register_for_event(events_recv);
  evt.connect_sse();

  sleep (10);
  evt.disconnect_sse();
  evt.wait_for_sse_close();
}
