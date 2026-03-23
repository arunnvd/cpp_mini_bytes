//#include <cassert>
#include "configlib.h"
#include <gtest/gtest.h>
#include <string>

//using namespace config;

TEST(ConfiglibTest, BasicParse) {
  config::Config cfg;

  EXPECT_NO_THROW(cfg.load("test_config/config.in"));

  cfg.dump_cfg();
}

TEST(ConfiglibTest, InvalidFile) {
  config::Config cfg;

  EXPECT_THROW(cfg.load("test_config/_config.in"), config::ConfigFileException);
}

TEST(ConfiglibTest, NoFile) {
  config::Config cfg;

  EXPECT_THROW(cfg.load(""), config::ConfigFileException);
}

TEST(ConfiglibTest, GetBool) {
  config::Config cfg;
  bool value;

  EXPECT_NO_THROW(cfg.load("test_config/config.in"));

  EXPECT_THROW(cfg.get_bool("port"), config::ConfigTypeMissmatch);

  EXPECT_NO_THROW({
      value = cfg.get_bool("debug");
  });
  EXPECT_TRUE(value);
}

TEST(ConfiglibTest, GetInt) {
  config::Config cfg;
  int value;

  EXPECT_NO_THROW(cfg.load("test_config/config.in"));

  EXPECT_THROW(cfg.get_int("debug"), config::ConfigTypeMissmatch);

  EXPECT_NO_THROW({
      value = cfg.get_int("port");
  });

  EXPECT_EQ(value, 8080);
}

TEST(ConfiglibTest, GetString) {
  config::Config cfg;
  std::string str;

  EXPECT_NO_THROW(cfg.load("test_config/config.in"));

  EXPECT_THROW(cfg.get_string("invalid"), config::ConfigKeyNotFound);

  EXPECT_NO_THROW({
      str = cfg.get_string("host");
  });
  EXPECT_STRCASEEQ(str.c_str(), "localhost");
  
}






