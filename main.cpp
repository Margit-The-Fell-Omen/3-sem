#include <iostream>

using namespace std;

class my_string
{
public:
  char *str;
  int len;

  my_string() { str = new char[6]{"Empty"}; }

  my_string(const char *value)
  {
    while (*value != '\0' || *value)
    {
      ++len;
    }
    str = new char[len + 1];
    str = my_strcpy(str, value);
  }

  char *my_strcpy(char *dest, const char *src)
  {
    char *res = dest;
    while (*src != '\0')
    {
      *dest = *src;
      ++dest;
      ++src;
    }
    *dest = '\0';
    return res;
  }

  void print() { cout << str << endl; }

  ~my_string() { free(str); }
};

int main()
{
  my_string str;
  str.print();
  my_string str2("aabb");
  str2.print();
  cout << str2.len << endl;
  return 0;
}
