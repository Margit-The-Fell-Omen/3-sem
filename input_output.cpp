#include "my_string.cpp"
#include <iostream>
#include <ostream>
#define MAX_STR_SIZE 4294967196 // 2^32

void add_str_to_list(my_string my_str, my_string *my_string_list)
{
  int list_size = 0;

  my_string *temp = my_string_list;
  while (temp + list_size != nullptr)
  {
    ++list_size;
  }

  temp = new my_string[list_size + 1];
  for (int i = 0; i < list_size; i++)
  {
    temp[i] = my_string_list[i];
  }
  temp[list_size] = my_str;
  my_string_list = temp;
}

void menu()
{
  int menu_choice;
  my_string *my_string_list;

  std::cout << "Выберите действие: " << std::endl;

  std::cout << "1 - создать строку" << std::endl
            << "2 - изменить строку" << std::endl
            << "3 - вывести строку на экран" << std::endl
            << "0 - завершить работу программы" << std::endl;
  std::cin >> menu_choice;
  switch (menu_choice)
  {
  case 1:
    int create_menu_choice;

    std::cout << "Выберите действие: " << std::endl;
    std::cout << "1 - создать пустую строку" << std::endl
              << "2 - создать строку и присвоить ей значение" << std::endl
              << "3 - создать копию существующей строки" << std::endl
              << "0 - назад" << std::endl;

    std::cin >> create_menu_choice;

    switch (create_menu_choice)
    {
    case 1:
    {
      my_string my_str;
      add_str_to_list(my_str, my_string_list);
      break;
    }
    case 2:
    {
      char value[MAX_STR_SIZE];
      std::cout << "Введите строку: ";
      std::cin >> value;
      my_string my_str2(value);
      add_str_to_list(my_str2, my_string_list);
      break;
    }
    case 3:
    {
      if (my_string_list != nullptr)
      {
        my_string *temp = my_string_list;
        int i = 0;
        std::cout << "Выберите строку для копирования: " << std::endl;
        while (temp + i != nullptr)
        {
          std::cout << "Строка " << i << " : ";
          (temp + i)->print();
          ++i;
        }
        int copy_choice;
        std::cin >> copy_choice; // TODO: COPY OLD INPUT FUNCTIONS
        my_string my_str3(*(temp + copy_choice));
        add_str_to_list(my_str3, my_string_list);
      }
    }
    break;
    case 0:
      break;
    }

    break;
  case 2:

    break;
  case 3:

    break;
  case 0:

    break;
  }
}
