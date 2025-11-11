#include "BinTree.h"
#include "Interface.h"
#include "Member_of_commision.h"
#include "Prepod.h"
#include "Prepod_from_commision.h"
#include <iostream>

// TODO:  add overrides to iterators maybe and thats kinda it)

int main()
{
  // Главное меню приложения, где пользователь выбирает тип данных
  int mainChoice;
  while (true)
  {
    std::cout << "\n--- Главное меню ---\n";
    std::cout << "1. Работать с Prepod\n";
    std::cout << "2. Работать с Member_of_commision\n";
    std::cout << "3. Работать с Prepod_from_commision\n";
    std::cout << "4. Выход\n";
    std::cout << "Ваш выбор: ";
    std::cin >> mainChoice;

    if (mainChoice == 1)
    {
      BinTree<Prepod> tree;
      Interface<Prepod> menu(tree, "Prepod");
      menu.run();
    }
    else if (mainChoice == 2)
    {
      BinTree<Member_of_commision> tree;
      Interface<Member_of_commision> menu(tree, "Member_of_commision");
      menu.run();
    }
    else if (mainChoice == 3)
    {
      BinTree<Prepod_from_commision> tree;
      Interface<Prepod_from_commision> menu(tree, "Prepod_from_commision");
      menu.run();
    }
    else if (mainChoice == 4)
    {
      break;
    }
    else
    {
      std::cout << "Неверный выбор.\n";
    }

    // Очистка буфера на случай некорректного ввода
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }

  std::cout << "Завершение программы.\n";
  return 0;
}
