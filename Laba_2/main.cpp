#include "my_string.h"

int main() 
{
  // my_string s1("Hello");
  // std::cout << "s1: " << s1 << std::endl;
  // std::cout << "s2: " << s2 << std::endl;

  // // --- Comparison (<, >, ==) & Addition (+, +=) Demo ---
  // my_string s3= s1 + s2;
  // s1+=s2;
  // my_string s4(s1);

  // if (s3 < s4) 
  // {
  //   std::cout << s3 << " is less than " << s4 << std::endl;
  // }
  // if (s3 > s4) 
  // {
  //   std::cout << s3 << " is greater than " << s4 << std::endl;
  // }
  // if (s3 == s4)
  // {
  //   std::cout << s3 << " is equal to " << s4 << std::endl;
  // }

  // // --- Subscript ([]) Demo ---
  // std::cout << "\nOriginal s1: " << s1 << std::endl;
  // std::cout << "The character at index 1 of s1 is: " << s1[1]
  //           << std::endl;
  // s1[0] = 'J';
  // std::cout << "Modified s1: " << s1 << std::endl;

  // // --- Substring (()) Demo ---
  // my_string s5("Programming");
  // std::cout << "\nOriginal string for substring: " << s5 << std::endl;
  // my_string sub = s5(3, 7);
  // std::cout << "Substring from index 3 to 7: " << sub << std::endl;

  // --- Input/Output (>>,<<) Demo ---
  my_string s_input;
  std::cout << "\nEnter a word: ";
  std::cin >> s_input;
  std::cout << "You entered: " << s_input << std::endl;

  s_input = (s_input == s_input) ? s_input + s_input(1,4) : s_input+=s_input(1, 2);
  std::cout << "Результат: " << s_input << " А первый символ: " << s_input[0] << std::endl;
  return 0;
}