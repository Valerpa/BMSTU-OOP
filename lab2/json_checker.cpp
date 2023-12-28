#include "json_checker.h"

Json_checker::Json_checker(const std::string& json_txt) : error_message{"File is correct!"}, json_text{json_txt}, string_index(0), pos_in_file(1), pos_in_line(1) {}

void Json_checker::check_json() {
    skip_empty_space();
    if (json_text[string_index] == '{') {
        check_object();
    }
    else {
        Json_errors error("incorrect object symbol", "\"{\"", pos_in_file, pos_in_line);
        error_message = error.read_error();
        return;
    }
}

void Json_checker::skip_empty_space() {
    while (json_text[string_index] == ' ' || json_text[string_index] == '\n' || json_text[string_index] == '\t') {
        if (json_text[string_index] == '\n') {
            pos_in_file++;
            pos_in_line = 1;
        }
        else {
            pos_in_line++;
        }
        string_index++;
    }
}

void Json_checker::check_object() {
    string_index++;
    skip_empty_space();
    Object_elements elem;
    elem.move_to_key();
    if (json_text[string_index] == '}') {
        string_index++;
        pos_in_line++;
        return;
    }
    while (json_text[string_index]) {
        skip_empty_space();
        if (elem.key && json_text[string_index] == '"') {
            check_string();
            elem.move_to_colon();
        }
        else if (elem.colon && json_text[string_index] == ':') {
            elem.move_to_value();
            string_index++;
            pos_in_line++;
        }
        else if (elem.value && json_text[string_index] == '"') {
            check_string();
            elem.move_to_comma();
        }
        else if (elem.value && correct_symbols.find(json_text[string_index]) != std::string::npos) {
            check_number();
            elem.move_to_comma();
        }
        else if (elem.value && (json_text[string_index] == 't' || json_text[string_index] == 'f' || json_text[string_index] == 'n')) {
            check_special_type();
            elem.move_to_comma();
        }
        else if (elem.value && json_text[string_index] == '{') {
            check_object();
            elem.move_to_comma();
        }
        else if (elem.value && json_text[string_index] == '[') {
            check_array();
            elem.move_to_comma();
        }
        else if (elem.comma && json_text[string_index] == ',') {
            string_index++;
            pos_in_line++;
            elem.move_to_key();
        }
        else if (elem.comma && json_text[string_index] == '\n') {
            string_index++;
            pos_in_file++;
            pos_in_line = 1;
            elem.move_to_cls_sq_bracket();
        }
        else if (elem.cls_bracket && json_text[string_index] == '}') {
            break;
        }
        else if (elem.comma && json_text[string_index] == '}') {
            break;
        }
        else {
            Json_errors error("incorrect object symbol", "\",\"", pos_in_file, pos_in_line);
            error_message = error.read_error();
            return;
        }
    }
    string_index++;
    pos_in_line++;
}

void Json_checker::check_string() {
    string_index++;
    pos_in_line++;
    while (json_text[string_index] != '"') {
        if (!json_text[string_index] || json_text[string_index] == '\n') {
            Json_errors error("incorrect string", "\"", pos_in_file, pos_in_line);
            error_message = error.read_error();
            return;
        }
        string_index++;
        pos_in_line++;
    }
    string_index++;
    pos_in_line++;

}

void Json_checker::check_special_type() {
    std::string expected_word;
    if (json_text[string_index] == 't') {
        expected_word = "true";
    }
    else if (json_text[string_index] == 'f') {
        expected_word = "false";
    }
    else {
        expected_word = "null";
    }
    for (int i = 0; expected_word[i]; i++) {
        if (expected_word[i] != json_text[string_index]) {
            Json_errors error("incorrect special type", expected_word, pos_in_file, pos_in_line);
            error_message = error.read_error();
            return;
        }
        string_index++;
        pos_in_line++;
    }

}

void Json_checker::check_number() {
    int points_counter = 0;
    int minus_counter = 0;
    while (correct_symbols.find(json_text[string_index]) != std::string::npos) {
        if (json_text[string_index] == '.') {
            points_counter++;
        }
        else if (json_text[string_index] == '-') {
            minus_counter++;
        }
        if (points_counter > 1) {
            Json_errors error("incorrect number", "one \".\"", pos_in_file, pos_in_line);
            error_message = error.read_error();
            return;
        }
        if (minus_counter > 1) {
            Json_errors error("incorrect number", "one \"-\"", pos_in_file, pos_in_line);
            error_message = error.read_error();
            return;
        }
        string_index++;
        pos_in_line++;
    }
}

void Json_checker::check_array() {
    string_index++;
    pos_in_line++;
    bool expected_value = true;
    while (json_text[string_index]) {
        skip_empty_space();
        if (!expected_value && json_text[string_index] == ']') {
            break;
        }
        else if (!expected_value && json_text[string_index] == ',') {
            string_index++;
            pos_in_line++;
            expected_value = true;
        }
        else if (expected_value && json_text[string_index] == '"') {
            check_string();
            expected_value = false;
        }
        else if (expected_value && json_text[string_index] == '[') {
            check_array();
            expected_value = false;
        }
        else if (expected_value && json_text[string_index] == '{') {
            check_object();
            expected_value = false;
        }
        else if (expected_value && (json_text[string_index] == 't' || json_text[string_index] == 'f' || json_text[string_index] == 'n')) {
            check_special_type();
            expected_value = false;
        }
        else if (expected_value && correct_symbols.find(json_text[string_index]) != std::string::npos) {
            check_number();
            expected_value = false;
        }
        else if (expected_value && (json_text[string_index] == ',' || json_text[string_index] == ']')) {
            Json_errors error("incorrect array", "array element", pos_in_file, pos_in_line);
            error.read_error();
            return;
        }
        else if (expected_value && json_text[string_index] != ',') {
            Json_errors error("incorrect array", "\",\"", pos_in_file, pos_in_line);
            error.read_error();
            return;
        }
        else {
            Json_errors error("incorrect array", "\"[\"", pos_in_line, pos_in_file);
            error.read_error();
            return;
        }
    }
    string_index++;
    pos_in_line++;
}

std::string Json_checker::assign_error() const {
    return error_message;
}


void Object_elements::move_to_key() {
    key = true;
    colon = false;
    value = false;
    comma = false;
    cls_bracket = false;
}

void Object_elements::move_to_colon() {
    colon = true;
    key = false;
    value = false;
    comma = false;
    cls_bracket = false;
}

void Object_elements::move_to_value() {
    value = true;
    colon = false;
    key = false;
    comma = false;
    cls_bracket = false;
}

void Object_elements::move_to_comma() {
    comma = true;
    value = false;
    key = false;
    colon = false;
    cls_bracket = false;
}

void Object_elements::move_to_cls_sq_bracket() {
    cls_bracket = true;
    comma = false;
    value = false;
    colon = false;
    key = false;
}
