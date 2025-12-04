#include "Member_of_commision.h"
#include "InputValidator.h" // Подключаем для доступа к интерактивным методам ввода
#include <iomanip>

Member_of_commision::Member_of_commision()
    : commision_name("Неизвестно"), biography("Нет")
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
  if (param == "commision_name" || param == "название_комиссии")
    return commision_name;
  if (param == "biography" || param == "биография")
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

// Операторы сравнения для Member_of_commision
bool Member_of_commision::operator<(const Member_of_commision &other) const
{
  if (static_cast<const Human &>(*this) < static_cast<const Human &>(other))
    return true;
  if (static_cast<const Human &>(other) < static_cast<const Human &>(*this))
    return false;

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
  os << std::left << std::setw(25) << "Название комиссии" << std::setw(30)
     << "Биография";
}

std::ostream &operator<<(std::ostream &os, const Member_of_commision &s)
{
  if (&os == &std::cout)
  {
    os << static_cast<const Human &>(s) << std::left << std::setw(25)
       << s.get("commision_name") << std::setw(30) << s.get("biography");
  }
  else
  {
    // File output
    os << static_cast<const Human &>(s) << " " << s.get("commision_name") << " "
       << s.get("biography");
  }
  return os;
}

// --- ПЕРЕРАБОТАННЫЙ ОПЕРАТОР ВВОДА ---
std::istream &operator>>(std::istream &is, Member_of_commision &m)
{
  is >> static_cast<Human &>(m);

  std::string temp_commision = InputValidator::readAndValidateNameField(
      "Введите название комиссии: ", LanguageCheck::ONLY_LATIN);
  std::string temp_bio =
      InputValidator::readSingleWord("Введите биографию (одно слово): ");

  m.set("commision_name", temp_commision);
  m.set("biography", temp_bio);

  return is;
}
