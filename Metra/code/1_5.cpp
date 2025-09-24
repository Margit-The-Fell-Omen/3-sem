#include <iostream>

int main(int argc, char *argv[]) {
  int array_1[20];
  int array_2[20];
  int array_3[20];
  int index = 0;

  std::cout << "Эта программа находит общие элементы двух целочисленных "
               "массивов размерностью 20"
            << std::endl;

  std::cout << "Введите первый массив целых чисел:" << std::endl;

  for (int i = 0; i < 19; i++) {
    std::cin >> array_1[i];
  }

  std::cin.ignore(10000, '\n');

  std::cout << "Введите второй массив целых чисел:" << std::endl;

  for (int i = 0; i < 19; i++) {
    std::cin >> array_2[i];
  }

  bool already_is_in_array_3;

  for (int i = 0; i < 19; i++) {
    for (int j = i; j < 19; j++) {
      already_is_in_array_3 = false;
      for (int k = 0; k < index; k++) {
        if (array_3[k] == array_1[i]) {
          already_is_in_array_3 = true;
          break;
        }
      }
      if (array_1[i] == array_2[j] && !already_is_in_array_3) {
        array_3[index] = array_1[i];
        index++;
      }
    }
  }

  for (int i = index; i < 19; i++) {
    array_3[i] = 0;
  }

  std::cout << "Первый массив: " << std::endl;
  for (int i = 0; i < 19; i++) {
    std::cout << array_1[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Второй массив: " << std::endl;
  for (int i = 0; i < 19; i++) {
    std::cout << array_2[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "Итоговый массив: " << std::endl;
  for (int i = 0; i < 19; i++) {
    std::cout << array_3[i] << " ";
  }
  std::cout << std::endl;
  return 0;
}
