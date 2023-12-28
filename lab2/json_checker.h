#ifndef JSON_CHECKER_H
#define JSON_CHECKER_H

#include <iostream>
#include "Json_errors.h"

class Json_checker {
private:
    std::string error_message;
private:
    std::string json_text;
    std::string correct_symbols = "-.0123456789";
    int string_index;
    int pos_in_file;
    int pos_in_line;
    void skip_empty_space();
    void check_object();
    void check_string();
    void check_special_type();
    void check_number();
    void check_array();
public:
    Json_checker(const std::string& json_txt);
    void check_json();
    std::string assign_error() const;
};

class Object_elements {
public:
    bool key;
    bool value;
    bool colon;
    bool comma;
    bool cls_bracket;
    void move_to_key();
    void move_to_colon();
    void move_to_value();
    void move_to_comma();
    void move_to_cls_sq_bracket();
};



#endif // JSON_CHECKER_H
