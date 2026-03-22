#include <cassert>
#include <iostream>
#include "configlib.h"

//using namespace config;

int main () {
  
  config::Config cfg;
  std::string error;

  
  assert(cfg.load("test_config/config.in", error) == true);
  //assert(error.empty());

  std::cout << "Test completed and value = " << error << std::endl;
  return 0;
}
