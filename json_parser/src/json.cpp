#include <cstddef>
#include <iostream>
#include "json.h"
#include "elements.h"
#include "utils.h"
#include <bitset>
#include <memory>
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

static std::string get_string_value(const std::string data, const int start_pos, bool &status, int &str_end_pos) {
  // find closing or illegal char
  size_t last_pos = start_pos;

  while (!string_last_char(data.at(last_pos))) {
    if(last_pos >= data.length()){
      //No string closing, invalid data
      status = false;
      return "";
    }
    last_pos ++;
  }

  status = true;
  str_end_pos = last_pos;
  return data.substr(start_pos, (last_pos - start_pos));
}

static std::unique_ptr<Elements> get_next_value(const std::string data, const int value_start, int &value_end) {
  
  char c = data.at(value_start);

  if(is_string(c)) {
    bool stat;
    std::string value = get_string_value(data, value_start + 1, stat, value_end);
    if(stat ==false) {
      // illegal string value, break
      return nullptr;
    }

    auto next_value = std::make_unique<JSONString>(value);
    return next_value;
  }

  return nullptr;
}

static std::string get_next_key(const std::string data, const int key_start, int &end_pos) {
  std::string   key;
  int           key_end = -1;

  if (data.at(key_start) != '"'){
    //Invalid Key start - Keys are always expected to start with double quotes
    //std::cout << "DEBUG :: Invalid Key start : " << data.at(key_start) << std::endl;
    return "";
  }

  for (size_t i = key_start + 1; i < data.length() ; i++) {
    char c = data.at(i);
    
    if(!valid_keychar(c)){
      // Invalud Key character found ABORT
      //std::cout << "DEBUG :: Invalid char at : " << std::to_string(i) <<", char : "<<  c << std::endl;
      return "";
    }

    if(c == '"') {
      key_end = i;
      end_pos = key_end;
      break;
    } 
  }

  key = data.substr(key_start + 1, key_end - key_start - 1);
  //std::cout << "DEBUG : extracted key : " << key << std::endl;

  return key;
}

static bool parse_obj(JSONObject *obj, std::string &data, size_t length, std::string &err) {

  // iterate through json object
  bool                      searching_key = true;
  bool                      searching_comma = false;
  std::string               active_key;
  int                       key_value_separator_index = -1;
  std::unique_ptr<Elements> value;

  for(size_t j = 0; j < length ;) {
    char c = data.at(j);
    if (is_char_ignored(c) || (j==0 && c == OBJ_BEGIN_VALID)) {
      j++;
      continue;
    }

    if(searching_key && c == '"') {
      // Start of a new key
      int end_pos = 0;
      active_key = get_next_key((const std::string) data , j,  end_pos);

      if(active_key.length() < 1) {
        err = "ERRROR : Invalid Key, error parsing";
        return false;
      }

      //std::cout << "DEBUG : Key = " << active_key << std::endl;
      searching_key = false;
      j = end_pos + 1;
      continue;

    } else if(searching_key == false && searching_comma == false) {
      //Wait until ':' and then the first valid char
      if(c != ':' && key_value_separator_index < 0) {
        err = "Invalid key-value separator at index : " + std::to_string(j) + " , char : " + c ;
        return false;
      } else if(key_value_separator_index < 0) {
        //Found separator, update separator index and continue
        key_value_separator_index = j;
        j++;
        continue;
      } else {

        //This will be the first char of value. identify the type and create an object.
        int value_end_pos;
        value = get_next_value((const std::string) data, j, value_end_pos);
        if(value == nullptr) {
          err = "Value parsing failed, Invalid Object";
          return false;
        }
        obj->add_element(active_key, std::move(value));
        key_value_separator_index = -1;
        searching_comma = true;
        j = value_end_pos;
      }

    } else if(searching_comma) {
      if (c == OBJ_END_VALID) {
        // Nothing more to parse
        return true;
      }

      if(c == ',') {
        // End of key-value pair go to next_value
        searching_comma = false;
        searching_key = true;
        j++;
        continue;
      }

      std::cout << "Char caused failure = " << c << std::endl;

      err = "Elements are not separated using ','";
      return false; // No separator found
    }
    else {
      //Invalid object
      err = "Invalid Object parsed, cant parse char at : " + std::to_string(j);
      return false;
    }

    j++;
  }

  return true;
}


JSON::JSON(std::string data, size_t length) : base_data (std::move(data)), total_length(length) {
  //std::cout << "JSON CLASS CREATED\n";
}

JSON::~JSON() {
  //std::cout << "Class destroyed \n";
  if(json_root) {
    std::cout << "Destroying the root node\n";
    delete json_root;
  }
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

  root->set_total_length(total_length);

  //Start parsing now.
  if (!parse_obj(root, base_data, total_length, error)) {
    std::cerr << "Parsing failed : " << error << std::endl;
    return false;
  }
  json_root = root;
  return true;
}


std::string JSON::to_str() {
  if(json_root) {
    return json_root->display();
  } else {
    return "ERROR :: Json parsing not completed! Call JSON.parse() before using to_str";
  }
}
