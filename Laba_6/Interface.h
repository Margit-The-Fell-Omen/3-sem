#pragma once
#include "BinTree.h"
#include "BinTreeException.h"
#include "FileHandler.h" // Предполагается, что FileException определен здесь или в Exception.h
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// Предварительное объявление FileException, если он в отдельном файле
class FileException;

template <typename T> class Interface
{
private:
  BinTree<T> &tree;
  const std::string className;
  bool isRunning = true;
  FileHandler<T> fileHandler{"default.txt"};

  // Обработчики меню и выбора
  void _displayMenu() const;
  int _getUserChoice();
  void _processChoice(int choice);

  // Приватные методы для поиска и сортировки
  void _handleSearch();
  void _handleSort();

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
  std::cout << "11. Сохранить в файл\n";
  std::cout << "12. Загрузить из файла\n";
  std::cout << "13. Вернуться в главное меню\n";
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
    catch (const BinTreeException &e)
    {
      std::cerr << "\n[ОШИБКА ОПЕРАЦИИ]: " << e.what() << std::endl;
    }
    catch (const FileException &e)
    {
      std::cerr << "\n[ОШИБКА ФАЙЛА]: " << e.what() << std::endl;
    }
  }
}

template <typename T> void Interface<T>::_handleSearch()
{
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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

  std::string searchParam;
  std::getline(std::cin, searchParam);

  std::cout << "Введите значение для поиска: ";
  std::string searchValue;
  std::getline(std::cin, searchValue);

  std::vector<T> results;
  auto it = tree.template begin<Order::InOrder>();
  auto end_it = tree.template end<Order::InOrder>();
  while (it != end_it)
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
}

template <typename T> void Interface<T>::_handleSort()
{
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
  auto end_it = tree.template end<Order::InOrder>();
  while (it != end_it)
  {
    elements.push_back(*it);
    ++it;
  }

  std::sort(elements.begin(), elements.end(),
            [&sortField](const T &a, const T &b)
            {
              if (sortField == "birthday" || sortField == "дата_рождения")
              {
                std::string dateA_str = a.get(sortField);
                std::string dateB_str = b.get(sortField);
                auto toComparable = [](const std::string &date)
                {
                  if (date.length() != 10)
                    return std::string("");
                  return date.substr(6, 4) + date.substr(3, 2) +
                         date.substr(0, 2);
                };
                return toComparable(dateA_str) < toComparable(dateB_str);
              }
              else
              {
                return a.get(sortField) < b.get(sortField);
              }
            });

  if (elements.empty())
  {
    std::cout << "Дерево пусто.\n";
  }
  else
  {
    std::cout << "Отсортировано по полю '" << sortField << "':\n";
    T dummy;
    dummy.printHeader(std::cout);
    std::cout << std::endl;
    for (const auto &element : elements)
    {
      std::cout << element << std::endl;
    }
  }
}

template <typename T> void Interface<T>::_processChoice(int choice)
{
  auto clearAfterObjectInput = []()
  {
    if (std::cin.peek() != '\n' && std::cin.peek() != EOF)
    {
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  };

  switch (choice)
  {
  case 1:
  {
    std::cout << "\n--- Добавление нового элемента ---\n";
    T value;
    std::cin >> value;
    tree.insert(value);
    std::cout << "Успешно добавлено!\n";
    clearAfterObjectInput();
    break;
  }
  case 2:
  {
    std::cout << "\n--- Удаление элемента ---\n";
    T value;
    std::cin >> value;
    tree.remove(value);
    std::cout << "Успешно удалено!\n";
    clearAfterObjectInput();
    break;
  }
  case 3:
  {
    std::cout << "\n--- Обновление элемента ---\n";
    T oldValue, newValue;
    std::cout << "Введите СТАРЫЕ данные элемента для обновления:\n";
    std::cin >> oldValue;
    clearAfterObjectInput();
    std::cout << "Введите НОВЫЕ данные для элемента:\n";
    std::cin >> newValue;
    tree.update(oldValue, newValue);
    std::cout << "Успешно обновлено!\n";
    clearAfterObjectInput();
    break;
  }
  case 4:
  {
    _handleSearch();
    break;
  }
  case 5:
  {
    _handleSort();
    break;
  }
  case 6:
  case 7:
  case 8:
  case 9:
  {
    T dummy;
    auto display = [&](const std::string &orderName, auto begin_it, auto end_it)
    {
      std::cout << "Порядок " << orderName << ":\n";
      if (!tree.getRoot())
      {
        std::cout << "(Дерево пусто)\n";
        return;
      }
      dummy.printHeader(std::cout);
      std::cout << std::endl;
      while (begin_it != end_it)
      {
        std::cout << *begin_it << std::endl;
        ++begin_it;
      }
    };
    if (choice == 6)
      display("InOrder", tree.template begin<Order::InOrder>(),
              tree.template end<Order::InOrder>());
    if (choice == 7)
      display("PreOrder", tree.template begin<Order::PreOrder>(),
              tree.template end<Order::PreOrder>());
    if (choice == 8)
      display("PostOrder", tree.template begin<Order::PostOrder>(),
              tree.template end<Order::PostOrder>());
    if (choice == 9)
      display("LevelOrder", tree.template begin<Order::LevelOrder>(),
              tree.template end<Order::LevelOrder>());
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
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите имя файла для сохранения (по умолчанию: "
              << fileHandler.getFilename() << "): ";
    std::string fname;
    std::getline(std::cin, fname);
    if (!fname.empty())
      fileHandler.setFilename(fname);
    fileHandler.writeToFile(tree);
    std::cout << "Дерево успешно сохранено в файл '"
              << fileHandler.getFilename() << "'\n";
    break;
  }
  case 12:
  {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "Введите имя файла для загрузки (по умолчанию: "
              << fileHandler.getFilename() << "): ";
    std::string fname;
    std::getline(std::cin, fname);
    if (!fname.empty())
      fileHandler.setFilename(fname);
    fileHandler.readFromFile(tree);
    std::cout << "Дерево успешно загружено из файла '"
              << fileHandler.getFilename() << "'\n";
    break;
  }
  case 13:
  {
    isRunning = false;
    std::cout << "Возврат в главное меню...\n";
    break;
  }
  default:
    std::cout << "Неверный выбор.\n";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}
