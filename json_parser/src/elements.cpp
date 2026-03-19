#include "elements.h"
#include "json.h"
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

void JSONObject::set_total_length(size_t total_length) {
  if(total_length > 0){
    length = total_length;
  }
  else {
    std::cout << "ERROR : Invalid total Length is passed \n" ;
  }
}

std::string JSONObject::get_name() {
  return name;
}

std::string JSONObject::display() {
  std::string display_str;
  display_str.reserve(length);
  display_str += "{ \n";

  for(const auto& [key, value]: data) {
    display_str += key + " : " + value->display() + "\n";
  }

  display_str += "}";
  return display_str;
}

bool JSONObject::add_element(std::string key, std::unique_ptr<Elements> value) {

  if(key.empty() || value == nullptr) {
    std::cerr << "Invalid Object passed !! \n";
    return false;
  }

  data[key] = std::move(value);
  return true;
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

JSONString::JSONString(std::string value) : data(value){
  //std::cout << "JSONString constructor called with value "<< value << std::endl;

}

Element_Type JSONString::get_type() {
  return type;
}

std::string JSONString::display() {
  return data;
}
