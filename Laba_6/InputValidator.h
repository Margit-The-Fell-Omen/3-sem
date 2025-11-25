#pragma once
#include "Exception.h"
#include <cctype>
#include <string>
#include <vector>

class InputValidator
{
private:
  static void validateNoSpecialCharsOrDigitsUTF8(const std::string &input);
  static void validateDateFormat(const std::string &dateStr);
  static int stringToInt(const std::string &s);

public:
  // Методы для чтения и валидации
  static std::string readAndValidateNameField(const std::string &prompt);
  static std::string readAndValidateDate(const std::string &prompt);
  static std::string readSingleWord(const std::string &prompt);
};
