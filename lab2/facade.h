#ifndef FACADE_H
#define FACADE_H
#include <iostream>
#include "work_with_file.h"
#include "json_checker.h"

class Facade {
private:
    Work_with_file file_worker;
public:
    std::string read_operation(const std::string& fp);
    std::string check_operation(const std::string& ft);
};

#endif // FACADE_H
