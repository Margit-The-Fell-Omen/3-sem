#include "Human.h"

#include <iomanip>
#include <iostream>

Human::Human() : name("John"), surname("Doe"), birthday("Unknown") {}

Human::Human(std::string name, std::string surname, std::string birthday)
    : name(name), surname(surname), birthday(birthday)
{
}

Human::Human(const Human &other)
    : name(other.name), surname(other.surname), birthday(other.birthday)
{
}

Human::~Human() {}

std::string Human::get(std::string param) const
{
  if (param == "name" || param == "имя")
    return name;
  if (param == "surname" || param == "фамилия")
    return surname;
  if (param == "birthday" || param == "дата_рождения")
    return birthday;
  return "NaN";
}

void Human::set(std::string param, std::string value)
{
  if (param == "name")
    name = value;
  else if (param == "surname")
    surname = value;
  else if (param == "birthday")
    birthday = value;
}

Human &Human::operator=(const Human &other)
{
  if (this != &other)
  {
    name = other.name;
    surname = other.surname;
    birthday = other.birthday;
  }
  return *this;
}

// Comparison operators
bool Human::operator<(const Human &other) const
{
  // Compare by surname first, then by name
  if (surname != other.surname)
    return surname < other.surname;
  return name < other.name;
}

bool Human::operator>(const Human &other) const { return other < *this; }

bool Human::operator==(const Human &other) const
{
  return name == other.name && surname == other.surname &&
         birthday == other.birthday;
}

void Human::printHeader(std::ostream &os) const
{
  os << std::left << std::setw(15) << "Name" << std::setw(15) << "Surname"
     << std::setw(15) << "Birthday";
}

std::ostream &operator<<(std::ostream &os, const Human &s)
{
  os << std::left << std::setw(15) << s.name << std::setw(15) << s.surname
     << std::setw(15) << s.birthday;
  return os;
}

std::istream &operator>>(std::istream &is, Human &h)
{
  std::string temp_name, temp_surname, temp_birthday;

  if (!(is >> temp_surname >> temp_name >> temp_birthday))
  {
    return is;
  }

  InputException::checkNoSpecialCharsOrDigits_UTF8(temp_surname, "Фамилия");
  InputException::checkNoSpecialCharsOrDigits_UTF8(temp_name, "Имя");
  InputException::checkDateFormat(temp_birthday, "Дата_рождения");

  h.set("surname", temp_surname);
  h.set("name", temp_name);
  h.set("birthday", temp_birthday);

  return is;
}
