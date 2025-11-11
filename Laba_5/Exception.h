// Exception.h
#pragma once
#include "ExceptionTypes.h"
#include <string>

class Exception
{
protected:
  int code;
  ExceptionTypes type;
  std::string errorMessage;

public:
  // Конструкторы и деструктор
  Exception();
  Exception(int code, ExceptionTypes type, const std::string &message);
  Exception(const Exception &other);

  virtual ~Exception();

  // Методы для получения информации об ошибке
  const char *GetMessage() const;
  int GetCode() const;
  ExceptionTypes GetType() const;
};
