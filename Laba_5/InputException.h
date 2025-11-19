#pragma once
#include "Exception.h"
#include <iostream>
#include <string>

// Класс для обработки ошибок ввода, содержит методы-гейткиперы
class InputException : public Exception
{
private:
  // Приватные утилиты для внутренней проверки
  static void
  _validateNoSpecialCharsOrDigits_UTF8(const std::string &input,
                                       const std::string &fieldName);
  static void _validateDateFormat(const std::string &dateStr,
                                  const std::string &fieldName);
  static int _stringToInt(const std::string &s, const std::string &fieldName);

public:
  InputException(const std::string &msg, int errCode = 101);

  // --- НОВЫЕ ПУБЛИЧНЫЕ МЕТОДЫ-ГЕЙТКИПЕРЫ ---

  // Читает и валидирует строку, которая должна содержать только буквы
  static std::string readAndValidateNameField(const std::string &prompt);

  // Читает и валидирует дату в формате ДД.ММ.ГГГГ
  static std::string readAndValidateDate(const std::string &prompt);

  // Просто читает одно слово (без пробелов)
  static std::string readSingleWord(const std::string &prompt);
};
