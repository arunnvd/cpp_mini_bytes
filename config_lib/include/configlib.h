#pragma once

#include <string>
#include <unordered_map>

namespace config {

  const char config_debug = '#';
  const char config_delimitor = '=';

  class Config {
    private:
      std::string path;
      std::unordered_map<std::string, std::string> data;
      bool config_ready{false};

    public:
      Config(); // lets use default constructor for now.

      bool load(std::string path, std::string& error);

      bool         get_bool(const std::string key);
      int          get_int(const std::string key);
      std::string  get_string(const std::string key);
  };
}
