#include "Prepod.h"
#include "InputValidator.h"
#include <iomanip>

Prepod::Prepod() : degree("Неизвестно"), position("Неизвестно"), works("Нет") {}

Prepod::Prepod(std::string degree, std::string position, std::string works)
    : degree(degree), position(position), works(works)
{
}

Prepod::Prepod(const Prepod &other)
    : Human(other), degree(other.degree), position(other.position),
      works(other.works)
{
}

std::string Prepod::get(std::string param) const
{
  if (param == "degree")
    return degree;
  if (param == "position")
    return position;
  if (param == "works")
    return works;
  return Human::get(param);
}

void Prepod::set(std::string param, std::string value)
{
  if (param == "degree")
    degree = value;
  else if (param == "position")
    position = value;
  else if (param == "works")
    works = value;
  else
    Human::set(param, value);
}

void Prepod::printHeader(std::ostream &os) const
{
  Human::printHeader(os);
  os << std::left << std::setw(15) << "Степень" << std::setw(15) << "Должность"
     << std::setw(25) << "Работы";
}

bool Prepod::operator<(const Prepod &other) const
{
  if (static_cast<const Human &>(*this) < static_cast<const Human &>(other))
    return true;
  if (static_cast<const Human &>(other) < static_cast<const Human &>(*this))
    return false;
  return degree < other.degree;
}

bool Prepod::operator>(const Prepod &other) const { return other < *this; }

bool Prepod::operator==(const Prepod &other) const
{
  return static_cast<const Human &>(*this) ==
             static_cast<const Human &>(other) &&
         degree == other.degree && position == other.position &&
         works == other.works;
}

std::ostream &operator<<(std::ostream &os, const Prepod &p)
{
  if (&os == &std::cout)
  {
    os << static_cast<const Human &>(p) << std::left << std::setw(20)
       << p.get("degree") << std::setw(15) << p.get("position") << std::setw(25)
       << p.get("works");
  }
  else
  {
    // File output
    os << static_cast<const Human &>(p) << " " << p.get("degree") << " "
       << p.get("position") << " " << p.get("works");
  }
  return os;
}
std::istream &operator>>(std::istream &is, Prepod &p)
{
  is >> static_cast<Human &>(p);

  std::string temp_degree =
      InputValidator::readAndValidateNameField("Введите ученую степень: ");
  std::string temp_position =
      InputValidator::readAndValidateNameField("Введите должность: ");
  std::string temp_works =
      InputValidator::readSingleWord("Введите работы (одно слово): ");

  p.set("degree", temp_degree);
  p.set("position", temp_position);
  p.set("works", temp_works);

  return is;
}
