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
    std::cout << "Reading file: " << files.params_file << " ...\n";

    try {
        const YAML::Node y = YAML::LoadFile(files.params_file);

        auto &c = calibration;
        read(y, "program_name", c.program_name);
        read(y, "pattern_type", c.pattern_type);
        read(y, "cols", c.cols);
        read(y, "rows", c.rows);
        read(y, "square_size", c.square_size);
        read(y, "refine_calibration", c.refine_calibration);
        read(y, "project_pattern", c.project_pattern);
        read(y, "output_path", files.output_path);
        read(y, "pattern_image", files.pattern_image);
    } catch (const YAML::BadFile &) {
        return false;
    } catch (const YAML::Exception &e) {
        std::cerr << "[Error] Invalid YAML value at " << files.params_file << ": " << e.what() << "\n";
        return false;
    }

    const auto &c = calibration;
    std::cout << " - Calibration pattern: " << c.pattern_type << "\n"
              << " - Number of columns: " << c.cols << "\n"
              << " - Number of lines: " << c.rows << "\n"
              << " - Square size: " << c.square_size << "\n"
              << " - Output path: " << files.output_path << "\n";
    return true;
}
