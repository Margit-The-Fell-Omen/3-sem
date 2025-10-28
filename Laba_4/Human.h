#ifndef HUMAN_H
#define HUMAN_H
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
  Human(const Human &other);
  virtual ~Human();

  virtual std::string get(std::string param) const;
  virtual void set(std::string param, std::string value);

  Human &operator=(const Human &other);

  // Comparison operators for BinTree
  bool operator<(const Human &other) const;
  bool operator>(const Human &other) const;
  bool operator==(const Human &other) const;

  // Virtual function for output header
  virtual void printHeader(std::ostream &os) const;

  // Overloaded input/output operators
  friend std::ostream &operator<<(std::ostream &os, const Human &s);
  friend std::istream &operator>>(std::istream &is, Human &s);
};
#endif
