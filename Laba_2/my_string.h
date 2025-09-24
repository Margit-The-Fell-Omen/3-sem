#ifndef MY_STRING_H
#define MY_STRING_H
#include <iostream>

class my_string // класс строковых переменных
{
  char *str;    // динамический массив символов (байтов)
  int len;      // длина строки в символах (не в байтах)

public:
  my_string();                       // конструктор без параметров
  my_string(const char *value);      // конструктор с параметром
  my_string(const my_string &other); // конструктор копирования
  ~my_string();                      // деструктор класса
  
  my_string &operator=(const my_string &other);                           // перегрузка оператора присваивания
  my_string operator+(const my_string &other) const;                      // перегрузка оператора +
  my_string &operator+=(const my_string &other);                          // перегрузка оператора +=
  bool operator==(const my_string &other) const;                          // перегрузка оператора ==
  bool operator>(const my_string &other) const;                           // перегрузка оператора >
  bool operator<(const my_string &other) const;                           // перегрузка оператора <
  char &operator[](int index);                                            // перегрузка оператора [] 
  const char &operator[](int index) const;                                // перегрузка оператора [] для read-only
  my_string operator()(int start, int end) const;                         // перегрузка оператора ()

  friend std::ostream &operator<<(std::ostream &os, const my_string &s);  // перегрузка оператора <<
  friend std::istream &operator>>(std::istream &is, my_string &s);        // перегрузка оператора >>

  void print();               // функция вывода строки
  const char *string() const; // функция получения строки
  int length() const;         // функция получения длины строки в символах
  int byte_length() const;    // функция получения длины строки в байтах


private:
  static bool is_continuation_byte(char c);         // функция проверки на продолжающий символ
  static int get_char_count(const char *s);         // функция подсчёта количества символов в строке UTF-8
  int get_byte_pos_by_char_pos(int char_pos) const; // функция нахождения начального байта символа по его индексу
  int get_char_pos_by_byte_pos(int byte_pos) const; // функция нахождения индекса символа по его начальному байту
};

#endif       // MY_STRING_H
