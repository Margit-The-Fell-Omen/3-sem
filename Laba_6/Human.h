#pragma once
#include <iostream>
#include <string>

class Human
{
protected:
  std::string name;
  std::string surname;
  std::string birthday;

public:
  Human();
  Human(std::string name, std::string surname, std::string birthday);
  virtual ~Human() = default;

  virtual std::string get(std::string param) const;
  virtual void set(std::string param, std::string value);
  virtual void printHeader(std::ostream &os) const;

  bool operator<(const Human &other) const;
  bool operator==(const Human &other) const;
};

// Объявление дружественной функции для перегрузки оператора >>
std::istream &operator>>(std::istream &is, Human &h);
std::ostream &operator<<(std::ostream &os, const Human &h);
