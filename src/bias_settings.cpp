#include "bias_settings.h"

#include <iostream>
#include <stdexcept>
#include <yaml-cpp/yaml.h>

std::vector<std::string> BiasSettings::validate() const {
    std::vector<std::string> errors;
    auto check = [&](const char *name, int v, BiasRange r) {
        if (!r.contains(v))
            errors.push_back(std::string(name) + "=" + std::to_string(v) + " fora de [" +
                             std::to_string(r.min) + ", " + std::to_string(r.max) + "]");
    };
    check("bias_diff_on", diff_on, diff_on_range());
    check("bias_diff_off", diff_off, diff_off_range());
    check("bias_fo", fo, fo_range());
    check("bias_hpf", hpf, hpf_range());
    check("bias_refr", refr, refr_range());
    return errors;
}

bool BiasSettings::load_from_file(const std::string &path) {
    std::cout << "Lendo arquivo: " << path << " ...\n";

    try {
        const YAML::Node y     = YAML::LoadFile(path);
        const YAML::Node biases = y["ll_biases_state"];
        if (!biases || !biases.IsMap()) {
            std::cerr << "[Erro] 'll_biases_state' ausente ou invalido em: " << path << "\n";
            return false;
        }

        auto read = [&](const char *name) {
            const YAML::Node n = biases[name];
            if (!n)
                throw std::runtime_error(std::string("bias ausente: ") + name);
            return n.as<int>();
        };
        diff     = read("bias_diff");
        diff_off = read("bias_diff_off");
        diff_on  = read("bias_diff_on");
        fo       = read("bias_fo");
        hpf      = read("bias_hpf");
        refr     = read("bias_refr");
    } catch (const YAML::BadFile &) {
        return false;
    } catch (const std::exception &e) {
        std::cerr << "[Erro] Falha ao ler biases em " << path << ": " << e.what() << "\n";
        return false;
    }

    std::cout << "bias_diff= " << diff << "\nbias_diff_off= " << diff_off << "\nbias_diff_on= " << diff_on
              << "\nbias_fo= " << fo << "\nbias_hpf= " << hpf << "\nbias_refr= " << refr << "\n";
    for (const auto &w : validate())
        std::cerr << "[Aviso] " << w << "\n";
    return true;
}
