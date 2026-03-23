//#include <cassert>
#include "configlib.h"
#include <gtest/gtest.h>

//using namespace config;

TEST(ConfiglibTest, BasicParse) {
  config::Config cfg;
  std::string error;

  EXPECT_THROW(cfg.load("test_config/_config.in"), config::ConfigFileException);


  cfg.dump_cfg();
}


