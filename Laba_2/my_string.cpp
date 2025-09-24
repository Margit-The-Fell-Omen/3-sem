#include "my_string.h"
#include <cstring>
#include <iostream>

// ------ Конструкторы, операторы и деструктор класса my_string ------

my_string::my_string() // конструктор без параметров
{
  len = 0;
  str = new char[1];
  *str = '\0';
}

my_string::my_string(const char *value) // конструктор с параметром
{
  if (!value) {
    len = 0;
    str = new char[1];
    str[0] = '\0';
  } 
  else 
  {
    len = get_char_count(value);
    int byte_len = strlen(value);
    str = new char[byte_len + 1];
    strcpy(str, value);
  }
}

my_string::my_string(const my_string &other) // конструктор копирования
{
  len = other.len;
  int byte_len = strlen(other.str);
  str = new char[byte_len + 1];
  strcpy(str, other.str);
}

my_string::~my_string() { delete[] str; } // деструктор

// ------ Вспомогательные функции для работы с UTF-8 ------

/**
 * @brief Проверяет, является ли байт продолжением символа UTF-8.
 * @param c Байт для проверки.
 * @return true, если байт имеVет вид 10xxxxxx.
 */
bool my_string::is_continuation_byte(char c) { return (c & 0xC0) == 0x80; }

/**
 * @brief Считает количество символов в строке UTF-8.
 * @param s Нуль-терминированная строка.
 * @return Количество символов.
 */
int my_string::get_char_count(const char *s) 
{
  int count = 0;
  if (!s)
    return 0;
  while (*s != '\0') 
  {
    if (!is_continuation_byte(*s)) 
    {
      count++;
    }
    s++;
  }
  return count;
}

/**
 * @brief Находит позицию байта, с которого начинается символ с заданным
 * индексом.
 * @param char_pos Индекс символа.
 * @return Индекс байта. Возвращает -1, если индекс символа вне диапазона.
 */
int my_string::get_byte_pos_by_char_pos(int char_pos) const 
{
  if (char_pos < 0 || char_pos > len)
    return -1;
  if (char_pos == len)
    return strlen(str);

  int current_char_count = 0;
  int byte_pos = 0;

  while (str[byte_pos] != '\0') 
  {
    if (current_char_count == char_pos &&
        !is_continuation_byte(str[byte_pos])) 
    {
      return byte_pos;
    }
    if (!is_continuation_byte(str[byte_pos]))
    {
      current_char_count++;
    }
    byte_pos++;
  }
  return byte_pos;
}

/**
 * @brief Находит индекс символа, который начинается с указанной позиции байта.
 * @param byte_pos Индекс байта.
 * @return Индекс символа. Возвращает -1, если позиция байта некорректна.
 */
int my_string::get_char_pos_by_byte_pos(int byte_pos) const 
{
  int byte_len = strlen(str);
  if (byte_pos < 0 || byte_pos > byte_len)
    return -1;

  int char_count = 0;
  for (int i = 0; i < byte_pos; i++) 
  {
    if (!is_continuation_byte(str[i])) 
    {
      char_count++;
    }
  }
  return char_count;
}

// ------ Перегрузки операторов класса my_string ------

my_string &my_string::operator=(const my_string &other)         // перегрузка оператора присваивания
{
  if (this != &other) 
  {
    delete[] str;
    len = other.len;
    int byte_len = strlen(other.str);
    str = new char[byte_len + 1];
    strcpy(str, other.str);
  }
  return *this;
}

my_string my_string::operator+(const my_string &other) const    // перегрузка оператора +
{
  if (!other.str) 
  {
    return *this;
  }

  int value_char_len = get_char_count(other.str);
  int value_byte_len = strlen(other.str);
  int old_byte_len = strlen(this->str);

  char *new_str = new char[old_byte_len + value_byte_len + 1];

  memcpy(new_str, this->str, old_byte_len);
  memcpy(new_str + old_byte_len, other.str, value_byte_len);
  new_str[old_byte_len + value_byte_len] = '\0';

  my_string result;
  result.str = new_str;
  result.len = this->len + value_char_len;

  return result;
}

my_string &my_string::operator+=(const my_string &other)        // перегрузка оператора +=
{
  if (!other.str) 
  {
    return *this;
  }

  // int value_char_len = get_char_count(other.str);
  // int value_byte_len = strlen(other.str);
  // int old_byte_len = strlen(this->str);

  // char *new_str = new char[old_byte_len + value_byte_len + 1];

  // memcpy(new_str, this->str, old_byte_len);
  // memcpy(new_str + old_byte_len, other.str, value_byte_len);
  // new_str[old_byte_len + value_byte_len] = '\0';

  // delete[] str;
  // this->str = new_str;
  // this->len += value_char_len;
  *this = *this + other;
  return *this;
}

bool my_string::operator==(const my_string &other) const        // перегрузка оператора ==
{
  return strcmp(this->str, other.str) == 0;
}

bool my_string::operator<(const my_string &other) const         // перегрузка оператора >
{
  return strcmp(this->str, other.str) < 0;
}

bool my_string::operator>(const my_string &other) const         // перегрузка оператора <
{
  return strcmp(this->str, other.str) > 0;
}

char &my_string::operator[](int index)                          // перегрузка оператора [] 
{
  if (index < 0 || index >= len) 
  {
    throw std::out_of_range("Index out of range");
  }
  return str[index];
}

const char &my_string::operator[](int index) const              // перегрузка оператора [] для read-only
{
  if (index < 0 || index >= len) 
  {
    throw std::out_of_range("Index out of range");
  }
  return str[index];
}

my_string my_string::operator()(int start, int end) const       // перегрузка оператора ()
{
  if (start < 0 || end > len || start > end) 
  {
    return my_string("");
  }

  int sub_len = end - start;
  char *sub_str = new char[sub_len + 1];

  for (int i = 0; i < sub_len; ++i) 
  {
    sub_str[i] = this->str[start + i];
  }
  sub_str[sub_len] = '\0';

  my_string result(sub_str);
  delete[] sub_str;
  return result;
}

std::ostream &operator<<(std::ostream &os, const my_string &s)  // перегрузка оператора <<
{
  os << s.str;
  return os;
}

std::istream &operator>>(std::istream &is, my_string &s)        // перегрузка оператора >>
{
  std::string temp;
  is >> temp;

  s = my_string(temp.c_str());

  return is;
}

// ------ Методы класса my_string ------

void my_string::print() { std::cout << str; }         // функция вывода строки

const char *my_string::string() const { return str; } // функция получения строки

int my_string::length() const { return len; }         // функция получения длины строки в символах

int my_string::byte_length() const                    // функция получения длины строки в байтах
{
  return strlen(str);
}
