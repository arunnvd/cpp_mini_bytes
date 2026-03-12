#include <iostream>
#include "json.h"
#include "utils.h"
#include <iostream>

JSON::JSON() {
  std::cout << "JSON CLASS CREATED\n";
}

JSON::~JSON() {
  std::cout << "Class destroyed \n";
}

bool JSON::parse(void* data, size_t len, std::string * err)
{
  base_ptr = (p_data) data;

  if(base_ptr == nullptr || len < JSON_MIN_SIZE)
  {
    *err = "Invalid Pointer passed!!";
    return false;   
  }


  return true;
}
