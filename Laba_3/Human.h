#ifndef HUMAN_H
#define HUMAN_H
#include <string>
#include <iostream>

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

    // Виртуальная функция вывода шапки таблицы
    virtual void printHeader(std::ostream &os) const;

    // Перегрузки ввода-вывода
    friend std::ostream &operator<<(std::ostream &os, const Human &s);
    friend std::istream &operator>>(std::istream &is, Human &s);
};
#endif
