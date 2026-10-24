#pragma once
#include <string>

/// Paths used by the application.
struct FilePaths {
    std::string bias_file   = "../cfg/settings.yaml";
    std::string params_file = "../cfg/params.yaml";
    std::string output_file = "../data_calibration";
    std::string path_data;
    std::string pattern_image = "assets/blink-pattern.jpg";
};

/// Calibration procedure settings (loaded from params.yaml).
struct CalibrationSettings {
    std::string program_name       = "calib_cam_1.0";
    std::string pattern_type       = "CHESSBOARD";
    int         cols               = 9;
    int         rows               = 6;
    float       square_dist        = 0.05f;
    bool        refine_calibration = false;
    bool        project_pattern    = true;
};

struct AppConfig {
    FilePaths           files;
    CalibrationSettings calibration;

    /// Loads params.yaml (path taken from files.params_file). Missing keys keep their defaults.
    bool load();
};
