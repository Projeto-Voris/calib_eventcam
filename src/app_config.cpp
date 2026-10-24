#include "app_config.h"

#include <iostream>
#include <yaml-cpp/yaml.h>

namespace {
// Overwrites `out` only if `key` is present in the node.
template <typename T>
void read(const YAML::Node &n, const char *key, T &out) {
    if (const YAML::Node v = n[key])
        out = v.as<T>();
}
} // namespace

bool AppConfig::load() {
    std::cout << "Lendo arquivo: " << files.params_file << " ...\n";

    try {
        const YAML::Node y = YAML::LoadFile(files.params_file);

        auto &c = calibration;
        read(y, "program_name", c.program_name);
        read(y, "pattern_type", c.pattern_type);
        read(y, "cols", c.cols);
        read(y, "rows", c.rows);
        read(y, "square_dist", c.square_dist);
        read(y, "refine_calibration", c.refine_calibration);
        read(y, "projeta_padrao", c.project_pattern);

        read(y, "output_file", files.output_file);
        read(y, "path_data", files.path_data);
        read(y, "pattern_image", files.pattern_image);
    } catch (const YAML::BadFile &) {
        return false;
    } catch (const YAML::Exception &e) {
        std::cerr << "[Erro] YAML invalido em " << files.params_file << ": " << e.what() << "\n";
        return false;
    }

    const auto &c = calibration;
    std::cout << " - Padrao de calibracao: " << c.pattern_type << "\n"
              << " - N colunas: " << c.cols << "\n"
              << " - N linhas: " << c.rows << "\n"
              << " - Dimensao do quadrado: " << c.square_dist << "\n"
              << " - Arquivo de saida: " << files.output_file << "\n";
    return true;
}
