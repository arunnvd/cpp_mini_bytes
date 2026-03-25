#include "sseclient.h"
#include <cstddef>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

namespace eventsource {

  void EventSource::parse_url(){
    if(url.empty()) {
      throw SSEException("Url not ready");
    }

    const auto protocol_idx = url.find_first_of(':');
    if(protocol_idx == std::string::npos) {
      throw SSEException("Invalid URL");
    }

    const std::string protocol = url.substr(0, protocol_idx);

    if(protocol != "http") {
      throw ("Invalid/NotSupported Url");
    }

    const std::string temp_url = url.substr(protocol_idx + 3); // not efficient approach but for nw doing this
    const auto hostname_idx = temp_url.find_first_of(':');

    if(hostname_idx == std::string::npos) {
      throw SSEException("Invalid Hostname in URL");
    }

    hostname = new char[hostname_idx + 1];
    std::strcpy(hostname, (temp_url.substr(0, hostname_idx)).c_str());

    const auto path_idx = temp_url.find_first_of("/");

    if(path_idx == std::string::npos) {
      throw SSEException("Invalid Port/path in url");
    }

    const std::string port_str = temp_url.substr(hostname_idx + 1, path_idx - hostname_idx - 1);
    
    port = new char[port_str.length() + 1];
    std::strcpy(port, port_str.c_str());

    path = temp_url.substr(path_idx);

  }


  EventSource::EventSource(std::string &url)
    : url(std::move(url)) {

    }

  bool EventSource::init() {
    
    try{
      parse_url();
    }catch (const SSEException & e) {
      std::cout << "SSE Init Failed : " << e.what() << std::endl;
      return false;
    }

    return true;
  }

  bool EventSource::register_for_event(event_cb listner) {
    if(!listner) {
      return false;
    }

    active_listners.push_back(listner);
    return true;
  }

  bool EventSource::session_active() {
    return active_session_handle_t.joinable();
  }

  void EventSource::connect_sse() {
    if (this->session_active()) {
      throw SSEException("Session active, disconnect old session first");
    }

    struct addrinfo hints{}, *res, *p;
    int resolve_status = -1;

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    resolve_status = getaddrinfo(hostname, port, &hints, &res);
    if(resolve_status != 0) {
      throw SSEException("Failed to resolve host");
    }

    // Try all the address from listner
    for(p = res; p != nullptr; p = p->ai_next) {
      socket_handle = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

      if(socket_handle == -1) {
        continue;
      }

      if(connect(socket_handle, p->ai_addr, p->ai_addrlen) == 0) {
        break;
      }
      else {
        std::cerr << "connect failed: " << strerror(errno) << std::endl;
      }

      // If it comes here, then connect Failed
      close(socket_handle);
      socket_handle= -1;
      freeaddrinfo(res);
      throw SSEException("Socket Connection Failed");
    }

    // Connection succesfull, start receive task in thread
    active_session_handle_t = std::thread(&EventSource::http_receive_task,this);
    freeaddrinfo(res);
  }

  void EventSource::http_receive_task() {
    
    std::string request = 
      "GET " + path + " HTTP/1.1\r\n"
      "Host: "+ hostname + "\r\n"
      "Accept: text/event-stream\r\n"
      "Cache-Control: no-cache\r\n"
      "Connection: keep-alive\r\n"
      "\r\n";

    char buffer[1024];
    std::string data_buffer;

    send(socket_handle, request.c_str(), request.length(), 0);

    while (!stop_flag) {
      int bytes = recv(socket_handle, buffer, sizeof(buffer) - 1, 0);

      //std::cout << "Received " << std::to_string(bytes) << " bytes of data\n"; 

      if(bytes <= 0) {
        std::cout << "Connection Closed \n";
        break;
      }

      buffer[bytes] = '\0';
      data_buffer += buffer;

      size_t pos;
      while ((pos = data_buffer.find("\n\n")) != std::string::npos) {
        std::string event = data_buffer.substr(0, pos);
        data_buffer.erase(0, pos + 2);

        const auto header_idx = event.find("\r\n\r\n");
        if(header_idx != std::string::npos) {
          event.erase(0, header_idx + 4);
        }

        const auto message_idx = event.find_first_of (':');
        if(message_idx != std::string::npos) {
          event.erase(0, message_idx + 2);
          for(event_cb message_cb : active_listners) {
            message_cb(event);
          }
  
        }

      }
    }

    close(socket_handle);
    socket_handle = -1;
  }

  void EventSource::disconnect_sse() {
    stop_flag = true;
    shutdown(socket_handle, SHUT_RDWR);
  }

  void EventSource::wait_for_sse_close() {
    if(active_session_handle_t.joinable()) {
      active_session_handle_t.join();
    }
  }
}




