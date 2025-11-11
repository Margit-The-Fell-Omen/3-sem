#ifndef MEMBER_OF_COMMISION_H
#define MEMBER_OF_COMMISION_H
#include "Human.h"
#include <iostream>
#include <string>

class Member_of_commision : public virtual Human
{
protected:
  std::string commision_name;
  std::string biography;

public:
  Member_of_commision();
  Member_of_commision(std::string commision_name, std::string biography);
  Member_of_commision(const Member_of_commision &other);
  virtual ~Member_of_commision();

  std::string get(std::string param) const override;
  void set(std::string param, std::string value) override;

  Member_of_commision &operator=(const Member_of_commision &other);

  // Comparison operators
  bool operator<(const Member_of_commision &other) const;
  bool operator>(const Member_of_commision &other) const;
  bool operator==(const Member_of_commision &other) const;

  void printHeader(std::ostream &os) const override;
  static void printInputPrompt();

  friend std::ostream &operator<<(std::ostream &os,
                                  const Member_of_commision &s);
  friend std::istream &operator>>(std::istream &is, Member_of_commision &s);
};
#endif
