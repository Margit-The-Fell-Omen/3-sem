#pragma once

#include "Exception.h"
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

enum class LanguageCheck
{
  ONLY_LATIN,
  ONLY_CYRILLIC
};

class InputException : public Exception
{
private:
  // Конвертер строки в число теперь тоже принимает имя поля для детализации
  // ошибки
  static int _stringToInt(const std::string &s, const std::string &fieldName);

public:
  InputException(const std::string &msg, int errCode = 101);

  // --- Статические методы валидации с детализацией ошибок ---
  static void checkIsNumber(const std::string &input,
                            const std::string &fieldName);
  static void checkLanguage(const std::string &input,
                            const std::string &fieldName,
                            LanguageCheck langCheck);
  static void checkNoSpecialCharsOrDigits_UTF8(const std::string &input,
                                               const std::string &fieldName);
  static void checkDateFormat(const std::string &dateStr,
                              const std::string &fieldName);
};
