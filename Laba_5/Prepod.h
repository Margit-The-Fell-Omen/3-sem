#ifndef PREPOD_H
#define PREPOD_H
#include "Human.h"
#include <iostream>
#include <string>

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
  virtual ~Prepod();

  std::string get(std::string param) const override;
  void set(std::string param, std::string value) override;

  Prepod &operator=(const Prepod &other);

  // Comparison operators
  bool operator<(const Prepod &other) const;
  bool operator>(const Prepod &other) const;
  bool operator==(const Prepod &other) const;

  void printHeader(std::ostream &os) const override;
  static void printInputPrompt();

  friend std::ostream &operator<<(std::ostream &os, const Prepod &s);
  friend std::istream &operator>>(std::istream &is, Prepod &s);
};
#endif
