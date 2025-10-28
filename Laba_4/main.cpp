#include "functions.h"
#include <iostream>
#include <limits>

int main()
{
  BinTree<Member_of_commision> memberTree;
  BinTree<Prepod> prepodTree;
  BinTree<Prepod_from_commision> prepodMemberTree;

  int mainChoice;

  std::cout << "=== Система управления бинарными деревьями ===\n";

  while (true)
  {
    std::cout << "\nГлавное меню:\n";
    std::cout << "1. Работа с деревом Member_of_commision\n";
    std::cout << "2. Работа с деревом Prepod\n";
    std::cout << "3. Работа с деревом Prepod_from_commision\n";
    std::cout << "4. Выход\n";
    std::cout << "Введите ваш выбор: ";

    if (!(std::cin >> mainChoice))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Неверный ввод. Пожалуйста, введите число.\n";
      continue;
    }

    switch (mainChoice)
    {
    case 1:
      handleTreeOperations(memberTree, "Member_of_commision");
      break;
    case 2:
      handleTreeOperations(prepodTree, "Prepod");
      break;
    case 3:
      handleTreeOperations(prepodMemberTree, "Prepod_from_commision");
      break;
    case 4:
      std::cout << "Выход из программы.\n";
      return 0;
    default:
      std::cout << "Неверный выбор. Пожалуйста, введите число от 1 до 4.\n";
    }
  }
}
