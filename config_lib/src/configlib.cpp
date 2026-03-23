#include "configlib.h"
#include <fstream>
#include <iostream>
#include <optional>
#include <utility>

namespace config {

  static std::string trim_whitespace(const std::string &str) {
    const std::string &whitespace = " \t\n\r";
    const auto begin = str.find_first_not_of(whitespace);

    if(begin == std::string::npos) {
      //Entire string is white space
      return "";
    }

    const auto end = str.find_last_not_of(whitespace);
    const auto range = end - begin + 1;

    return str.substr(begin, range);
  }

  static std::optional<std::pair<std::string, std::string>> split_key_value(std::string &config_line) {
    
    const auto delim_index = config_line.find_first_of(config::config_delimitor);
    
    if(delim_index == std::string::npos) {
      // No delimitor('=') present in the line 
      return std::nullopt;
    }

    std::string key = trim_whitespace(config_line.substr(0, delim_index));
    std::string value = trim_whitespace(config_line.substr(delim_index + 1));

    return std::make_pair(key, value);
  }

  Config::Config(){
    // Nothing doing here for now
  }

  bool Config::load(std::string path) {

    if (path.empty()) {
      //error = "Invalid config path, can't parse!";
      throw ConfigFileException("Invalid File path");
    }

    std::ifstream cfg_file(path);
    std::string   line_read;
    int           line_number = 0;

    if(!cfg_file.is_open()) {
      //error = "Unable to open config file";
      throw ConfigFileException("Unable to open config file");
    }

    while (std::getline(cfg_file, line_read)) {
      std::string line = trim_whitespace(line_read);
      line_number ++ ;

      // Ignore if line is empty
      if(line.empty()) {
        continue;
      }
      // Ignore if its a comment line
      if (line.front() == config::config_debug) {
        continue;
      }

      auto config_pair = split_key_value(line);

      if(config_pair == std::nullopt) {
        //error = "Invalid Key value pair at line : " + line ;
        cfg_file.close();
        throw ConfigParseException("Invalid key-value pair", line_number);
      }

      data.insert((std::pair<std::string, std::string>) *config_pair);
    }

    config_ready = true;

    cfg_file.close();
    return config_ready;
  }

  void Config::dump_cfg() {
    if(config_ready == false) {
      std::cout << "Data not ready\n";
      return;
    }

    for(const auto &[key, value] : data) {
      std::cout << key << " :: " << value << std::endl;
    }

  }



}
