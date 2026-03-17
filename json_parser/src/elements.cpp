#include "elements.h"
#include "utils.h"
#include <iostream>

inline bool is_valid_char(char c) {
  return !(c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\0');
}

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

  if(data_obj.at(0) != OBJ_BEGIN_VALID ) {
    error_messge = "Invalid start char";
    return false;
  }

  if (data_obj.back() != OBJ_END_VALID) {
    error_messge = "Invalid Last char";
    return false;
  }

  error_messge = "No Error";
  return true;
  
}

std::string JSONObject::get_name() {
  return name;
}

std::string JSONObject::display() {
  return "Not Implemented Yet\n";
}

/* --------------------------------------------------------------------------- 
*
* JSONNull 
*
* ---------------------------------------------------------------------------*/

Element_Type JSONNull::get_type() {
  return type;
}

std::string JSONNull::display() {
  return "Null";
}


/* --------------------------------------------------------------------------- 
*
* JSONString
*
* ---------------------------------------------------------------------------*/

JSONString::JSONString(std::string value) {
  std::cout << "JSONString constructor called with value "<< value << std::endl;

}

Element_Type JSONString::get_type() {
  return type;
}

std::string JSONString::display() {
  return data;
}
