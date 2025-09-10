#include <iostream>

class my_string // класс строковых переменных
{
public:
  char *str; // динамический массив символов
  int len;   // длина строки

  my_string() // конструктор без параметров
  {
    len = 0;
    str = new char[1];
    *str = '\0';
  }

  my_string(const char *value) // конструктор с параметром
  {
    len = 0;
    const char *src = value;
    while (*value != '\0')
    {
      ++len;
      ++value;
    }
    str = new char[len + 1];
    strcpy(str, src);
  }

  void strcpy(char *dest,
              const char *src) // вспомогательная функция копирования массива
                               // символов в массив символов
  {
    char *res = dest;
    while (*src != '\0')
    {
      *dest = *src;
      ++dest;
      ++src;
    }
    *dest = '\0';
  }

  void print()
  {
    std::cout << str << std::endl;
  } // функция вывода строки в терминал

  void append(
      const char *value) // функция добавления массива символов в конец строки
  {
    if (!value)
      return;

    int value_len = 0;
    while (value[value_len] != '\0')
      ++value_len;

    char *new_str = new char[len + value_len + 1];

    strcpy(new_str, str);

    strcpy(new_str + len, value);

    delete[] str;

    str = new_str;
    len += value_len;
  }

  char at(int pos) // функция получения символа в строке по индексу
  {
    if (pos && pos < len)
    {
      return str[pos];
    }

    std::cerr << "Out of bounds index";
    exit(1);
  }

  char back()
  {
    return str[len - 1];
  } // функция получения последнего символа строки (который не является '\0')

  my_string(const my_string &other) // конструктор копирования
  {
    len = other.len;
    str = new char[len + 1];
    strcpy(str, other.str);
  }

  my_string &operator=(const my_string &other) // перегрузка оператора &
  {
    if (this != &other)
    {
      delete[] str;
      len = other.len;
      str = new char[len + 1];
      strcpy(str, other.str);
    }
    return *this;
  }

  void clear() // функция очистки строки
  {
    delete[] str;
    str = new char[1];
    *str = '\0';
    len = 0;
  }

  bool compare(const my_string &str2) const // функция сравнения 2 строк
  {
    const char *iter1 = str;
    const char *iter2 = str2.str;

    while (*iter1 != '\0' && *iter2 != '\0')
    {
      if (*iter1 != *iter2)
        return false;
      ++iter1;
      ++iter2;
    }
    return (*iter1 == '\0' && *iter2 == '\0');
  }

  void copy(const my_string &str2) // функция копирования строки
  {
    delete[] str;

    char *new_str = new char[str2.len + 1];
    const char *src = str2.str;
    char *dest = new_str;

    while (*src != '\0')
    {
      *dest = *src;
      ++dest;
      ++src;
    }
    *dest = '\0';

    str = new_str;
    len = str2.len;
  }

  void resize(int new_size,
              char fill_char = '\0') // функция изменения размера строки
  {
    if (new_size < 0)
    {
      std::cerr << "Negative size not allowed\n";
      return;
    }

    char *new_str = new char[new_size + 1];

    int copy_len = (new_size < len) ? new_size : len;

    for (int i = 0; i < copy_len; ++i)
    {
      new_str[i] = str[i];
    }

    for (int i = copy_len; i < new_size; ++i)
    {
      new_str[i] = fill_char;
    }

    new_str[new_size] = '\0';

    delete[] str;

    str = new_str;
    len = new_size;
  }

  my_string substr(int start,
                   int num_chars) // функция получения подстроки из строки
  {
    if (start < 0 || start >= len)
    {
      return my_string("");
    }

    if (start + num_chars > len)
    {
      num_chars = len - start;
    }

    char *new_str = new char[num_chars + 1]; // +1 для '\0'

    for (int i = 0; i < num_chars; i++)
    {
      new_str[i] = str[start + i];
    }
    new_str[num_chars] = '\0';

    my_string new_my_str(new_str);
    delete[] new_str;
    return new_my_str;
  }

  int rfind(my_string goal_str) // функция обратного поиска
  {
    const char *goal = goal_str.str;
    int check_len = len - goal_str.len;
    for (int i = check_len; i > 0; i--)
    {
      int same = 0;
      for (int j = i, k = 0; j < len - (check_len - i); k++, j++)
      {
        if (str[j] == goal[k])
        {
          ++same;
        }
      }
      if (same == goal_str.len)
      {
        return i;
      }
    }
    return -1;
  }

  int find(my_string goal_str) // функция прямого поиска
  {
    const char *goal = goal_str.str;
    int check_len = len - goal_str.len;
    for (int i = 0; i < check_len; i++)
    {
      int same = 0;
      for (int j = i, k = 0; j < i + check_len; k++, j++)
      {
        if (str[j] == goal[k])
        {
          ++same;
        }
      }
      if (same == goal_str.len)
      {
        return i;
      }
    }
    return -1;
  }

  void replace(int start, int num_chars,
               my_string src_str) // функция замены подстроки заданного размера
                                  // другой строкой
  {
    if (!start || start > len)
    {
      return;
    }
    const char *src = src_str.str;
    int new_len = src_str.len + len - num_chars;
    char *new_str = new char[new_len + 1];
    for (int i = 0; i < len; i++)
    {
      if (i != start)
      {
        new_str[i] = str[i];
      }
      else
      {
        for (int j = 0; j < num_chars; j++)
        {
          new_str[start + j] = src[j];
        }
      }
    }
    delete[] str;
    str = new_str;
  }

  bool empty()
  {
    return (*str != '\0' && len != 0) ? false : true;
  } // функция проверки строки на пустоту

  char pop_back() // функция удаления последнего символа строки
  {
    char deleted = str[len - 1];
    char *new_str = new char[len];
    for (int i = 0; i < len - 1; i++)
    {
      new_str[i] = str[i];
    }
    new_str[--len] = '\0';
    delete[] str;
    str = new_str;
    return deleted;
  }

  void push_back(
      my_string src) // функция добавления другой строки в конец этой строки
  {
    char deleted = str[len + 1];
    char *new_str = new char[len];
    for (int i = 0; i < len; i++)
    {
      new_str[i] = str[i];
    }
    int new_len = len + src.len;
    for (int i = len; i < new_len; i++)
    {
      new_str[i] = src.str[i - len];
    }
    new_str[new_len] = '\0';
    delete[] str;
    str = new_str;
    len = new_len;
  }

  void erase(int start, int num_chars)
  {
    if (!start || start > len)
    {
      return;
    }
    int new_len = len - num_chars;
    char *new_str = new char[new_len + 1];
    for (int i = 0; i < new_len; i++)
    {
      if (i <= start)
      {
        new_str[i] = str[i];
      }
      else
      {
        new_str[i] = str[i + num_chars];
      }
    }
    delete[] str;
    str = new_str;
  }
  ~my_string() { delete[] str; } // деструктор класса
};
