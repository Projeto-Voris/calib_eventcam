#pragma once
#include <string>
#include <vector>

/// Valid range of one bias (SilkyEvCam, Gen3.1 VGA).
/// See https://docs.prophesee.ai/stable/hw/manuals/biases.html
struct BiasRange {
    int min;
    int max;
    bool contains(int v) const { return v >= min && v <= max; }
};

/// Bias values to be written on the camera, plus their validation limits.
class BiasSettings {
public:
    static constexpr int kBiasDiffDefault = 299; // do not change

    int diff     = kBiasDiffDefault;
    int diff_on  = 0;
    int diff_off = 0;
    int fo       = 0;
    int hpf      = 0;
    int refr     = 0;

    /// Returns one message per out-of-range bias (empty if everything is valid).
    std::vector<std::string> validate() const;

    /// Loads values from the settings YAML (ll_biases_state: name: value). Returns false on failure.
    bool load_from_file(const std::string &path);

    static BiasRange diff_on_range()  { return {kBiasDiffDefault + 75, kBiasDiffDefault + 200}; }
    static BiasRange diff_off_range() { return {100, kBiasDiffDefault - 65}; }
    static BiasRange fo_range()       { return {1250, 1800}; }
    static BiasRange hpf_range()      { return {900, 1800}; }
    static BiasRange refr_range()     { return {1300, 1800}; }
};
