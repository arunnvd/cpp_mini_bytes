#include <iostream>
#include "json.h"
#include "elements.h"


static bool validate_type(Elements *obj, Element_Type type){
  if(obj->get_type() == type){
    return true;
  }
  return false;
}


JSON::JSON(std::string data, size_t length) : base_data (std::move(data)), total_length(length) {
  std::cout << "JSON CLASS CREATED\n";
}

JSON::~JSON() {
  std::cout << "Class destroyed \n";
}

bool JSON::parse() {

  // start parsing from base data
  JSONObject *root = new JSONObject();
  std::string error;

  if(!root || !validate_type(root, Element_Type::JSON_ELEMENT_OBJECT))
    return false;

  if(!root->is_valid((const std::string) base_data, total_length, error)) {
    std::cout << "Parse Failed : " << error << std::endl;
    return false;
  }

  
  return true;
}
