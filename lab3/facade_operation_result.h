#ifndef FACADE_OPERATION_RESULT_H
#define FACADE_OPERATION_RESULT_H
#include <iostream>

class Facade_operation_result {
private:
    std::string _error_message;
    bool _is_success;
public:
    Facade_operation_result();
    std::string get_error_message() const;
    bool is_success() const;
    void set_error_message(const std::string& message);

};

#endif // FACADE_OPERATION_RESULT_H
