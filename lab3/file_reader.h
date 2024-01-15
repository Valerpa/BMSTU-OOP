#ifndef FILE_READER_H
#define FILE_READER_H
#include "base_file_reader.h"
#include "normalization_parameters.h"
#include "iostream"
#include "facade_operation_result.h"
#include "fstream"
#include "vector"

class File_reader : public Base_file_reader {
private:
    float get_min_z(const std::vector<std::vector<float>>& data);
    float get_max_z(const std::vector<std::vector<float>>& data);
    std::vector<std::vector<float>> normalize(std::vector<std::vector<float>>& data, Normalization_parameters& parameters);
    std::vector<std::vector<float>> get_data_from_file(const std::string& path);
    std::vector<Vertex>* make_vertices(std::vector<std::vector<float>>& data, const Normalization_parameters params);
    std::vector<Edge>* make_edge(std::vector<Vertex>& vertices, size_t length, size_t width);
public:
    std::shared_ptr<Scene> read_scene(const std::string& path, Normalization_parameters& parameters) override;
};

#endif // FILE_READER_H
