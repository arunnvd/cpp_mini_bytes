#include "sseclient.h"
#include <cstring>
#include <exception>
//#include <iostream>
#include <string>

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
    
    try {
      port = std::stoi(port_str);
    } catch(const std::exception &e) {
      throw SSEException("Unable parse port from URL");
    }

    path = temp_url.substr(path_idx);

  }


  EventSource::EventSource(std::string &url)
    : url(std::move(url)) {

    }

  bool EventSource::init() {
    parse_url();
    return true;
  }
}
