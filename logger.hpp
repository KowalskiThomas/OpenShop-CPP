#include <iostream>
#include <string>

class Logger {
private:
  static auto write(std::string s) { std::cout << s << std::endl; }

public:
  static auto warn(std::string tag, std::string message) {
    Logger::write("Warning: [" + tag + "] " + message);
  }

  static auto info(std::string tag, std::string message) {
    Logger::write("Info:    [" + tag + "] " + message);
  }

  enum class level { _INFO, _WARNING };

  static level i;
};

Logger::level Logger::i = Logger::level::_INFO;