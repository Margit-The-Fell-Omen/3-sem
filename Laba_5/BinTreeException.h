#pragma once
#include "Exception.h"
#include <string>

// Класс для исключений, связанных с операциями в бинарном дереве
class BinTreeException : public Exception
{
public:
  // Конструктор вызывает конструктор базового класса
  explicit BinTreeException(const std::string &msg,
                            int errCode = 201) // Код 201 для ошибок контейнера
      : Exception(errCode, ExceptionTypes::CONTAINER, msg)
  {
  }

  // --- Статические методы для проверок ---

  // Выбрасывает исключение, если элемент НЕ найден
  static void throwIfElementNotFound(bool found, const std::string &operation)
  {
    if (!found)
    {
      throw BinTreeException("Ошибка " + operation +
                             ": элемент не найден в дереве.");
    }
  }

  // Выбрасывает исключение, если элемент УЖЕ существует
  static void throwIfElementExists(bool found, const std::string &operation)
  {
    if (found)
    {
      throw BinTreeException("Ошибка " + operation +
                             ": такой элемент уже существует в дереве.");
    }
  }
};
