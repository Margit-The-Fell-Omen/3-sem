#include "Human.h"
#include <iostream>
#include <iomanip>

Human::Human() : name("John"), surname("Doe"), birthday("Unknown") {}
Human::Human(std::string name, std::string surname, std::string birthday)
    : name(name), surname(surname), birthday(birthday) {}
Human::Human(const Human &other)
    : name(other.name), surname(other.surname), birthday(other.birthday) {}
Human::~Human() {}

std::string Human::get(std::string param) const {
    if (param == "name") return name;
    if (param == "surname") return surname;
    if (param == "birthday") return birthday;
    return "NaN";
}

void Human::set(std::string param, std::string value) {
    if (param == "name") name = value;
    else if (param == "surname") surname = value;
    else if (param == "birthday") birthday = value;
}

Human &Human::operator=(const Human &other) {
    if (this != &other) {
        name = other.name;
        surname = other.surname;
        birthday = other.birthday;
    }
    return *this;
}

void Human::printHeader(std::ostream &os) const {
    os << std::left << std::setw(15) << "Name"
       << std::setw(15) << "Surname"
       << std::setw(15) << "Birthday";
}

std::ostream &operator<<(std::ostream &os, const Human &s) {
    os << std::left << std::setw(15) << s.name
       << std::setw(15) << s.surname
       << std::setw(15) << s.birthday;
    return os;
}

std::istream &operator>>(std::istream &is, Human &s) {
    is >> s.name >> s.surname >> s.birthday;
    return is;
}
