#include "InputValidator.h"
#include "InputException.h"
#include <iostream>
#include <limits>

void InputValidator::validateNoSpecialCharsOrDigitsUTF8(
    const std::string &input)
{
  for (size_t i = 0; i < input.length();)
  {
    unsigned char c = input[i];
    size_t char_len = 1;

    if ((c & 0x80) == 0)
    {
      char_len = 1;
      if (!std::isalpha(c))
      {
        throw InputException("Недопустимый символ '" + std::string(1, c) +
                             "' на позиции " + std::to_string(i) + ".");
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
      throw InputException("Некорректный байт на позиции " + std::to_string(i) +
                           ".");
    }

    if (i + char_len > input.length())
    {
      throw InputException("Неполный UTF-8 символ в конце.");
    }
    i += char_len;
  }
}

int InputValidator::stringToInt(const std::string &s)
{
  if (s.empty())
    throw InputException("Компонент даты не может быть пустым.");

  for (size_t i = 0; i < s.length(); ++i)
  {
    if (!std::isdigit(s[i]))
    {
      throw InputException("Компонент даты содержит недопустимый символ '" +
                           std::string(1, s[i]) + "'.");
    }
  }

  return std::stoi(s);
}

void InputValidator::validateDateFormat(const std::string &dateStr)
{
  if (dateStr.length() != 10 || dateStr[2] != '.' || dateStr[5] != '.')
  {
    throw InputException("Неверный формат даты. Ожидается ДД.ММ.ГГГГ.");
  }

  int day = stringToInt(dateStr.substr(0, 2));
  int month = stringToInt(dateStr.substr(3, 2));
  int year = stringToInt(dateStr.substr(6, 4));

  if (year < 1900 || year > 2100)
  {
    throw InputException("Год вне допустимого диапазона (1900-2100).");
  }

  if (month < 1 || month > 12)
  {
    throw InputException("Месяц вне допустимого диапазона (1-12).");
  }

  std::vector<int> daysInMonth = {0,  31, 28, 31, 30, 31, 30,
                                  31, 31, 30, 31, 30, 31};
  bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);

  if (isLeap)
    daysInMonth[2] = 29;

  if (day < 1 || day > daysInMonth[month])
  {
    throw InputException("День '" + std::to_string(day) +
                         "' вне допустимого диапазона для этого месяца.");
  }
}

std::string InputValidator::readAndValidateNameField(const std::string &prompt)
{
  while (true)
  {
    try
    {
      std::cout << prompt;
      std::string input;
      std::cin >> input;

      if (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InputException("Ошибка потока ввода.");
      }

      validateNoSpecialCharsOrDigitsUTF8(input);
      return input;
    }
    catch (const InputException &e)
    {
      std::cerr << "[Ошибка ввода]: " << e.what()
                << " Пожалуйста, попробуйте снова.\n";
    }
  }
}

std::string InputValidator::readAndValidateDate(const std::string &prompt)
{
  while (true)
  {
    try
    {
      std::cout << prompt;
      std::string input;
      std::cin >> input;

      if (std::cin.fail())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InputException("Ошибка потока ввода.");
      }

      validateDateFormat(input);
      return input;
    }
    catch (const InputException &e)
    {
      std::cerr << "[Ошибка ввода]: " << e.what()
                << " Пожалуйста, попробуйте снова.\n";
    }
  }
}

std::string InputValidator::readSingleWord(const std::string &prompt)
{
  std::cout << prompt;
  std::string input;
  std::cin >> input;
  return input;
}
