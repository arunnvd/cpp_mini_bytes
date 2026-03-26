#pragma once

#include <atomic>
#include <exception>
#include <functional>
#include <string>
#include<sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <thread>
#include <unordered_map>

namespace eventsource {

  enum class ReadyState {
    CLOSED,
    CONNECTING,
    OPEN
  };

  enum class EventType {
    OPEN,
    MESSAGE,
    ERROR,
    DISCONNECT
  };

  typedef struct {
    std::string   data;
    char          * source;
    EventType     event_type;
  } Event;

  std::string event_type_str(EventType e);

  class SSEException : public std::exception {
    private:
      std::string message;
    public:
      explicit SSEException(std::string msg) : message(std::move(msg)){};
      const char* what() const noexcept {return message.c_str();}
  };

  typedef std::function<void (Event *)> event_cb;

  class EventSource {
    private:
      int                     socket_handle{-1};
      char                    * hostname;
      char                    * port;
      ReadyState              ready_state{ReadyState::CLOSED};
      std::string             url;
      std::string             path;
      std::thread             active_session_handle_t;
      std::unordered_map<EventType, event_cb> event_listners;
      std::atomic<bool>       stop_flag {false};

    public:
      EventSource(std::string &url);

      bool init();
      bool add_event_listner(EventType type, event_cb listner, bool force_overwrite);

      void connect_sse();
      void disconnect_sse();
      bool session_active();
      ReadyState get_readystate();

      void wait_for_sse_close();

    private:
      void parse_url();
      void http_receive_task();
      void notify_listner(EventType type, const std::string &message);
  };
}
