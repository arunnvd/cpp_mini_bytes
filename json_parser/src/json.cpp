#include <iostream>
#include "json.h"
#include "elements.h"
#include "utils.h"
#include <bitset>
#include <string>

// VALID Non Function Chars

bool is_char_ignored(char c) {
  std::bitset<256> valid_non_chars;
  valid_non_chars.set(' ');
  valid_non_chars.set('\t');
  valid_non_chars.set('\r');
  valid_non_chars.set('\n');

  return valid_non_chars.test((unsigned char) c);

}

constexpr inline bool valid_keychar(char c) {
  return (c >= 'A' && c <= 'Z') ||
         (c >= 'a' && c <= 'z') ||
         (c >= '0' && c <= '9') ||
         (c == '_') || (c == '"');
}


static bool validate_type(Elements *obj, Element_Type type){
  if(obj->get_type() == type){
    return true;
  }
  return false;
}

static std::string get_next_key(const std::string data, const int key_start, size_t remaining_len) {
  std::string   key;
  int           key_end = -1;

  if (data.at(key_start) != '"'){
    //Invalid Key start - Keys are always expected to start with double quotes
    std::cout << "DEBUG :: Invalid Key start : " << data.at(key_start) << std::endl;
    return "";
  }

  for (size_t i = key_start + 1; i < remaining_len ; i++) {
    char c = data.at(i);
    
    if(!valid_keychar(c)){
      // Invalud Key character found ABORT
      std::cout << "DEBUG :: Invalid char at : " << std::to_string(i) <<", char : "<<  c << std::endl;
      return "";
    }

    if(c == '"') {
      key_end = i;
      break;
    } 
  }

  key = data.substr(key_start + 1, key_end - key_start - 1);
  std::cout << "DEBUG : extracted key : " << key << std::endl;

  return key;
}

static bool parse_obj(JSONObject *obj, std::string &data, size_t length, std::string &err) {

  // iterate through json object
  bool          searching_key = true;
  std::string   active_key;

  for(size_t j = 0; j < length ;j++) {
//  for (char c : data) {
    char c = data.at(j);
    if (is_char_ignored(c) || (j==0 && c == OBJ_BEGIN_VALID)) {
      continue;
    }

    if(searching_key && c == '"') {
      // Start of a new key
      size_t remaining_len = length - j;
      active_key = get_next_key((const std::string) data , j, remaining_len);

      if(active_key.length() < 1) {
        err = "ERRROR : Invalid Key, error parsing";
        return false;
      }

      std::cout << "DEBUG : Key = " << active_key << std::endl;
      // Temp break
      break;
      obj->get_name();

    } else if(searching_key == false) {
      //Logic to parse value for active key
    }
    else {
      //Invalid object
      err = "Invalid Object parsed, cant parse char at : " + std::to_string(j);
      return false;
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
