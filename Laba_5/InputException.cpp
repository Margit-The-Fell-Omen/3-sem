#include "InputException.h"

// --- Реализация методов класса InputException ---

InputException::InputException(const std::string &msg, int errCode)
    : Exception(errCode, ExceptionTypes::INPUT, msg)
{
}

int InputException::_stringToInt(const std::string &s,
                                 const std::string &fieldName)
{
  if (s.empty())
  {
    throw InputException("Поле '" + fieldName +
                         "': невозможно конвертировать пустую строку в число.");
  }
  for (size_t i = 0; i < s.length(); ++i)
  {
    if (!std::isdigit(static_cast<unsigned char>(s[i])))
    {
      throw InputException("Поле '" + fieldName +
                           "': компонент даты содержит недопустимый символ '" +
                           std::string(1, s[i]) + "' на позиции " +
                           std::to_string(i));
    }
  }
  int result = 0;
  for (char c : s)
  {
    result = result * 10 + (c - '0');
  }
  return result;
}

void InputException::checkIsNumber(const std::string &input,
                                   const std::string &fieldName)
{
  if (input.empty())
  {
    throw InputException("Ввод не может быть пустым.");
  }
  bool hasDecimalPoint = false;
  size_t start = 0;
  if (input[0] == '-' || input[0] == '+')
  {
    start = 1;
    if (input.length() == 1)
    {
      throw InputException("Ввод '" + input + "' не является числом.");
    }
  }
  for (size_t i = start; i < input.length(); ++i)
  {
    if (std::isdigit(input[i]))
    {
      continue;
    }
    if (input[i] == '.')
    {
      if (hasDecimalPoint)
      {
        throw InputException(
            "Ввод '" + input +
            "' не является числом (несколько десятичных точек).");
      }
      hasDecimalPoint = true;
    }
    else
    {
      throw InputException("Ввод '" + input +
                           "' содержит недопустимые символы для числа.");
    }
  }
}

void InputException::checkLanguage(const std::string &input,
                                   const std::string &fieldName,
                                   LanguageCheck langCheck)
{
  bool hasLatin = false, hasCyrillic = false;
  for (unsigned char c : input)
  {
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
      hasLatin = true;
    }
    else if (c > 127)
    {
      hasCyrillic = true;
    }
  }
  if (langCheck == LanguageCheck::ONLY_LATIN && hasCyrillic)
  {
    throw InputException("Строка '" + input +
                         "' должна содержать только латинские буквы.");
  }
  if (langCheck == LanguageCheck::ONLY_CYRILLIC && hasLatin)
  {
    throw InputException("Строка '" + input +
                         "' должна содержать только кириллические буквы.");
  }
}

void InputException::checkNoSpecialCharsOrDigits_UTF8(
    const std::string &input, const std::string &fieldName)
{
  for (size_t i = 0; i < input.length();)
  {
    unsigned char c = input[i];
    size_t char_len = 1; // По умолчанию 1 байт (ASCII)

    if ((c & 0x80) == 0)
    { // ASCII
      char_len = 1;
      if (!std::isalpha(c) && !std::isspace(c))
      {
        throw InputException(
            "Поле '" + fieldName + "' содержит недопустимый символ '" +
            std::string(1, c) + "' на позиции " + std::to_string(i));
      }
    }
    else if ((c & 0xE0) == 0xC0)
    {
      char_len = 2;
    }
    else if ((c & 0xF0) == 0xE0)
    {
      char_len = 3;
    }
    else if ((c & 0xF8) == 0xF0)
    {
      char_len = 4;
    }
    else
    {
      throw InputException("Поле '" + fieldName +
                           "' содержит некорректный байт на позиции " +
                           std::to_string(i));
    }
    if (i + char_len > input.length())
    {
      throw InputException("Поле '" + fieldName +
                           "' содержит неполный UTF-8 символ в конце.");
    }
    i += char_len;
  }
}

void InputException::checkDateFormat(const std::string &dateStr,
                                     const std::string &fieldName)
{
  if (dateStr.length() != 10 || dateStr[2] != '.' || dateStr[5] != '.')
  {
    throw InputException("Поле '" + fieldName +
                         "': неверный формат даты. Ожидается ДД.ММ.ГГГГ.");
  }

  int day = _stringToInt(dateStr.substr(0, 2), fieldName);
  int month = _stringToInt(dateStr.substr(3, 2), fieldName);
  int year = _stringToInt(dateStr.substr(6, 4), fieldName);

  if (year < 1900 || year > 2100)
  {
    throw InputException("Поле '" + fieldName + "': год " +
                         std::to_string(year) +
                         " вне допустимого диапазона (1900-2100).");
  }
  if (month < 1 || month > 12)
  {
    throw InputException("Поле '" + fieldName + "': месяц " +
                         std::to_string(month) +
                         " вне допустимого диапазона (1-12).");
  }

  std::vector<int> daysInMonth = {0,  31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};
  bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
  if (isLeap)
  {
    daysInMonth[2] = 29;
  }

  if (day < 1 || day > daysInMonth[month])
  {
    throw InputException(
        "Поле '" + fieldName + "': день '" + std::to_string(day) +
        "' вне допустимого диапазона для месяца " + std::to_string(month) +
        " в " + std::to_string(year) + " году.");
  }
}
