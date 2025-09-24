#ifndef MY_STRING_H
#define MY_STRING_H

class my_string   // класс строковых переменных
{
  char *str;      // динамический массив символов (байтов)
  int len;        // длина строки в символах (не в байтах)

public:
  my_string();                                      // конструктор без параметров
  my_string(const char *value);                     // конструктор с параметром
  my_string(const my_string &other);                // конструктор копирования
  ~my_string();                                     // деструктор класса
  my_string& operator=(const my_string &other);     // перегрузка оператора присваивания

  void print();                                     // функция вывода строки
  const char* string() const;                       // функция получения строки
  int length() const;                               // функция получения длины строки в символах
  int byte_length() const;                          // функция получения длины строки в байтах
  void append(const char *value);                   // функция записи подстроки в конец строки
  my_string at(int pos);                            // функция получения СИМВОЛА строки по индексу
  my_string back();                                 // функция получения последнего СИМВОЛА строки
  void clear();                                     // функция очистки строки
  bool compare(const my_string &str2) const;        // функция сравнения строки
  void copy(const my_string &str2);                 // функция копирования строки
  bool empty();                                     // функция проверки строки на пустоту
  void erase(int start, int num_chars);             // функция удаления подстроки из строки
  int find(my_string goal_str);                     // функция прямого поиска в строке
  void insert(int start,
              my_string src_string);                // функция записи подстроки в строку
  my_string pop_back();                             // функция удаления последнего символа строки
  void push_back(my_string src);                    // функция записи строки в конец строки
  void replace(int start, int num_chars,
               my_string src_str);                  // функция замены подстроки строкой
  void resize(int new_size,
              const char* fill_str = "\0");         // функция изменения размера строки
  int rfind(my_string goal_str);                    // функция обратного поиска в строке
  my_string substr(int start,
                   int num_chars);                  // функция получения подстроки из строки

private:
  void strcpy(char *dest, const char *src);                     // локальная реализация функции strcpy
  int strlen(const char *s) const;                              // локальная реализация функции strlen
  int strcmp(const char *s1, const char *s2) const;             // локальная реализация функции strcmp
  char* strstr(const char *haystack, const char *needle) const; // локальная реализация функции strstr
  void memcpy(char *dest, const char *src, int n) const;        // локальная реализация функции memcpy
  int memcmp(const char *s1, const char *s2, int n) const;      // локальная реализация функции memcmp

  static int get_char_count(const char *s);         // функция подсчёта количества символов в строке UTF-8
  int get_byte_pos_by_char_pos(int char_pos) const; // функция нахождения начального байта символа по его индексу
  int get_char_pos_by_byte_pos(int byte_pos) const; // функция нахождения индекса символа по его начальному байту
};

void menu(); // функция меню для тестирования работы класса
#endif       // MY_STRING_H