#pragma once
#include "Exception.h"
#include <string>

class BinTreeException : public Exception
{
public:
  explicit BinTreeException(const std::string &msg, int errCode = 201)
      : Exception(msg, errCode)
  {
  }
};
