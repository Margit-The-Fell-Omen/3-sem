#include "Human.h"
#include <iostream>
#include <string>

Human::Human()
{
  this->name = "John";
  this->surname = "Doe";
  this->birthday = "Unknown";
}

Human::Human(std::string name, std::string surname, std::string birthday) 
{
  Human::set("name", name);
  Human::set("surname", surname);
  Human::set("birthday", birthday);
}

Human::Human(const Human &other) 
{

}

std::string Human::get(std::string param)
{
  if (param == "name")
  {
    return this->name;
  }
  else if (param == "surname")
  {
    return this->surname;
  }
  else if (param == "birthday")
  {
    return this->birthday;
  }
  else
  {
    std::cerr << "Unable to set" << param << ": no such param in class Human"
              << std::endl;
    return "NaN";
  }
}

void Human::set(std::string param, std::string value)
{
  if (param == "name")
  {
    this->name = value;
  }
  else if (param == "surname")
  {
    this->surname = value;
  }
  else if (param == "birthday")
  {
    this->birthday = value;
  }
  else
  {
    std::cerr << "Unable to set" << param << ": no such param in class Human"
              << std::endl;
  }
}

Human &Human::operator=(const Human &other)         // перегрузка оператора присваивания
{
  if (this != &other) 
  {
    this->name = other.name;
    this->surname = other.surname;
    this->birthday = other.birthday;
  }
  return *this;
}

std::ostream &operator<<(std::ostream &os,
                         const Human &s) // перегрузка оператора <<
{
  os << "Human name: " << s.name << ", surname: " << s.surname
     << ", birthday: " << s.birthday << std::endl;
  return os;
}

std::istream &operator>>(std::istream &is,
                         Human &s) // перегрузка оператора >>
{
  std::cout
      << "Формат ввода: (имя фамилия [дата рождения в формате ДД.ММ.ГГГГ])";
  std::string name;  
  std::string surname;  
  std::string birthday;
  is >> name >> surname >> birthday;
  s = Human(name, surname, birthday);

  return is;
}
