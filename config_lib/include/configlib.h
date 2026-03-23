#pragma once

#include <exception>
#include <string>
#include <unordered_map>

namespace config {

  const char config_debug = '#';
  const char config_delimitor = '=';


  class ConfigException : public std::exception {
    protected:
      std::string message;
    public:
      explicit ConfigException(std::string msg);

      const char* what() const noexcept override;
  };

  class ConfigFileException : public ConfigException {
    public:
      using ConfigException::ConfigException;
  };

  class ConfigParseException : public ConfigException {
    private:
      int line;
    public:
      ConfigParseException(std::string msg, int line);
      int getline() const noexcept;
  };

  class ConfigDataNotReady : public ConfigException {
    public:
      using ConfigException::ConfigException;
  };

  class ConfigKeyNotFound : public ConfigException {
    public:
      using ConfigException::ConfigException;
  };

  class ConfigTypeMissmatch : public ConfigException {
    private:
      std:: string value;
    public:
      ConfigTypeMissmatch(std::string msg, std::string val);
      std::string getvalue() const noexcept;
  };

  class Config {
    private:
      std::string path;
      std::unordered_map<std::string, std::string> data;
      bool config_ready{false};

    public:
      Config(); // lets use default constructor for now.

      bool load(std::string path);

      bool         get_bool(const std::string &key);
      int          get_int(const std::string &key);
      std::string  get_string(const std::string &key);

      void dump_cfg();  // For debug
  };
}
