#include "elements.h"
#include "utils.h"

Object::Object(p_data data, size_t len) : obj_ptr{data},len{len} {

}

bool Object::is_valid() {
  if(len < JSON_MIN_SIZE)
    return false;

  if(*(obj_ptr[0]) != OBJ_BEGIN_VALID || *obj_ptr[len - 1] != OBJ_END_VALID)
    return false;

  return true;
}
