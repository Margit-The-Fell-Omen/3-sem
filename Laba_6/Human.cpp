#include "Human.h"
#include "InputValidator.h"
#include <iomanip>

Human::Human()
    : name("Неизвестно"), surname("Неизвестно"), birthday("01.01.1900")
{
}
Human::Human(std::string name, std::string surname, std::string birthday)
    : name(name), surname(surname), birthday(birthday)
{
}

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
void Human::printHeader(std::ostream &os) const
{
  os << std::left << std::setw(22) << "Фамилия" << std::setw(18) << "Имя"
     << std::setw(23) << "Дата рожд.";
}

bool Human::operator<(const Human &other) const
{
  if (surname != other.surname)
    return surname < other.surname;
  return name < other.name;
}

bool Human::operator==(const Human &other) const
{
  return surname == other.surname && name == other.name &&
         birthday == other.birthday;
}

std::ostream &operator<<(std::ostream &os, const Human &h)
{
  os << std::left << std::setw(15) << h.get("surname") << std::setw(15)
     << h.get("name") << std::setw(15) << h.get("birthday");
  return os;
}

// РЕАЛИЗАЦИЯ operator>> с вызовом интерактивных гейткиперов
std::istream &operator>>(std::istream &is, Human &h)
{

  std::string temp_surname = InputValidator::readAndValidateNameField(
      "Введите фамилию: ", LanguageCheck::ONLY_LATIN);
  std::string temp_name = InputValidator::readAndValidateNameField(
      "Введите имя: ", LanguageCheck::ONLY_LATIN);
  std::string temp_birthday = InputValidator::readAndValidateDate(
      "Введите дату рождения (ДД.ММ.ГГГГ): ");

  h.set("surname", temp_surname);
  h.set("name", temp_name);
  h.set("birthday", temp_birthday);

  return is;
}
