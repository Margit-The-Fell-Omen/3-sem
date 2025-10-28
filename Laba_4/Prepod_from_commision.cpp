#include "Prepod_from_commision.h"
#include <iomanip>

Prepod_from_commision::Prepod_from_commision()
    : Human(), Prepod(), Member_of_commision(), commision_works("None")
{
}

Prepod_from_commision::Prepod_from_commision(
    std::string name, std::string surname, std::string birthday,
    std::string degree, std::string position, std::string works,
    std::string commision_name, std::string biography,
    std::string commision_works)
    : Human(name, surname, birthday), Prepod(degree, position, works),
      Member_of_commision(commision_name, biography),
      commision_works(commision_works)
{
}

Prepod_from_commision::Prepod_from_commision(const Prepod_from_commision &other)
    : Human(other), Prepod(other), Member_of_commision(other),
      commision_works(other.commision_works)
{
}

Prepod_from_commision::~Prepod_from_commision() {}

std::string Prepod_from_commision::get(std::string param) const
{
  if (param == "commision_works")
    return commision_works;
  if (param == "degree" || param == "position" || param == "works")
    return Prepod::get(param);
  if (param == "commision_name" || param == "biography")
    return Member_of_commision::get(param);
  return Human::get(param);
}

void Prepod_from_commision::set(std::string param, std::string value)
{
  if (param == "commision_works")
    commision_works = value;
  else if (param == "degree" || param == "position" || param == "works")
    Prepod::set(param, value);
  else if (param == "commision_name" || param == "biography")
    Member_of_commision::set(param, value);
  else
    Human::set(param, value);
}

Prepod_from_commision &
Prepod_from_commision::operator=(const Prepod_from_commision &other)
{
  if (this != &other)
  {
    Prepod::operator=(other);
    Member_of_commision::operator=(other);
    commision_works = other.commision_works;
  }
  return *this;
}

// Comparison operators for Prepod_from_commision
bool Prepod_from_commision::operator<(const Prepod_from_commision &other) const
{
  // First compare by Human criteria
  if (static_cast<const Human &>(*this) < static_cast<const Human &>(other))
    return true;
  if (static_cast<const Human &>(other) < static_cast<const Human &>(*this))
    return false;

  // If Human parts are equal, compare by commission works
  return commision_works < other.commision_works;
}

bool Prepod_from_commision::operator>(const Prepod_from_commision &other) const
{
  return other < *this;
}

bool Prepod_from_commision::operator==(const Prepod_from_commision &other) const
{
  return static_cast<const Human &>(*this) ==
             static_cast<const Human &>(other) &&
         static_cast<const Prepod &>(*this) ==
             static_cast<const Prepod &>(other) &&
         static_cast<const Member_of_commision &>(*this) ==
             static_cast<const Member_of_commision &>(other) &&
         commision_works == other.commision_works;
}

void Prepod_from_commision::printHeader(std::ostream &os) const
{
  Human::printHeader(os);
  os << std::setw(15) << "Degree" << std::setw(15) << "Position"
     << std::setw(25) << "Works" << std::setw(20) << "Commission"
     << std::setw(20) << "Biography" << std::setw(25) << "Commision Works"
     << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Prepod_from_commision &s)
{
  os << static_cast<const Human &>(s);
  os << std::setw(15) << s.degree << std::setw(15) << s.position
     << std::setw(25) << s.works << std::setw(20) << s.commision_name
     << std::setw(20) << s.biography << std::setw(25) << s.commision_works;
  return os;
}

std::istream &operator>>(std::istream &is, Prepod_from_commision &s)
{
  is >> static_cast<Human &>(s) >> s.degree >> s.position >> s.works >>
      s.commision_name >> s.biography >> s.commision_works;
  return is;
}
