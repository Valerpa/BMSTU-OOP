#ifndef SYSTEM_ERRORS_H
#define SYSTEM_ERRORS_H
#include <iostream>
#include <exception>

class System_errors : public std::exception {
private:
    std::string error_message;
public:
    System_errors(const std::string& message) : error_message{message} {}
    const char* what () const noexcept final {
        return error_message.c_str();
    }
};

#endif // SYSTEM_ERRORS_H
