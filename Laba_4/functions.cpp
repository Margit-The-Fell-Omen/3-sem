#include "functions.h"
#include <algorithm>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

// Template function to handle operations for a specific class type
template <typename T>
void handleTreeOperations(BinTree<T> &tree, const std::string &className)
{
  int choice;
  T value;
  T oldValue, newValue;
  std::string searchParam;

  while (true)
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

    if (!(std::cin >> choice))
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Неверный ввод. Пожалуйста, введите число.\n";
      continue;
    }

    switch (choice)
    {
    case 1: // Insert
    {
      std::cout << "Введите данные " << className << ":\n";
      if (className == "Member_of_commision")
      {
        std::cout << "Формат: Имя Фамилия Дата_рождения Название_комиссии "
                     "Биография\n";
        std::cout << "Пример: Иван Иванов 1990-01-01 Математическая_комиссия "
                     "Преподаватель_математики\n";
      }
      else if (className == "Prepod")
      {
        std::cout << "Формат: Имя Фамилия Дата_рождения Ученая_степень "
                     "Должность Работы\n";
        std::cout << "Пример: Петр Петров 1985-05-15 Кандидат_наук Доцент "
                     "Научные_статьи\n";
      }
      else if (className == "Prepod_from_commision")
      {
        std::cout
            << "Формат: Имя Фамилия Дата_рождения Ученая_степень Должность "
               "Работы Название_комиссии Биография Работы_в_комиссии\n";
        std::cout << "Пример: Анна Сидорова 1980-03-20 Доктор_наук Профессор "
                     "Монографии Научная_комиссия Исследователь "
                     "Разработка_программ\n";
      }

      std::cin.ignore(); // Clear newline from buffer
      if (std::cin >> value)
      {
        tree.insert(value);
        std::cout << "Успешно добавлено!\n";
      }
      else
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод.\n";
      }
      break;
    }
    case 2: // Remove
    {
      std::cout << "Введите данные " << className << " для удаления:\n";
      if (className == "Member_of_commision")
      {
        std::cout << "Формат: Имя Фамилия Дата_рождения Название_комиссии "
                     "Биография\n";
      }
      else if (className == "Prepod")
      {
        std::cout << "Формат: Имя Фамилия Дата_рождения Ученая_степень "
                     "Должность Работы\n";
      }
      else if (className == "Prepod_from_commision")
      {
        std::cout
            << "Формат: Имя Фамилия Дата_рождения Ученая_степень Должность "
               "Работы Название_комиссии Биография Работы_в_комиссии\n";
      }

      std::cin.ignore();
      if (std::cin >> value)
      {
        tree.remove(value);
        std::cout << "Успешно удалено!\n";
      }
      else
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверный ввод.\n";
      }
      break;
    }
    case 3: // Update
    {
      std::cout << "Введите старые данные " << className << ":\n";
      if (className == "Member_of_commision")
      {
        std::cout << "Формат: Имя Фамилия Дата_рождения Название_комиссии "
                     "Биография\n";
      }
      else if (className == "Prepod")
      {
        std::cout << "Формат: Имя Фамилия Дата_рождения Ученая_степень "
                     "Должность Работы\n";
      }
      else if (className == "Prepod_from_commision")
      {
        std::cout
            << "Формат: Имя Фамилия Дата_рождения Ученая_степень Должность "
               "Работы Название_комиссии Биография Работы_в_комиссии\n";
      }

      std::cin.ignore();
      if (std::cin >> oldValue)
      {
        std::cout << "Введите новые данные " << className << ":\n";
        if (className == "Member_of_commision")
        {
          std::cout << "Формат: Имя Фамилия Дата_рождения Название_комиссии "
                       "Биография\n";
        }
        else if (className == "Prepod")
        {
          std::cout << "Формат: Имя Фамилия Дата_рождения Ученая_степень "
                       "Должность Работы\n";
        }
        else if (className == "Prepod_from_commision")
        {
          std::cout
              << "Формат: Имя Фамилия Дата_рождения Ученая_степень Должность "
                 "Работы Название_комиссии Биография Работы_в_комиссии\n";
        }

        if (std::cin >> newValue)
        {
          if (tree.update(oldValue, newValue))
          {
            std::cout << "Успешно обновлено!\n";
          }
          else
          {
            std::cout << "Ошибка обновления. Старые данные не найдены.\n";
          }
        }
        else
        {
          std::cin.clear();
          std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          std::cout << "Неверные новые данные.\n";
        }
      }
      else
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Неверные старые данные.\n";
      }
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
      std::cin.ignore();
      std::getline(std::cin, searchParam);

      std::cout << "Введите значение для поиска: ";
      std::string searchValue;
      std::getline(std::cin, searchValue);

      // Collect all elements from the tree
      std::vector<T> results;
      auto it = tree.template begin<Order::InOrder>();
      auto end = tree.template end<Order::InOrder>();

      while (it != end)
      {
        T current = *it; // Create a copy
        if (current.get(searchParam) == searchValue)
        {
          results.push_back(current);
        }
        ++it;
      }

      // Display results
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
      std::cin.ignore();
      std::string sortField;
      std::getline(std::cin, sortField);

      // Collect all elements from the tree
      std::vector<T> elements;
      auto it = tree.template begin<Order::InOrder>();
      auto end = tree.template end<Order::InOrder>();

      while (it != end)
      {
        elements.push_back(*it);
        ++it;
      }

      // Sort by the specified field
      std::sort(elements.begin(), elements.end(),
                [&sortField](const T &a, const T &b)
                { return a.get(sortField) < b.get(sortField); });

      // Display sorted results
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
    case 6: // InOrder
    {
      std::cout << "Порядок InOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto inIt = tree.template begin<Order::InOrder>();
      auto inEnd = tree.template end<Order::InOrder>();
      if (!(inIt != inEnd))
      {
        std::cout << "(Дерево пусто)" << std::endl;
      }
      else
      {
        while (inIt != inEnd)
        {
          std::cout << *inIt << std::endl;
          ++inIt;
        }
      }
      break;
    }
    case 7: // PreOrder
    {
      std::cout << "Порядок PreOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto preIt = tree.template begin<Order::PreOrder>();
      auto preEnd = tree.template end<Order::PreOrder>();
      if (!(preIt != preEnd))
      {
        std::cout << "(Дерево пусто)" << std::endl;
      }
      else
      {
        while (preIt != preEnd)
        {
          std::cout << *preIt << std::endl;
          ++preIt;
        }
      }
      break;
    }
    case 8: // PostOrder
    {
      std::cout << "Порядок PostOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto postIt = tree.template begin<Order::PostOrder>();
      auto postEnd = tree.template end<Order::PostOrder>();
      if (!(postIt != postEnd))
      {
        std::cout << "(Дерево пусто)" << std::endl;
      }
      else
      {
        while (postIt != postEnd)
        {
          std::cout << *postIt << std::endl;
          ++postIt;
        }
      }
      break;
    }
    case 9: // LevelOrder
    {
      std::cout << "Порядок LevelOrder:\n";
      T dummy;
      dummy.printHeader(std::cout);
      std::cout << std::endl;

      auto levelIt = tree.template begin<Order::LevelOrder>();
      auto levelEnd = tree.template end<Order::LevelOrder>();
      if (!(levelIt != levelEnd))
      {
        std::cout << "(Дерево пусто)" << std::endl;
      }
      else
      {
        while (levelIt != levelEnd)
        {
          std::cout << *levelIt << std::endl;
          ++levelIt;
        }
      }
      break;
    }
    case 10: // Clear
      tree = BinTree<T>();
      std::cout << "Дерево очищено.\n";
      break;
    case 11: // Back to main menu
      return;
    default:
      std::cout << "Неверный выбор. Пожалуйста, введите число от 1 до 11.\n";
    }
  }
}

// Explicit template instantiation for the types we use
template void
handleTreeOperations<Member_of_commision>(BinTree<Member_of_commision> &,
                                          const std::string &);
template void handleTreeOperations<Prepod>(BinTree<Prepod> &,
                                           const std::string &);
template void
handleTreeOperations<Prepod_from_commision>(BinTree<Prepod_from_commision> &,
                                            const std::string &);
