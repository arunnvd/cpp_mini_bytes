#pragma once
#include <stddef.h>

typedef struct _item {
  char *key;
  void *value;
} Item;

typedef char* p_data ;


class Elements {

  public:
    virtual bool is_valid() = 0;

};

class Object : private Elements {
  private:
    p_data obj_ptr;
    size_t len;
  public:
    Object(p_data data, size_t len);
    bool is_valid();

};
