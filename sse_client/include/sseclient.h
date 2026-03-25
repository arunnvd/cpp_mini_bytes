#pragma once

#include <atomic>
#include <exception>
#include <functional>
#include <string>
#include<sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>
#include <vector>

namespace eventsource {

  class SSEException : public std::exception {
    private:
      std::string message;
    public:
      explicit SSEException(std::string msg) : message(std::move(msg)){};
      const char* what() const noexcept {return message.c_str();}
  };

  typedef std::function<void (std::string &)> event_cb;

  class EventSource {
    private:
      int                     socket_handle{-1};
      char                    * hostname;
      char                    * port;
      std::string             url;
      std::string             path;
      std::thread             active_session_handle_t;
      std::vector<event_cb>   active_listners;
      std::atomic<bool>       stop_flag {false};

    public:
      EventSource(std::string &url);

      bool init();
      bool register_for_event(event_cb listner);

      void connect_sse();
      void disconnect_sse();
      bool session_active();

      void wait_for_sse_close();

    private:
      void parse_url();
      void http_receive_task();
  };
}
