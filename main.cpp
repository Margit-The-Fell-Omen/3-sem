#include <cstdlib>
#include <iostream>
using namespace std;

class my_string
{
public:
  char *str;
  int len;

  my_string()
  {
    len = 5; // "Empty" length
    str = new char[len + 1];
    strcpy(str, "Empty");
  }

  my_string(const char *value)
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

  void strcpy(char *dest, const char *src)
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

  void print() { cout << str << endl; }

  void append(const char *value)
  {
    if (!value)
      return;

    int value_len = 0;
    while (value[value_len] != '\0')
      ++value_len;

    char *new_str = new char[len + value_len + 1];

    // copy old string
    strcpy(new_str, str);

    // append new value
    strcpy(new_str + len, value);

    // free old memory
    delete[] str;

    // update pointer and length
    str = new_str;
    len += value_len;
  }

  char at(int pos)
  {
    if (pos && pos < len)
    {
      return str[pos];
    }

    cerr << "Out of bounds index";
    exit(1);
  }

  char back() { return str[len - 1]; }

  my_string(const my_string &other) // конструктор копирования
  {
    len = other.len;
    str = new char[len + 1];
    strcpy(str, other.str);
  }

  // Copy assignment operator
  my_string &operator=(const my_string &other)
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

  void clear()
  {
    delete[] str;
    str = new char[1];
    *str = '\0';
    len = 0;
  }

  bool compare(const my_string &str2) const
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

  void copy(const my_string &str2)
  {
    delete[] str; // free old memory

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

    str = new_str; // store pointer to start of allocation
    len = str2.len;
  }

  void resize(int new_size, char fill_char = '\0')
  {
    if (new_size < 0)
    {
      std::cerr << "Negative size not allowed\n";
      return;
    }

    // Allocate new buffer
    char *new_str = new char[new_size + 1];

    // Number of characters to copy from old string
    int copy_len = (new_size < len) ? new_size : len;

    // Copy existing characters
    for (int i = 0; i < copy_len; ++i)
    {
      new_str[i] = str[i];
    }

    // If expanding, fill with fill_char
    for (int i = copy_len; i < new_size; ++i)
    {
      new_str[i] = fill_char;
    }

    // Null-terminate
    new_str[new_size] = '\0';

    // Free old memory
    delete[] str;

    // Update members
    str = new_str;
    len = new_size;
  }

  my_string substr(int start, int num_chars)
  {
    if (start < 0 || start >= len)
    {
      return my_string(""); // or handle error
    }

    if (start + num_chars > len)
    {
      num_chars = len - start; // clamp to available length
    }

    char *new_str = new char[num_chars + 1]; // +1 for '\0'

    for (int i = 0; i < num_chars; i++)
    {
      new_str[i] = str[start + i];
    }
    new_str[num_chars] = '\0'; // null terminate

    my_string new_my_str(new_str);
    delete[] new_str; // free temp buffer, since constructor copies
    return new_my_str;
  }

  int rfind(my_string goal_str)
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
      if (same == goal_str.len - 1)
      {
        return i;
      }
    }
    return -1;
  }

  ~my_string() { delete[] str; }
};

int main()
{
  my_string str;
  str.print();

  my_string str2("aabb");
  str2.print();
  cout << str2.len << endl;

  str2.append("cc");
  str2.print();

  cout << str.compare(str2) << endl;

  cout << str2.at(2) << endl;

  cout << str.back() << endl;

  str.clear();
  str.print();

  str.copy(str2);
  str.print();

  str.resize(8, 'e');
  str.print();

  str2 = str.substr(2, 2);
  str2.print();

  cout << str.rfind(str2) << endl;

  return 0;
}
