#include "Prepod_from_commision.h"
#include "InputException.h"
#include <iomanip>

Prepod_from_commision::Prepod_from_commision() : Human(), commision_works("Нет")
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
  if (param == "commision_works" || param == "работы_в_комиссии")
    return commision_works;
  // Сначала проверяем поля Prepod
  if (param == "degree" || param == "position" || param == "works")
    return Prepod::get(param);
  // Затем поля Member_of_commision
  if (param == "commision_name" || param == "biography")
    return Member_of_commision::get(param);
  // В конце - поля Human
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

bool Prepod_from_commision::operator<(const Prepod_from_commision &other) const
{
  if (static_cast<const Human &>(*this) < static_cast<const Human &>(other))
    return true;
  if (static_cast<const Human &>(other) < static_cast<const Human &>(*this))
    return false;
  // Можно добавить сравнение по другим полям для уникальности, если нужно
  return commision_works < other.commision_works;
}

bool Prepod_from_commision::operator>(const Prepod_from_commision &other) const
{
  return other < *this;
}

bool Prepod_from_commision::operator==(const Prepod_from_commision &other) const
{
  return Prepod::operator==(other) && Member_of_commision::operator==(other) &&
         commision_works == other.commision_works;
}

void Prepod_from_commision::printHeader(std::ostream &os) const
{
  // Выводим заголовки всех полей, избегая дублирования Human
  Human::printHeader(os);
  os << std::left << std::setw(20) << "Степень" << std::setw(15) << "Должность"
     << std::setw(25) << "Работы" << std::setw(25) << "Название комиссии"
     << std::setw(30) << "Биография" << std::setw(25) << "Работы в комиссии";
}

std::ostream &operator<<(std::ostream &os, const Prepod_from_commision &s)
{
  // Выводим все поля, явно приводя к типам, чтобы вызвать нужные operator<<
  os << static_cast<const Human &>(s);
  // Используем геттеры для полей из Prepod и Member_of_commision, чтобы
  // избежать неоднозначности
  os << std::left << std::setw(20) << s.Prepod::get("degree") << std::setw(15)
     << s.Prepod::get("position") << std::setw(25) << s.Prepod::get("works")
     << std::setw(25) << s.Member_of_commision::get("commision_name")
     << std::setw(30) << s.Member_of_commision::get("biography")
     << std::setw(25) << s.get("commision_works"); // Уникальное поле
  return os;
}

// ИСПРАВЛЕНА РЕАЛИЗАЦИЯ
std::istream &operator>>(std::istream &is, Prepod_from_commision &pfc)
{
  // ПРАВИЛЬНЫЙ ПОДХОД:
  // 1. Вызываем ввод для Human
  is >> static_cast<Human &>(pfc);

  // 2. Вводим поля Prepod
  std::string temp_degree =
      InputException::readAndValidateNameField("Введите ученую степень: ");
  std::string temp_position =
      InputException::readAndValidateNameField("Введите должность: ");
  std::string temp_works =
      InputException::readSingleWord("Введите работы (одно слово): ");
  pfc.Prepod::set("degree", temp_degree);
  pfc.Prepod::set("position", temp_position);
  pfc.Prepod::set("works", temp_works);

  // 3. Вводим поля Member_of_commision
  std::string temp_commision =
      InputException::readAndValidateNameField("Введите название комиссии: ");
  std::string temp_bio =
      InputException::readSingleWord("Введите биографию (одно слово): ");
  pfc.Member_of_commision::set("commision_name", temp_commision);
  pfc.Member_of_commision::set("biography", temp_bio);

  // 4. Вводим уникальное поле этого класса
  std::string temp_c_works = InputException::readSingleWord(
      "Введите работы в комиссии (одно слово): ");
  pfc.set("commision_works", temp_c_works);

  return is;
}
