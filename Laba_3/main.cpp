#include "Human.h"
#include <iostream>

int main(int argc, char *argv[])
{
  std::cout << "Human entering:" << std::endl;
  Human first();
  Human second("a", "b", "10.10.2000");
  Human third = second;
  std::cout << first << std::endl << second << std::endl << third << std::endl;
  return 0;
}
