#pragma once
#include "Human.h"

class Prepod : public virtual Human
{
protected:
  std::string degree;
  std::string position;
  std::string works;

public:
  Prepod();
  Prepod(std::string degree, std::string position, std::string works);
  Prepod(const Prepod &other);

  std::string get(std::string param) const override;
  void set(std::string param, std::string value) override;
  void printHeader(std::ostream &os) const override;
  bool operator<(const Prepod &other) const;
  bool operator>(const Prepod &other) const;
  bool operator==(const Prepod &other) const;
};

std::istream &operator>>(std::istream &is, Prepod &p);
std::ostream &operator<<(std::ostream &os, const Prepod &p);
