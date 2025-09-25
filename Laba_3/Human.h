#ifndef HUMAN_H
#include <string>
class Human
{
private:
  std::string name;
  std::string surname;
  std::string birthday;

public:
  Human();
  Human(std::string name, std::string surname, std::string birthday);
  Human(const Human &other);
  ~Human();

  virtual std::string get(std::string param) const;
  virtual void set(std::string param, std::string value);

  Human &operator=(const Human &other);
  friend std::ostream &operator<<(std::ostream &os,
                                  const Human &s); // перегрузка оператора <<
  friend std::istream &operator>>(std::istream &is,
                                  Human &s); // перегрузка оператора >>
};
#endif // !HUMAN_H
