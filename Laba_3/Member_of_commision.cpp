#include "Member_of_commision.h"
#include <iostream>
#include <string>

Member_of_commision::Member_of_commision()
{
  this->commision_name = "Commisinon name";
  this->biography = "No bio";
}

Member_of_commision::Member_of_commision(std::string commision_name,
                                         std::string biography)
{
  Member_of_commision::set("commision_name", commision_name);
  Member_of_commision::set("biography", biography);
}

Member_of_commision::Member_of_commision(const Member_of_commision &other)
{
  this->commision_name = other.get("commision_name");
  this->biography = other.get("biography");
}

Member_of_commision::~Member_of_commision() {}

std::string Member_of_commision::get(std::string param) const
{
  if (param == "commision_name")
  {
    return this->commision_name;
  }
  else if (param == "biography")
  {
    return this->biography;
  }
  else
  {
    std::cerr << "Unable to set" << param
              << ": no such param in class Member_of_commision" << std::endl;
    return "NaN";
  }
}

void Member_of_commision::set(std::string param, std::string value)
{
  if (param == "commision_name")
  {
    this->commision_name = value;
  }
  else if (param == "biography")
  {
    this->biography = value;
  }
  else
  {
    std::cerr << "Unable to set" << param
              << ": no such param in class Member_of_commision" << std::endl;
  }
}

Member_of_commision &Member_of_commision::operator=(
    const Member_of_commision &other) // перегрузка оператора присваивания
{
  if (this != &other)
  {
    this->commision_name = other.get("name");
    this->biography = other.get("biography");
  }
  return *this;
}

std::ostream &
operator<<(std::ostream &os,
           const Member_of_commision &s) // перегрузка оператора <<
{
  os << "Member_of_commision: " << s.commision_name << ", bio: " << s.biography
     << std::endl;
  return os;
}

std::istream &operator>>(std::istream &is,
                         Member_of_commision &s) // перегрузка оператора >>
{
  std::cout
      << "Формат ввода: (имя фамилия [дата рождения в формате ДД.ММ.ГГГГ])";
  std::string commision_name;
  std::string biography;
  is >> commision_name >> biography;
  s = Member_of_commision(commision_name, biography);

  return is;
}
