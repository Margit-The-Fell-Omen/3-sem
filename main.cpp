#include "header.h"
#include <iostream>

int main()
{
  my_string str;
  str.print();

  std::cout << str.empty() << std::endl;

  my_string str2("aabb");
  str2.print();
  std::cout << str2.len << std::endl;

  str2.append("cc");
  str2.print();

  std::cout << str.compare(str2) << std::endl;

  std::cout << str2.at(2) << std::endl;

  std::cout << str.back() << std::endl;

  str.clear();
  str.print();

  str.copy(str2);
  str.print();

  str.resize(8, 'e');
  str.print();

  str2 = str.substr(2, 2);
  str2.print();

  std::cout << str.rfind(str2) << std::endl;

  std::cout << str.find(str2) << std::endl;
  str.replace(1, 1, str2);
  str.print();

  str.pop_back();
  str.print();

  str.push_back(str2);
  str.print();
  str.erase(1, 2);
  str.print();
  return 0;
}
