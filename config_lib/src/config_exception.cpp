#include <configlib.h>
#include <utility>

namespace config {
  ConfigException::ConfigException(std::string msg) : message(std::move(msg)) {

  }

  const char* ConfigException::what() const noexcept {
    return message.c_str();
  }

  ConfigParseException::ConfigParseException(std::string msg, int line)
    : ConfigException(
        msg + "(Line : " + std::to_string(line) + " )"
        ), line(line) {

  }

  int ConfigParseException::getline() const noexcept{
    return line;
  }

  ConfigTypeMissmatch::ConfigTypeMissmatch(std::string msg, std::string val)
    : ConfigException(
        msg + "(Actual Value = " + val + ")"
        ), value(val) {

  }

  std::string ConfigTypeMissmatch::getvalue() const noexcept{
    return value;
  }
}
