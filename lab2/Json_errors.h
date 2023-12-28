#ifndef JSON_ERRORS_H
#define JSON_ERRORS_H
#include <iostream>

class Json_errors {
private:
    std::string message;
public:
    Json_errors(const std::string& info, const std::string& expected_str, const int pos_in_file, const int pos_in_line) {
        message = "Error: " + info + " at position: " + std::to_string(pos_in_file) + "," + std::to_string(pos_in_line) + ". " + "Expected: " + expected_str + ".";
    }
    std::string read_error() const {
        return message;
    }
};

#endif // JSON_ERRORS_H
