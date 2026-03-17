#pragma once

#include <cstddef>
#include <string>


constexpr inline bool is_number(char c) {
  return (c >= '0' && c <= '9') || (c == '-');
}

constexpr inline bool is_string(char c) {
  return (c == '"');
}

constexpr inline bool is_array(char c) {
  return (c == '[');
}

constexpr inline bool is_boolean(char c) {
  return (c == 't' || c == 'f');
}

constexpr inline bool is_null(char c) {
  return (c == 'n');
}

constexpr inline bool is_object(char c) {
  return (c == '{');
}

constexpr inline bool string_last_char(char c) {
  return (c == '"'); // Not considering escape char now
}


class JSON{
  private:
    std::string  base_data;
    size_t total_length {0};
  public:
    JSON(std::string data, size_t length);
    ~JSON();
    
    bool parse();
};

