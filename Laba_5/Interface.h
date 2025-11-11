#pragma once

#include "BinTree.h"
#include "ExceptionHandler.h"
#include "Member_of_commision.h"
#include "Prepod.h"
#include "Prepod_from_commision.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

template <typename T> class Interface
{
private:
  BinTree<T> &tree;
  const std::string &className;
  bool isRunning = true;

  // Отображает меню
  void _displayMenu() const;
  // Получает выбор пользователя
  int _getUserChoice();
  // Обрабатывает выбор пользователя
  bool _processChoice(int choice);

public:
  Interface(BinTree<T> &treeRef, const std::string &name);
  void run();
};

// --- РЕАЛИЗАЦИЯ МЕТОДОВ ---

template <typename T>
Interface<T>::Interface(BinTree<T> &treeRef, const std::string &name)
    : tree(treeRef), className(name)
{
  // Включаем исключения для cin на время жизни объекта интерфейса
  std::cin.exceptions(std::ios_base::failbit);
}

template <typename T> void Interface<T>::_displayMenu() const
{
  std::cout << "\n=== Операции с деревом " << className << " ===\n";
  std::cout << "1. Добавить " << className << "\n";
  std::cout << "2. Удалить " << className << "\n";
  std::cout << "3. Обновить " << className << "\n";
  std::cout << "4. Поиск " << className << "\n";
  std::cout << "5. Сортировка и отображение\n";
  std::cout << "6. Отобразить в порядке InOrder\n";
  std::cout << "7. Отобразить в порядке PreOrder\n";
  std::cout << "8. Отобразить в порядке PostOrder\n";
  std::cout << "9. Отобразить в порядке LevelOrder\n";
  std::cout << "10. Очистить дерево\n";
  std::cout << "11. Вернуться в главное меню\n";
  std::cout << "Введите ваш выбор: ";
}

template <typename T> int Interface<T>::_getUserChoice()
{
  int choice;
  std::cin >>
      choice; // Может бросить исключение, которое поймает ExceptionHandler
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  return choice;
}

template <typename T> void Interface<T>::run()
{
  while (isRunning)
  {
    _displayMenu();

    ExceptionHandler::execute(
        [&]()
        {
          int choice = _getUserChoice();
          if (!_processChoice(choice))
          {
            isRunning = false;
          }
        });
  }
  // Отключаем исключения cin после завершения работы меню
  std::cin.exceptions(std::ios_base::goodbit);
}

