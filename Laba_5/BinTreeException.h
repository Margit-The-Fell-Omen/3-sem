#pragma once
#include "Exception.h"
#include <string>

class BinTreeException : public Exception
{
public:
  explicit BinTreeException(const std::string &msg, int errCode = 201)
      : Exception(errCode, ExceptionTypes::CONTAINER, msg)
  {
  }

  static void throwIfElementNotFound(bool found, const std::string &operation)
  {
    if (!found)
    {
      throw BinTreeException("Ошибка " + operation +
                             ": элемент не найден в дереве.");
    }
  }

  static void throwIfElementExists(bool found, const std::string &operation)
  {
    if (found)
    {
      throw BinTreeException("Ошибка " + operation +
                             ": такой элемент уже существует в дереве.");
    }
  }
};
