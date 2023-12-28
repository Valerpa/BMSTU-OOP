#include "facade.h"

std::string Facade::read_operation(const std::string& fp) {
    return file_worker.parse_file(fp);
}

std::string Facade::check_operation(const std::string& ft) {
    Json_checker json_cheker(ft);
    json_cheker.check_json();
    return json_cheker.assign_error();
}
