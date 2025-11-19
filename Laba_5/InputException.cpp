#include "InputException.h"
#include <cctype>
#include <limits>
#include <vector>

InputException::InputException(const std::string &msg, int errCode)
    : Exception(errCode, ExceptionTypes::INPUT, msg)
{
}

// --- РЕАЛИЗАЦИЯ НОВЫХ ПУБЛИЧНЫХ МЕТОДОВ ---

std::string InputException::readAndValidateNameField(const std::string &prompt)
{
  while (true) // Цикл до получения корректного ввода
  {
    try
    {
      std::cout << prompt;
      std::string input;
      std::cin >> input;

      if (std::cin.fail())
      {
        // Очищаем состояние ошибки, если был достигнут конец файла
        // (Ctrl+D/Ctrl+Z)
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        throw InputException("Ошибка потока ввода.");
      }

      _validateNoSpecialCharsOrDigits_UTF8(
          input,
          "");      // Имя поля не нужно, т.к. ошибка будет перехвачена здесь же
      return input; // Возвращаем корректное значение
    }
    catch (const InputException &e)
    {
      std::cerr << "[Ошибка ввода]: " << e.GetMessage()
                << " Пожалуйста, попробуйте снова.\n";
    }
  }
}

std::string InputException::readAndValidateDate(const std::string &prompt)
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

      _validateDateFormat(input, "");
      return input;
    }
    catch (const InputException &e)
    {
      std::cerr << "[Ошибка ввода]: " << e.GetMessage()
                << " Пожалуйста, попробуйте снова.\n";
    }
  }
}

std::string InputException::readSingleWord(const std::string &prompt)
{
  std::cout << prompt;
  std::string input;
  std::cin >> input;
  return input;
}

// --- РЕАЛИЗАЦИЯ ПРИВАТНЫХ УТИЛИТ ---

void InputException::_validateNoSpecialCharsOrDigits_UTF8(
    const std::string &input, const std::string &fieldName)
{
  for (size_t i = 0; i < input.length();)
  {
    unsigned char c = input[i];
    size_t char_len = 1;
    if ((c & 0x80) == 0)
    { // ASCII
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

int InputException::_stringToInt(const std::string &s,
                                 const std::string &fieldName)
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
  // Простая реализация достаточна, т.к. мы уже проверили, что это цифры
  return std::stoi(s);
}

void InputException::_validateDateFormat(const std::string &dateStr,
                                         const std::string &fieldName)
{
  if (dateStr.length() != 10 || dateStr[2] != '.' || dateStr[5] != '.')
  {
    throw InputException("Неверный формат даты. Ожидается ДД.ММ.ГГГГ.");
  }
  int day = _stringToInt(dateStr.substr(0, 2), "День");
  int month = _stringToInt(dateStr.substr(3, 2), "Месяц");
  int year = _stringToInt(dateStr.substr(6, 4), "Год");
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
