#include "elements.h"
#include "utils.h"
#include <iostream>

// ------ Constructors & Destructors -------------

JSONObject::JSONObject() : name{"root"} {
  //Json object created without name - Consider as root object
  // TODO : Limit number of root objects to One
}

JSONObject::JSONObject(std::string name) : name{name} {}

JSONObject::~JSONObject() {}

// -----------------------------------------------

Element_Type JSONObject::get_type() {
  return type;
}

bool JSONObject::is_valid(const std::string data_obj,  
          size_t length, std::string &error_messge) {
  
  // Validate the object starts with '{' and ends with '}'
  // Rest of the Json validation happens later

  if (length < JSON_OBJ_MIN_SIZE) {
    std::cerr << "Invalid json object, minimum size required = " << JSON_OBJ_MIN_SIZE << std::endl;
    error_messge = "Invalid size";
    return false;
  }

  //Validate first and last chars
  if(data_obj.at(0) == OBJ_BEGIN_VALID 
      && data_obj.at(length -1) == OBJ_END_VALID) {
    error_messge = "No Error";
    return true;
  }

  error_messge = "Invalid Object, can't parse";
  return false;
  
}

std::string JSONObject::get_name() {
  return name;
}
