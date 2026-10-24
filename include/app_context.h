#pragma once
#include "app_config.h"
#include "bias_settings.h"

/// State shared by all commands.
struct AppContext {
    AppConfig    config;
    BiasSettings biases;

    bool reload_biases() { return biases.load_from_file(config.files.bias_file); }
};
