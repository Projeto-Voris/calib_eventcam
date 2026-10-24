#pragma once
#include <metavision/sdk/driver/camera.h>

#include "bias_settings.h"

/// Reads/writes biases on a connected camera through the low-level biases facility.
class CameraBiasController {
public:
    explicit CameraBiasController(Metavision::Camera &cam) : cam_(cam) {}

    /// Prints the biases currently set on the camera.
    void print() const;

    /// Writes biases to the camera (on-the-fly, no stop needed). Returns false on failure.
    bool write(const BiasSettings &settings) const;

    /// Prints current values, writes the new ones, then prints the result.
    bool apply(const BiasSettings &settings) const;

private:
    Metavision::Camera &cam_;
};
