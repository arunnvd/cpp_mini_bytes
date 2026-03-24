#pragma once

#include <exception>
#include <string>
#include<sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

namespace eventsource {

  class SSEException : public std::exception {
    private:
      std::string message;
    public:
      explicit SSEException(std::string msg) : message(std::move(msg)){};
      const char* what() const noexcept {return message.c_str();}
  };

  class EventSource {
    private:
      int             socket_handle;
      char            * hostname;
      struct hostent  * host_entry;
      struct in_addr  ** addr_list;
      int             port {80};
      std::string     url;
      std::string     path;

    public:
      EventSource(std::string &url);

      bool init();

      void just_debug();

    private:
      void parse_url();
  };
}
