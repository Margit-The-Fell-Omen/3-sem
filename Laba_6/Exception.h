#pragma once
#include <stdexcept>
#include <string>

class Exception : public std::runtime_error
{
private:
  int code;

public:
  explicit Exception(const std::string &msg, int errCode = 0)
      : std::runtime_error(msg), code(errCode)
  {
  }

  int getCode() const { return code; }
};