template <typename T> bool Interface<T>::_processChoice(int choice)
{
  T value;
  T oldValue, newValue;
  std::string searchParam, searchValue;

  switch (choice)
  {
  case 1: // Insert
  {
    std::cout << "Введите данные для добавления " << className << ":\n";
    T::printInputPrompt();
    std::cin >> value; // Теперь бросает InputException напрямую
    tree.insert(value);
    std::cout << "Успешно добавлено!\n";
    break;
  }
  case 2: // Remove
  {
    std::cout << "Введите данные " << className << " для удаления:\n";
    T::printInputPrompt();
    std::cin >> value;
    tree.remove(value);
    std::cout << "Успешно удалено!\n";
    break;
  }
  case 3: // Update
  {
    std::cout << "Введите старые данные " << className << ":\n";
    T::printInputPrompt();
    std::cin >> oldValue;
    std::cout << "Введите новые данные " << className << ":\n";
    T::printInputPrompt();
    std::cin >> newValue;
    tree.update(oldValue, newValue);
    std::cout << "Успешно обновлено!\n";
    break;
  }
  case 4: // Search
  {
    std::cout << "Введите параметр поиска (";
    if (className == "Member_of_commision")
    {
      std::cout << "name/имя, surname/фамилия, birthday/дата_рождения, "
                   "commision_name/название_комиссии, biography/биография";
    }
    else if (className == "Prepod")
    {
      std::cout << "name/имя, surname/фамилия, birthday/дата_рождения, "
                   "degree/ученая_степень, position/должность, works/работы";
    }
    else if (className == "Prepod_from_commision")
    {
      std::cout << "name/имя, surname/фамилия, birthday/дата_рождения, "
                   "degree/ученая_степень, position/должность, works/работы, "
                   "commision_name/название_комиссии, biography/биография, "
                   "commision_works/работы_в_комиссии";
    }
    std::cout << "): ";
    std::getline(std::cin, searchParam);

    std::cout << "Введите значение для поиска: ";
    std::getline(std::cin, searchValue);

    std::vector<T> results;
    auto it = tree.template begin<Order::InOrder>();
    auto end = tree.template end<Order::InOrder>();
    while (it != end)
    {
      if ((*it).get(searchParam) == searchValue)
      {
        results.push_back(*it);
      }
      ++it;
    }

    if (results.empty())
    {
      std::cout << "Совпадений не найдено.\n";
    }
    else
    {
      std::cout << "Найдено " << results.size() << " совпадение(ий):\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;
      for (const auto &result : results)
      {
        std::cout << result << std::endl;
      }
    }
    break;
  }
  case 5: // Sort and Display
  {
    std::cout << "Выберите поле для сортировки (";
    if (className == "Member_of_commision")
    {
      std::cout << "name/имя, surname/фамилия, birthday/дата_рождения, "
                   "commision_name/название_комиссии, biography/биография";
    }
    else if (className == "Prepod")
    {
      std::cout << "name/имя, surname/фамилия, birthday/дата_рождения, "
                   "degree/ученая_степень, position/должность, works/работы";
    }
    else if (className == "Prepod_from_commision")
    {
      std::cout << "name/имя, surname/фамилия, birthday/дата_рождения, "
                   "degree/ученая_степень, position/должность, works/работы, "
                   "commision_name/название_комиссии, biography/биография, "
                   "commision_works/работы_в_комиссии";
    }
    std::cout << "): ";
    std::string sortField;
    std::getline(std::cin, sortField);

    std::vector<T> elements;
    auto it = tree.template begin<Order::InOrder>();
    auto end = tree.template end<Order::InOrder>();
    while (it != end)
    {
      elements.push_back(*it);
      ++it;
    }

    std::sort(elements.begin(), elements.end(),
              [&sortField](const T &a, const T &b)
              { return a.get(sortField) < b.get(sortField); });

    if (elements.empty())
    {
      std::cout << "Дерево пусто.\n";
    }
    else
    {
      std::cout << "Отсортировано по полю " << sortField << ":\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;
      for (const auto &element : elements)
      {
        std::cout << element << std::endl;
      }
    }
    break;
  }
  case 6: // InOrder traversal
  {
    std::cout << "Порядок InOrder:\n";
    if (!tree.getRoot())
    {
      std::cout << "(Дерево пусто)" << std::endl;
      break;
    }
    T dummy;
    dummy.printHeader(std::cout);
    std::cout << std::endl;
    auto it = tree.template begin<Order::InOrder>();
    auto end = tree.template end<Order::InOrder>();
    while (it != end)
    {
      std::cout << *it << std::endl;
      ++it;
    }
    break;
  }
  case 7: // PreOrder traversal
  {
    std::cout << "Порядок PreOrder:\n";
    if (!tree.getRoot())
    {
      std::cout << "(Дерево пусто)" << std::endl;
      break;
    }
    T dummy;
    dummy.printHeader(std::cout);
    std::cout << std::endl;
    auto it = tree.template begin<Order::PreOrder>();
    auto end = tree.template end<Order::PreOrder>();
    while (it != end)
    {
      std::cout << *it << std::endl;
      ++it;
    }
    break;
  }
  case 8: // PostOrder traversal
  {
    std::cout << "Порядок PostOrder:\n";
    if (!tree.getRoot())
    {
      std::cout << "(Дерево пусто)" << std::endl;
      break;
    }
    T dummy;
    dummy.printHeader(std::cout);
    std::cout << std::endl;
    auto it = tree.template begin<Order::PostOrder>();
    auto end = tree.template end<Order::PostOrder>();
    while (it != end)
    {
      std::cout << *it << std::endl;
      ++it;
    }
    break;
  }
  case 9: // LevelOrder traversal
  {
    std::cout << "Порядок LevelOrder:\n";
    if (!tree.getRoot())
    {
      std::cout << "(Дерево пусто)" << std::endl;
      break;
    }
    T dummy;
    dummy.printHeader(std::cout);
    std::cout << std::endl;
    auto it = tree.template begin<Order::LevelOrder>();
    auto end = tree.template end<Order::LevelOrder>();
    while (it != end)
    {
      std::cout << *it << std::endl;
      ++it;
    }
    break;
  }
  case 10: // Clear
  {
    tree = BinTree<T>();
    std::cout << "Дерево очищено.\n";
    break;
  }
  case 11: // Back to main menu
  {
    std::cout << "Возврат в главное меню...\n";
    return false; // Сигнал для выхода из цикла
  }
  default:
  {
    std::cout << "Неверный выбор. Пожалуйста, введите число от 1 до 11.\n";
    break;
  }
  }

  return true; // Сигнал для продолжения цикла
}
