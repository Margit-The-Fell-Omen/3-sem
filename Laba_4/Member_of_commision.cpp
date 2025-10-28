#include "Member_of_commision.h"
#include <iomanip>

Member_of_commision::Member_of_commision()
    : commision_name("Commission"), biography("No bio")
{
}

Member_of_commision::Member_of_commision(std::string commision_name,
                                         std::string biography)
    : commision_name(commision_name), biography(biography)
{
}

Member_of_commision::Member_of_commision(const Member_of_commision &other)
    : Human(other), commision_name(other.commision_name),
      biography(other.biography)
{
}

Member_of_commision::~Member_of_commision() {}

std::string Member_of_commision::get(std::string param) const
{
  if (param == "commision_name")
    return commision_name;
  if (param == "biography")
    return biography;
  return Human::get(param);
}

void Member_of_commision::set(std::string param, std::string value)
{
  if (param == "commision_name")
    commision_name = value;
  else if (param == "biography")
    biography = value;
  else
    Human::set(param, value);
}

Member_of_commision &
Member_of_commision::operator=(const Member_of_commision &other)
{
  if (this != &other)
  {
    Human::operator=(other);
    commision_name = other.commision_name;
    biography = other.biography;
  }
  return *this;
}

// Comparison operators for Member_of_commision
bool Member_of_commision::operator<(const Member_of_commision &other) const
{
  // First compare by Human criteria
  if (static_cast<const Human &>(*this) < static_cast<const Human &>(other))
    return true;
  if (static_cast<const Human &>(other) < static_cast<const Human &>(*this))
    return false;

  // If Human parts are equal, compare by commission name
  return commision_name < other.commision_name;
}

bool Member_of_commision::operator>(const Member_of_commision &other) const
{
  return other < *this;
}

bool Member_of_commision::operator==(const Member_of_commision &other) const
{
  return static_cast<const Human &>(*this) ==
             static_cast<const Human &>(other) &&
         commision_name == other.commision_name && biography == other.biography;
}

void Member_of_commision::printHeader(std::ostream &os) const
{
  Human::printHeader(os);
  os << std::setw(20) << "Commission" << std::setw(20) << "Biography"
     << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Member_of_commision &s)
{
  os << static_cast<const Human &>(s) << std::setw(20) << s.commision_name
     << std::setw(20) << s.biography;
  return os;
}

std::istream &operator>>(std::istream &is, Member_of_commision &s)
{
  is >> static_cast<Human &>(s) >> s.commision_name >> s.biography;
  return is;
}
