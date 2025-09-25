#ifndef MEMBER_OF_COMMISION_H
#include "Human.h"
#include <string>

class Member_of_commision : Human
{
private:
  std::string commision_name;
  std::string biography;

public:
  Member_of_commision();
  Member_of_commision(std::string commision_name, std::string biography);
  Member_of_commision(const Member_of_commision &other);
  ~Member_of_commision();

  std::string get(std::string param) const;
  void set(std::string param, std::string value);

  Member_of_commision &operator=(const Member_of_commision &other);
  friend std::ostream &
  operator<<(std::ostream &os,
             const Member_of_commision &s); // перегрузка оператора <<
  friend std::istream &
  operator>>(std::istream &is,
             Member_of_commision &s); // перегрузка оператора >>
};
#endif // !HUMAN_H
