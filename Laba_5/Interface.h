#pragma once
#include "BinTree.h"
#include "BinTreeException.h"
#include "Prepod.h" // И другие классы данных
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

template <typename T> class Interface
{
private:
  BinTree<T> &tree;
  const std::string className;
  bool isRunning = true;

  void _displayMenu() const;
  int _getUserChoice();
  void _processChoice(int choice);

public:
  Interface(BinTree<T> &treeRef, const std::string &name);
  void run();
};

template <typename T>
Interface<T>::Interface(BinTree<T> &treeRef, const std::string &name)
    : tree(treeRef), className(name)
{
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
  std::cin >> choice;
  if (std::cin.fail())
  {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    throw BinTreeException("Неверный выбор меню. Пожалуйста, введите число.");
  }
  // std::cin.ignore здесь не нужен, т.к. интерактивный ввод теперь пословный
  return choice;
}

template <typename T> void Interface<T>::run()
{
  while (isRunning)
  {
    _displayMenu();
    try
    {
      int choice = _getUserChoice();
      _processChoice(choice);
    }
    catch (const BinTreeException &e) // Ловим ТОЛЬКО ошибки контейнера
    {
      std::cerr << "\n[ОШИБКА ОПЕРАЦИИ]: " << e.GetMessage() << std::endl;
    }
  }
}

template <typename T> void Interface<T>::_processChoice(int choice)
{
  std::string searchParam, searchValue;

  // Clear the input buffer before any getline operations
  auto clearInputBuffer = []()
  { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); };

  switch (choice)
  {
  case 1: // Добавить
  {
    std::cout << "\n--- Добавление нового элемента ---\n";
    T value;
    std::cin >> value;
    tree.insert(value);
    std::cout << "Успешно добавлено!\n";
    clearInputBuffer(); // Clear buffer after cin >>
    break;
  }
  case 2: // Удалить
  {
    std::cout << "\n--- Удаление элемента ---\n";
    T value;
    std::cin >> value;
    tree.remove(value);
    std::cout << "Успешно удалено!\n";
    clearInputBuffer(); // Clear buffer after cin >>
    break;
  }
  case 3: // Обновить
  {
    std::cout << "\n--- Обновление элемента ---\n";
    T oldValue, newValue;
    std::cout << "Введите СТАРЫЕ данные элемента для обновления:\n";
    std::cin >> oldValue;
    clearInputBuffer(); // Clear buffer after first cin >>

    std::cout << "Введите НОВЫЕ данные для элемента:\n";
    std::cin >> newValue;
    tree.update(oldValue, newValue);
    std::cout << "Успешно обновлено!\n";
    clearInputBuffer(); // Clear buffer after second cin >>
    break;
  }
  case 4: // Search
  {
    clearInputBuffer(); // Clear buffer before getline operations

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
    clearInputBuffer(); // Clear buffer before getline operations

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
  case 10:
  {
    tree = BinTree<T>();
    std::cout << "Дерево очищено.\n";
    break;
  }
  case 11:
  {
    isRunning = false;
    std::cout << "Возврат в главное меню...\n";
    break;
  }
  default:
    std::cout << "Неверный выбор.\n";
  }
}
