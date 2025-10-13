#include "Member_of_commision.h"
#include <iomanip>

Member_of_commision::Member_of_commision()
    : Human("John", "Doe", "Unknown"), commision_name("Commission"), biography("No bio") {}

Member_of_commision::Member_of_commision(std::string name, std::string surname, std::string birthday,
                                         std::string commision_name, std::string biography)
    : Human(name, surname, birthday), commision_name(commision_name), biography(biography) {}

Member_of_commision::Member_of_commision(const Member_of_commision &other)
    : Human(other), commision_name(other.commision_name), biography(other.biography) {}

Member_of_commision::~Member_of_commision() {}

std::string Member_of_commision::get(std::string param) const {
    if (param == "commision_name") return commision_name;
    if (param == "biography") return biography;
    return Human::get(param);
}

void Member_of_commision::set(std::string param, std::string value) {
    if (param == "commision_name") commision_name = value;
    else if (param == "biography") biography = value;
    else Human::set(param, value);
}

Member_of_commision &Member_of_commision::operator=(const Member_of_commision &other) {
    if (this != &other) {
        Human::operator=(other);
        commision_name = other.commision_name;
        biography = other.biography;
    }
    return *this;
}

void Member_of_commision::printHeader(std::ostream &os) const {
    Human::printHeader(os);
    os << std::setw(20) << "Commission"
       << std::setw(20) << "Biography";
}

std::ostream &operator<<(std::ostream &os, const Member_of_commision &s) {
    os << static_cast<const Human &>(s)
       << std::setw(20) << s.commision_name
       << std::setw(20) << s.biography;
    return os;
}

std::istream &operator>>(std::istream &is, Member_of_commision &s) {
    is >> static_cast<Human &>(s) >> s.commision_name >> s.biography;
    return is;
}
