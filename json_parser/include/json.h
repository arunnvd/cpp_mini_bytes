#pragma once

#include "elements.h"
#include <cstddef>
#include <string>


class JSON{
  private:
    p_data base_ptr {nullptr};
    size_t len {0};
  public:
    JSON();
    ~JSON();

    bool parse(void* data, size_t len, std::string * err);
};

