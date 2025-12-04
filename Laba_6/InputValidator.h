#pragma once
#include "Exception.h"
#include <cctype>
#include <string>
#include <vector>

enum class LanguageCheck
{
  ONLY_LATIN,
  ONLY_CYRILLIC
};

class InputValidator
{
private:
  static void _validateSingleLanguage(const std::string &input,
                                      LanguageCheck langCheck);
  static void validateDateFormat(const std::string &dateStr);
  static int stringToInt(const std::string &s);

public:
  // Методы для чтения и валидации
  static std::string readAndValidateNameField(
      const std::string &prompt,
      LanguageCheck langCheck = LanguageCheck::ONLY_CYRILLIC);
  static std::string readAndValidateDate(const std::string &prompt);
  static std::string readSingleWord(const std::string &prompt);
};
