#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <iostream>
#include <exception>

class My_exception : public std::exception {
private:
    std::string message;
public:
    My_exception(const std::string &message) : message{message} {}
    const char* what() const noexcept final {
        return message.c_str();
    }
};

class Range_exception : public My_exception {
public:
    Range_exception() : My_exception("index out of range!") {}
    Range_exception(const std::string &message) : My_exception(message) {}
};

class List_size_exception : public My_exception {
public:
    List_size_exception() : My_exception("empty list!") {}
    List_size_exception(const std::string &message) : My_exception(message) {}
};

class Array_exception : public My_exception {
public:
    Array_exception() : My_exception("array size must be positive!") {}
    Array_exception(const std::string &message) : My_exception(message) {}
};

#endif // EXCEPTIONS_H
