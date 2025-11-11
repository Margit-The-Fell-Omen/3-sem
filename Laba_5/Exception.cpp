#include "Exception.h"

// Конструктор по умолчанию
Exception::Exception()
    : code(0), type(ExceptionTypes::GENERIC),
      errorMessage("An unknown error occurred.")
{
}

// Параметризованный конструктор
Exception::Exception(int code, ExceptionTypes type, const std::string &message)
    : code(code), type(type), errorMessage(message)
{
}

// Конструктор копирования
Exception::Exception(const Exception &other)
    : code(other.code), type(other.type), errorMessage(other.errorMessage)
{
}

// Деструктор (может быть пустым, главное, что он виртуальный)
Exception::~Exception() {}

// Геттер для сообщения
const char *Exception::GetMessage() const { return errorMessage.c_str(); }

// Геттер для кода ошибки
int Exception::GetCode() const { return code; }

// Геттер для типа исключения
ExceptionTypes Exception::GetType() const { return type; }
