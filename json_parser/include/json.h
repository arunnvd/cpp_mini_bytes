#pragma once

#include <cstddef>
#include <string>


class JSON{
  private:
    std::string  base_data;
    size_t total_length {0};
  public:
    JSON(std::string data, size_t length);
    ~JSON();
    
    bool parse();
};

