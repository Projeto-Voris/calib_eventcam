#pragma once
#include "bias_settings.h"

// Entry points adapted from the Metavision SDK samples.
int blinking_pattern_focus(int argc, char *argv[], const BiasSettings &biases);
int calibration_recording(int argc, char *argv[], const BiasSettings &biases);
int extract_intrinsics_parameters(int argc, char *argv[]);
