#include "Prepod.h"
#include <iomanip>

Prepod::Prepod() : degree("Unknown"), position("Unknown"), works("None") {}
Prepod::Prepod(std::string degree, std::string position, std::string works)
    : degree(degree), position(position), works(works)
{
}
Prepod::Prepod(const Prepod &other)
    : Human(other), degree(other.degree), position(other.position),
      works(other.works)
{
}
Prepod::~Prepod() {}

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

Prepod &Prepod::operator=(const Prepod &other)
{
  if (this != &other)
  {
    Human::operator=(other);
    degree = other.degree;
    position = other.position;
    works = other.works;
  }
  return *this;
}

// Comparison operators for Prepod
bool Prepod::operator<(const Prepod &other) const
{
  // First compare by Human criteria (surname, name)
  if (static_cast<const Human &>(*this) < static_cast<const Human &>(other))
    return true;
  if (static_cast<const Human &>(other) < static_cast<const Human &>(*this))
    return false;

  // If Human parts are equal, compare by degree
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

void Prepod::printHeader(std::ostream &os) const
{
  Human::printHeader(os);
  os << std::setw(15) << "Degree" << std::setw(15) << "Position"
     << std::setw(25) << "Works" << std::endl;
}

void Prepod::printInputPrompt()
{
  std::cout << "Формат: Фамилия Имя Дата_рождения(ДД.ММ.ГГГГ) Ученая_степень "
               "Должность Работы\n";
  std::cout
      << "Пример: Петров Петр 15.05.1985 Кандидат_наук Доцент Научные_статьи\n";
}
std::ostream &operator<<(std::ostream &os, const Prepod &s)
{
  os << static_cast<const Human &>(s) << std::setw(15) << s.degree
     << std::setw(15) << s.position << std::setw(25) << s.works;
  return os;
}

std::istream &operator>>(std::istream &is, Prepod &s)
{
  is >> static_cast<Human &>(s);
  if (!is)
    return is;

  std::string temp_degree, temp_position, temp_works;
  if (!(is >> temp_degree >> temp_position >> temp_works))
    return is;

  InputException::checkNoSpecialCharsOrDigits_UTF8(temp_degree,
                                                   "Ученая_степень");
  InputException::checkNoSpecialCharsOrDigits_UTF8(temp_position, "Должность");

  s.set("degree", temp_degree);
  s.set("position", temp_position);
  s.set("works", temp_works);

  return is;
}
