#ifndef PREPOD_H
#define PREPOD_H
#include "Human.h"
#include <string>
#include <iostream>

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

    void printHeader(std::ostream &os) const override;

    friend std::ostream &operator<<(std::ostream &os, const Prepod &s);
    friend std::istream &operator>>(std::istream &is, Prepod &s);
};
#endif
