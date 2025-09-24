#include <cmath>
#include <iostream>

int main(int argc, char *argv[]) {
  int array_1[8];
  int array_2[8];
  float result = 0;
  bool bool_array[8]{false};

  std::cout << "Эта программа выполняет суммирование кватратов отношений "
               "элементов двух целочисленных "
               "массивов размерностью 8 при условии того, что элемент первого "
               "массиво строго больше"
            << std::endl;

  std::cout << "Введите первый массив целых чисел:" << std::endl;

  for (int i = 0; i < 8; i++) {
    std::cin >> array_1[i];
  }

  std::cin.ignore(10000, '\n');

  std::cout << "Введите второй массив целых чисел:" << std::endl;

  for (int i = 0; i < 8; i++) {
    std::cin >> array_2[i];
  }

  for (int i = 0; i < 8; i++) {
    if (array_1[i] > array_2[i]) {
      result += pow(array_1[i] / array_2[i], 2);
      bool_array[i] = true;
    }
  }

  std::cout << "Первый массив: " << std::endl;
  for (int i = 0; i < 8; i++) {
    std::cout << array_1[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Второй массив: " << std::endl;
  for (int i = 0; i < 8; i++) {
    std::cout << array_2[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "В рассчёте учавствовали данные пары элементов: " << std::endl;
  for (int i = 0; i < 8; i++) {
    if (bool_array[i])
      std::cout << array_1[i] << " - " << array_2[i] << std::endl;
  }

  std::cout << "Итоговый результат: " << std::endl;
  std::cout << result << std::endl;
  return 0;
}

// отослать отчёт: задание, код, блочка, скриншоты выполненияЖ

/*
 * ======== Рассчёт метрик =======
 * По ьлочке: метрика Макейпа (блоки и соединения), метрика Джилбо (макс. ур.
 * вложенности), */
