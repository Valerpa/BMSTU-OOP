#ifndef BASE_FILE_READER_H
#define BASE_FILE_READER_H
#include "scene.h"
#include "normalization_parameters.h"
#include <memory>

class Base_file_reader {
public:
    virtual std::shared_ptr<Scene> read_scene(const std::string& path, Normalization_parameters& parameters) = 0;
    virtual ~Base_file_reader() {}
};

#endif // BASE_FILE_READER_H
