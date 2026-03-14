#include <iostream>
#include "json.h"
#include "elements.h"
#include "utils.h"
#include <bitset>

// VALID Non Function Chars

bool is_char_ignored(char c) {
  std::bitset<256> valid_non_chars;
  valid_non_chars.set(' ');
  valid_non_chars.set('\t');
  valid_non_chars.set('\r');
  valid_non_chars.set('\n');

  return valid_non_chars.test((unsigned char) c);

}



static bool validate_type(Elements *obj, Element_Type type){
  if(obj->get_type() == type){
    return true;
  }
  return false;
}

static bool parse_obj(JSONObject *obj, std::string &data, size_t length, std::string &err) {

  // iterate through json object
  unsigned int i = 0;
  bool searching_key = true;

  for (char c : data) {
    i++;
    if ((is_char_ignored(c) || (i==1 && c == OBJ_BEGIN_VALID))  
          && i < length) {
      continue;
    }

    if(c != '"' && searching_key) {
      std::cerr << "Char that violated rules : " << c << std::endl;
      err = "Missing Key, Invalid "+ obj->get_name() + " Object";
      return false;
    }
    else if (searching_key) {
      //Found key starting now capture key from next char
      searching_key = false;
      continue;
    }



  }

  return true;
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

  //Start parsing now.
  if (!parse_obj(root, base_data, total_length, error)) {
    std::cerr << "Parsing failed : " << error << std::endl;
    return false;
  }
  
  return true;
}
