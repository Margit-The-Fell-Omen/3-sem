#pragma once
#include "Exception.h"
#include <string>

class FileException : public Exception
{
public:
  explicit FileException(const std::string &msg, int errCode = 301)
      : Exception(msg, errCode)
  {
  }
};
