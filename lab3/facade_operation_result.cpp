#include "facade_operation_result.h"

Facade_operation_result::Facade_operation_result() : _error_message(""), _is_success(true) {}

std::string Facade_operation_result::get_error_message() const {
    return _error_message;
}

bool Facade_operation_result::is_success() const{
    return _is_success;
}

void Facade_operation_result::set_error_message(const std::string& message) {
    _error_message = message;
    if (_error_message != "") {
        _is_success = false;
    }
    else {
        _is_success = true;
    }
}
