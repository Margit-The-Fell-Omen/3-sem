#ifndef PREPOD_FROM_COMMISION_H
#define PREPOD_FROM_COMMISION_H
#include "Member_of_commision.h"
#include "Prepod.h"
#include <iostream>
#include <string>

class Prepod_from_commision : public Prepod, public Member_of_commision
{
private:
  std::string commision_works;

public:
  Prepod_from_commision();
  Prepod_from_commision(std::string name, std::string surname,
                        std::string birthday, std::string degree,
                        std::string position, std::string works,
                        std::string commision_name, std::string biography,
                        std::string commision_works);
  Prepod_from_commision(const Prepod_from_commision &other);
  virtual ~Prepod_from_commision();

  std::string get(std::string param) const override;
  void set(std::string param, std::string value) override;

  Prepod_from_commision &operator=(const Prepod_from_commision &other);

  bool operator<(const Prepod_from_commision &other) const;
  bool operator>(const Prepod_from_commision &other) const;
  bool operator==(const Prepod_from_commision &other) const;

  void printHeader(std::ostream &os) const override;

  friend std::ostream &operator<<(std::ostream &os,
                                  const Prepod_from_commision &s);
  friend std::istream &operator>>(std::istream &is, Prepod_from_commision &s);
};
#endif
