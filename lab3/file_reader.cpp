#include "file_reader.h"

float File_reader::get_min_z(const std::vector<std::vector<float>>& data) {
    float res = data[0][0];
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            if (res > data[i][j]) {
                res = data[i][j];
            }
        }
    }
    return res;
}

float File_reader::get_max_z(const std::vector<std::vector<float>>& data) {
    float res = data[0][0];
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            if (res < data[i][j]) {
                res = data[i][j];
            }
        }
    }
    return res;
}

std::vector<std::vector<float>> File_reader::normalize(std::vector<std::vector<float>>& data, Normalization_parameters& parameters) {
    float minim = get_min_z(data);
    float maxim = get_max_z(data);
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
           data[i][j] = parameters.min + ((data[i][j] - minim) * (parameters.max - parameters.min)) / (maxim - minim);
        }
    }
    return data;
}

std::vector<std::vector<float>> File_reader::get_data_from_file(const std::string& path) {
    std::vector <std::vector<float>> data;
    Facade_operation_result result;
    std::ifstream file(path);
    if (!file.is_open()) {
        result.set_error_message("File was not opened!");
        throw result.get_error_message();
    }
    std::string str;
    while (getline(file, str)) {
        if (str.empty()) {
            result.set_error_message("Line is empty!");
            throw result.get_error_message();
        }
        std::vector<float> row;
        size_t pos = 0;
        float value;
        str.push_back(',');
        while (str.size()) {
            std::string s_value;
            pos = str.find(',');
            s_value = str.substr(0, pos);
            value = stoi(s_value);
            row.push_back(value);
            str.erase(0, pos + 1);
        }
        data.push_back(row);
    }
    file.close();
    return data;
}

std::vector<Vertex>* File_reader::make_vertices(std::vector<std::vector<float>>& data, const Normalization_parameters params) {
    std::vector<Vertex>* res = new std::vector<Vertex>;
    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            Point_3d tmp_point(i * params.dx_step, j * params.dy_step, data[i][j]);
            Vertex tmp_vertex(tmp_point);
            res->push_back(tmp_vertex);
        }
    }
    return res;
}

std::vector<Edge>* File_reader::make_edge(std::vector<Vertex>& vertices, size_t length, size_t width) {
    std::vector<Edge>* res = new std::vector<Edge>;
    for (size_t i = 0; i < length; i++) {
        for (size_t j = 0; j < width; j++) {
            if ((i + 1) < length) {
                Edge horizontal_edge(vertices[width * i + j], vertices[width * (i + 1) + j]);
                res->push_back(horizontal_edge);
            }
            if ((j + 1) < width) {
                Edge vertical_edge(vertices[width * i + j], vertices[width * i + j + 1]);
                res->push_back(vertical_edge);
            }
        }
    }
    return res;
}

std::shared_ptr<Scene> File_reader::read_scene(const std::string& path, Normalization_parameters& parameters) {
    Facade_operation_result res;
    std::vector <std::vector<float>> data = get_data_from_file(path);
    if (data.size() != data[0].size()) {
        res.set_error_message("File is incorrect!");
        throw res.get_error_message();
    }
    data = normalize(data, parameters);
    std::vector<Vertex>* vertices = make_vertices(data, parameters);
    std::vector<Edge>* edges = make_edge(*vertices, data.size(), data[0].size());
    std::vector<Figure> press_f;
    std::unique_ptr<Figure> figa = std::make_unique<Figure>(vertices, edges);
    press_f.push_back(*figa);
    std::shared_ptr<Scene> scene = std::make_shared<Scene>(press_f);
    return scene;
}
