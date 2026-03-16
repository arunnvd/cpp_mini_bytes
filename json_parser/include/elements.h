#pragma once
#include <string>
#include <unordered_map>
#include <memory>

enum class Element_Type : short {
  JSON_ELEMENT_NUMBER,
  JSON_ELEMENT_BOOLEAN,
  JSON_ELEMENT_STRING,
  JSON_ELEMENT_OBJECT,
  JSON_ELEMENT_ARRAY,
  JSON_ELEMENT_NULL
};


class Elements {

  public:
    virtual Element_Type get_type() = 0;
    virtual std::string display() = 0;
    virtual ~Elements() = default;

};

class JSONNull : public Elements {
  private :
    Element_Type type {Element_Type::JSON_ELEMENT_NULL};
  public:
    Element_Type get_type();
    std::string  display();
};

class JSONString : public Elements {
  private:
    std::string data;
    Element_Type type {Element_Type::JSON_ELEMENT_STRING};
  public:
    Element_Type get_type();
    std::string  display();
};

class JSONObject : public Elements {

  private:
    Element_Type type {Element_Type::JSON_ELEMENT_OBJECT};
    std::string name;
    size_t length {0};
    std::string base_data;
    std::unordered_map <std::string, std::unique_ptr<Elements>> data;

  public:
    //Constructor & Destructor
    JSONObject();
    JSONObject(std::string name);
    ~JSONObject();

    Element_Type  get_type();
    bool          is_valid(const std::string data_obj, size_t length, std::string &error_message);
    std::string   get_name();
    bool          add_element(std::string name, Elements element);
    std::string   display();
};
