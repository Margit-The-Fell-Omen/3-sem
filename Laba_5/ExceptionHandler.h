#pragma once
#include <functional> // Для std::function, хотя мы будем использовать шаблоны

// Этот шаблонный метод принимает любую вызываемую сущность (лямбду, функцию)
// и выполняет ее внутри блока try-catch.
// Поскольку это шаблон, реализация должна быть в заголовочном файле.

#include "Exception.h"
#include <ios> // Для std::ios_base::failure
#include <iostream>
#include <limits>

namespace ExceptionHandler
{
template <typename Func> void execute(Func funcToRun)
{
  try
  {
    // Просто выполняем переданную нам функцию
    funcToRun();
  }
  catch (const std::ios_base::failure &) // Ловит ошибки ввода в std::cin
  {
    std::cerr << "\n[ОШИБКА ВВОДА]: Ожидалось число, но введены некорректные "
                 "данные.\n";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
  catch (const Exception &e) // Ловит все наши кастомные исключения
                             // (InputException, BinTreeException)
  {
    std::cerr << "\n[ОШИБКА]: " << e.GetMessage() << "\n";
    // Если ошибка произошла из-за cin, очищаем поток
    if (std::cin.fail())
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
  }
}
} // namespace ExceptionHandler
