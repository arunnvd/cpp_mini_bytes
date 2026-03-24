#include "sseclient.h"

#include <gtest/gtest.h>
#include <string>

TEST(SSEClientTest, BasicInit) {
  std::string url("http://192.168.10.245:8000/events");
  eventsource::EventSource evt(url);

  EXPECT_NO_THROW(evt.init());
}
