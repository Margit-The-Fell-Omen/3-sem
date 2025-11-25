#pragma once
#include "Exception.h"
#include <iostream>
#include <string>

// Класс для обработки ошибок ввода, содержит методы-гейткиперы

class InputException : public Exception
{
public:
  explicit InputException(const std::string &msg, int errCode = 101)
      : Exception(msg, errCode)
  {
  }
};
