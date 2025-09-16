#include "my_string.h"
#include <iostream>
#include <cstdlib>

// ------ Конструкторы, деструктор класса my_string ------

my_string::my_string()                                  // конструктор без параметров
{
  len = 0;
  str = new char[1];
  *str = '\0';
}

my_string::my_string(const char *value)                 // конструктор с параметром
{
  if (!value)
  {
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

my_string::my_string(const my_string &other)            // конструктор копирования
{
  len = other.len;
  int byte_len = strlen(other.str);
  str = new char[byte_len + 1];
  strcpy(str, other.str);
}

my_string::~my_string() { delete[] str; }               // деструктор

my_string& my_string::operator=(const my_string &other) // перегрузка оператора присваивания
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

// ------ Локальная имплементация некоторых функций из <string.h> ------

void my_string::strcpy(char *dest, const char *src)
{
  while (*src != '\0')
  {
    *dest = *src;
    ++dest;
    ++src;
  }
  *dest = '\0';
}

int my_string::strlen(const char *s) const
{
  if (!s) return 0;
  int length = 0;
  while (s[length] != '\0')
  {
    length++;
  }
  return length;
}

int my_string::strcmp(const char *s1, const char *s2) const
{
  while (*s1 && (*s1 == *s2))
  {
    s1++;
    s2++;
  }
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

char* my_string::strstr(const char *haystack, const char *needle) const
{
  if (!*needle) return (char*)haystack;
  
  for (int i = 0; haystack[i] != '\0'; i++)
  {
    int j = 0;
    while (needle[j] != '\0' && haystack[i + j] == needle[j])
    {
      j++;
    }
    if (needle[j] == '\0')
    {
      return (char*)(haystack + i);
    }
  }
  return nullptr;
}

void my_string::memcpy(char *dest, const char *src, int n) const
{
  for (int i = 0; i < n; i++)
  {
    dest[i] = src[i];
  }
}

int my_string::memcmp(const char *s1, const char *s2, int n) const
{
  for (int i = 0; i < n; i++)
  {
    if (s1[i] != s2[i])
    {
      return s1[i] - s2[i];
    }
  }
  return 0;
}

// ------ Вспомогательные функции для работы с UTF-8 ------

/**
 * @brief Проверяет, является ли байт продолжением символа UTF-8.
 * @param c Байт для проверки.
 * @return true, если байт имеет вид 10xxxxxx.
 */
static bool is_continuation_byte(char c) { return (c & 0xC0) == 0x80; }

/**
 * @brief Считает количество символов в строке UTF-8.
 * @param s Нуль-терминированная строка.
 * @return Количество символов.
 */
int my_string::get_char_count(const char *s)
{
  int count = 0;
  if (!s) return 0;
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
  if (char_pos < 0 || char_pos > len) return -1;
  if (char_pos == len) return strlen(str);

  int current_char_count = 0;
  int byte_pos = 0;
  
  while (str[byte_pos] != '\0')
  {
    if (current_char_count == char_pos && !is_continuation_byte(str[byte_pos]))
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
  if (byte_pos < 0 || byte_pos > byte_len) return -1;

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

// ------ Public методы класса my_string ------

void my_string::print() { std::cout << str; }         // функция вывода строки

const char* my_string::string() const { return str; } // функция получения строки

int my_string::length() const { return len; }         // функция получения длины строки в символах

int my_string::byte_length() const                    // функция получения длины строки в байтах 
{ 
  return strlen(str); 
}

void my_string::append(const char *value)             // функция записи подстроки в конец строки
{
  if (!value) return;

  int value_char_len = get_char_count(value);
  int value_byte_len = strlen(value);
  int old_byte_len = strlen(str);

  char *new_str = new char[old_byte_len + value_byte_len + 1];

  memcpy(new_str, str, old_byte_len);
  memcpy(new_str + old_byte_len, value, value_byte_len);
  new_str[old_byte_len + value_byte_len] = '\0';

  delete[] str;
  str = new_str;
  len += value_char_len;
}

my_string my_string::at(int pos)                // функция получения СИМВОЛА строки по индексу
{
  if (pos < 0 || pos >= len)
  {
    std::cerr << "Out of bounds index\n";
    exit(1);
  }
  int byte_start = get_byte_pos_by_char_pos(pos);
  int byte_next = get_byte_pos_by_char_pos(pos + 1);
  int char_byte_len = byte_next - byte_start;

  char *temp = new char[char_byte_len + 1];
  memcpy(temp, str + byte_start, char_byte_len);
  temp[char_byte_len] = '\0';

  my_string result(temp);
  delete[] temp;
  return result;
}

my_string my_string::back()                     // функция получения последнего СИМВОЛА строки
{
  if (len == 0)
  {
    std::cerr << "Back on empty string\n";
    exit(1);
  }
  return at(len - 1);
}

void my_string::clear()                         // функция очистки строки
{
  delete[] str;
  str = new char[1];
  str[0] = '\0';
  len = 0;
}

bool my_string::compare(const my_string &str2) const        // функция сравнения строки
{
  return strcmp(str, str2.str) == 0;
}

void my_string::copy(const my_string &str2)                 // функция копирования строки
{
  delete[] str;
  len = str2.len;
  int byte_len = strlen(str2.str);
  str = new char[byte_len + 1];
  strcpy(str, str2.str);
}

void my_string::resize(int new_size, const char* fill_str)  // функция изменения размера строки
{
  if (new_size < 0)
  {
    std::cerr << "Отрицательная длина строки не разрешена\n";
    return;
  }

  if (new_size == len)
    return;

  if (new_size < len)
  {
    int byte_pos = get_byte_pos_by_char_pos(new_size);
    char *new_str = new char[byte_pos + 1];
    memcpy(new_str, str, byte_pos);
    new_str[byte_pos] = '\0';
    delete[] str;
    str = new_str;
    len = new_size;
  }
  else
  { // new_size > len - увеличение размера с UTF-8 строкой
    int chars_to_add = new_size - len;
    
    if (!fill_str || fill_str[0] == '\0')
    {
      fill_str = " ";
    }
    
    // Получаем информацию о fill строке
    int fill_char_len = get_char_count(fill_str);
    int fill_byte_len = strlen(fill_str);
    
    if (fill_char_len == 0)
    {
      fill_str = " "; // на случай если fill_str содержит только continuation bytes
      fill_char_len = 1;
      fill_byte_len = 1;
    }
    
    int old_byte_len = strlen(str);
    
    // Вычисляем сколько раз нужно повторить fill_str
    int repeat_count = (chars_to_add + fill_char_len - 1) / fill_char_len; // округление вверх
    int new_byte_len = old_byte_len + (repeat_count * fill_byte_len);
    
    char *new_str = new char[new_byte_len + 1];
    
    // Копируем оригинальную строку
    memcpy(new_str, str, old_byte_len);
    
    // Добавляем fill строку нужное количество раз
    int current_byte_pos = old_byte_len;
    int chars_added = 0;
    
    while (chars_added < chars_to_add)
    {
      memcpy(new_str + current_byte_pos, fill_str, fill_byte_len);
      current_byte_pos += fill_byte_len;
      chars_added += fill_char_len;
    }
    
    new_str[new_byte_len] = '\0';
    delete[] str;
    str = new_str;
    len = new_size;
  }
}

my_string my_string::substr(int start, int num_chars)       // функция получения подстроки из строки
{
  if (start < 0 || start >= len || num_chars <= 0)
  {
    return my_string("");
  }
  if (start + num_chars > len)
  {
    num_chars = len - start;
  }

  int byte_start = get_byte_pos_by_char_pos(start);
  int byte_end = get_byte_pos_by_char_pos(start + num_chars);
  int sub_byte_len = byte_end - byte_start;

  char *temp = new char[sub_byte_len + 1];
  memcpy(temp, str + byte_start, sub_byte_len);
  temp[sub_byte_len] = '\0';

  my_string result(temp);
  delete[] temp;
  return result;
}

int my_string::rfind(my_string goal_str)                    // функция обратного поиска в строке
{
  if (goal_str.len == 0)
    return len;
  if (len < goal_str.len)
    return -1;

  int goal_byte_len = strlen(goal_str.str);
  int current_byte_len = strlen(str);

  for (int i = current_byte_len - goal_byte_len; i >= 0; --i)
  {
    if (memcmp(str + i, goal_str.str, goal_byte_len) == 0)
    {
      if (i == 0 || !is_continuation_byte(str[i]))
      {
        return get_char_pos_by_byte_pos(i);
      }
    }
  }
  return -1;
}

int my_string::find(my_string goal_str)                     // функция прямого поиска в строке
{
  if (goal_str.len == 0)
    return 0;
  if (len < goal_str.len)
    return -1;

  char *found_byte_pos = strstr(str, goal_str.str);
  if (found_byte_pos)
  {
    int byte_index = found_byte_pos - str;
    return get_char_pos_by_byte_pos(byte_index);
  }
  return -1;
}

void my_string::replace(int start, int num_chars, 
                        my_string src_str)                  // функция замены подстроки строкой
{
  if (start < 0 || start > len || num_chars < 0 || start + num_chars > len)
  {
    return;
  }

  my_string first_part = substr(0, start);
  my_string second_part = substr(start + num_chars, len - (start + num_chars));

  clear();
  append(first_part.str);
  append(src_str.str);
  append(second_part.str);
}

bool my_string::empty() { return len == 0; }                // функция проверки строки на пустоту

my_string my_string::pop_back()                             // функция удаления последнего СИМВОЛА строки
{
  if (len == 0)
  {
    std::cerr << "Pop_back on empty string\n";
    exit(1);
  }
  my_string last_char = back();

  int byte_pos = get_byte_pos_by_char_pos(len - 1);
  char *new_str = new char[byte_pos + 1];
  memcpy(new_str, str, byte_pos);
  new_str[byte_pos] = '\0';

  delete[] str;
  str = new_str;
  len--;

  return last_char;
}

void my_string::push_back(my_string src) { append(src.str); } // функция записи строки в конец строки

void my_string::erase(int start, int num_chars)                     // функция удаления подстроки из строки
{
  if (start < 0 || start >= len || num_chars <= 0) return;
  if (start + num_chars > len) num_chars = len - start;

  // Find exact byte positions for UTF-8 characters
  int byte_start = get_byte_pos_by_char_pos(start);
  int byte_end = get_byte_pos_by_char_pos(start + num_chars);
  
  int old_byte_len = strlen(str);
  int bytes_to_remove = byte_end - byte_start;
  int new_byte_len = old_byte_len - bytes_to_remove;

  char *new_str = new char[new_byte_len + 1];

  // Copy part before the deletion
  if (byte_start > 0)
  {
    memcpy(new_str, str, byte_start);
  }

  // Copy part after the deletion
  if (byte_end < old_byte_len)
  {
    memcpy(new_str + byte_start, str + byte_end, old_byte_len - byte_end);
  }

  new_str[new_byte_len] = '\0';

  delete[] str;
  str = new_str;
  len -= num_chars;
}

void my_string::insert(int start, my_string src_str)                // функция записи подстроки в строку
{
  if (start < 0 || start > len)
    return;

  int byte_pos = get_byte_pos_by_char_pos(start);
  int src_byte_len = strlen(src_str.str);
  int old_byte_len = strlen(str);
  int new_byte_len = old_byte_len + src_byte_len;

  char *new_str = new char[new_byte_len + 1];

  // Копируем часть до вставки
  memcpy(new_str, str, byte_pos);
  // Копируем вставляемую строку
  memcpy(new_str + byte_pos, src_str.str, src_byte_len);
  // Копируем остаток старой строки
  memcpy(new_str + byte_pos + src_byte_len, str + byte_pos,
         old_byte_len - byte_pos + 1);

  delete[] str;
  str = new_str;
  len += src_str.len;
}

// ------ Меню для тестирования ------

void menu()
{
  my_string s("тест");

  int choice;
  do
  {
    std::cout << "\n===== Меню тестирования класса my_string =====\n";
    std::cout << "Текущая строка: \"";
    s.print();
    std::cout << "\"\n";
    std::cout << "Длина (в символах): " << s.length() << "\n";
    std::cout << "Длина (в байтах): " << (s.byte_length()) << "\n";

    std::cout << "\nВыберите опцию:\n";
    std::cout << " 1. Присвоить из C-строки\n";
    std::cout << " 2. Добавить C-строку в конец (append)\n";
    std::cout << " 3. Добавить my_string в конец (push_back)\n";
    std::cout << " 4. Получить символ по индексу (at)\n";
    std::cout << " 5. Получить последний символ (back)\n";
    std::cout << " 6. Очистить строку (clear)\n";
    std::cout << " 7. Сравнить с другой my_string (compare)\n";
    std::cout << " 8. Скопировать из другой my_string (copy)\n";
    std::cout << " 9. Изменить размер (resize)\n";
    std::cout << "10. Получить подстроку (substr)\n";
    std::cout << "11. Найти подстроку (find)\n";
    std::cout << "12. Найти подстроку с конца (rfind)\n";
    std::cout << "13. Заменить подстроку (replace)\n";
    std::cout << "14. Проверить на пустоту (empty)\n";
    std::cout << "15. Удалить последний символ (pop_back)\n";
    std::cout << "16. Удалить подстроку (erase)\n";
    std::cout << "17. Вставить подстроку (insert)\n";
    std::cout << " 0. Выход\n";
    std::cout << "Ваш выбор: ";
    std::cin >> choice;

    if (!std::cin)
    {
      std::cin.clear();
      std::cin.ignore(10000, '\n');
      continue;
    }

    std::cin.ignore(10000, '\n');

    switch (choice)
    {
    case 1:
    {
      std::cout << "Введите C-строку: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      s = my_string(buf);
      break;
    }
    case 2:
    {
      std::cout << "Введите C-строку для добавления: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      s.append(buf);
      break;
    }
    case 3:
    {
      std::cout << "Введите строку для добавления: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      my_string temp(buf);
      s.push_back(temp);
      break;
    }
    case 4:
    {
      int idx;
      std::cout << "Введите индекс: ";
      std::cin >> idx;
      std::cin.ignore(10000, '\n');
      std::cout << "Символ: ";
      s.at(idx).print();
      std::cout << "\n";
      break;
    }
    case 5:
      std::cout << "Последний символ: ";
      s.back().print();
      std::cout << "\n";
      break;
    case 6:
      s.clear();
      std::cout << "Строка очищена.\n";
      break;
    case 7:
    {
      std::cout << "Введите строку для сравнения: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      my_string temp(buf);
      std::cout << (s.compare(temp) ? "Равны\n" : "Не равны\n");
      break;
    }
    case 8:
    {
      std::cout << "Введите строку для копирования: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      my_string temp(buf);
      s.copy(temp);
      break;
    }
    case 9:
    {
      int new_size;
      char fill_str[1024];
      std::cout << "Введите новый размер: ";
      std::cin >> new_size;
      std::cout << "Введите символ-заполнитель: ";
      std::cin >> fill_str;
      std::cin.ignore(10000, '\n');
      s.resize(new_size, fill_str);
      break;
    }
    case 10:
    {
      int start, num;
      std::cout << "Введите начальный индекс: ";
      std::cin >> start;
      std::cout << "Введите количество символов: ";
      std::cin >> num;
      std::cin.ignore(10000, '\n');
      my_string sub = s.substr(start, num);
      std::cout << "Подстрока: ";
      sub.print();
      std::cout << "\n";
      break;
    }
    case 11:
    {
      std::cout << "Введите подстроку для поиска: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      my_string temp(buf);
      std::cout << "Найдено по индексу: " << s.find(temp) << "\n";
      break;
    }
    case 12:
    {
      std::cout << "Введите подстроку для поиска с конца: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      my_string temp(buf);
      std::cout << "Найдено по индексу: " << s.rfind(temp) << "\n";
      break;
    }
    case 13:
    {
      int start, num;
      std::cout << "Введите начальный индекс: ";
      std::cin >> start;
      std::cout << "Введите количество символов для замены: ";
      std::cin >> num;
      std::cin.ignore(10000, '\n');
      std::cout << "Введите строку для замены: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      my_string temp(buf);
      s.replace(start, num, temp);
      break;
    }
    case 14:
      std::cout << (s.empty() ? "Строка пуста\n" : "Строка не пуста\n");
      break;
    case 15:
      std::cout << "Удалённый символ: ";
      s.pop_back().print();
      std::cout << "\n";
      break;
    case 16:
    {
      int start, num;
      std::cout << "Введите начальный индекс: ";
      std::cin >> start;
      std::cout << "Введите количество символов для удаления: ";
      std::cin >> num;
      std::cin.ignore(10000, '\n');
      s.erase(start, num);
      break;
    }
    case 17:
    {
      int start;
      std::cout << "Введите начальный индекс: ";
      std::cin >> start;
      std::cin.ignore(10000, '\n');
      std::cout << "Введите строку для вставки: ";
      char buf[1024];
      std::cin.getline(buf, 1024);
      my_string temp(buf);
      s.insert(start, temp);
      break;
    }
    case 0:
      std::cout << "Выход...\n";
      break;
    default:
      std::cout << "Неверный выбор.\n";
    }
  } while (choice != 0);
}