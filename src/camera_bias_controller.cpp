#include "camera_bias_controller.h"

#include <iostream>
#include <metavision/hal/facilities/i_ll_biases.h>

void CameraBiasController::print() const {
    auto *ll = cam_.get_device().get_facility<Metavision::I_LL_Biases>();
    if (!ll) {
        std::cerr << "[Erro] Nao foi possivel acessar a interface de Biases do hardware!\n";
        return;
    }
    try {
        std::cout << "\nValores dos biases lidos da eventcam:\n";
        for (const char *name : {"bias_diff_on", "bias_diff_off", "bias_fo", "bias_hpf", "bias_refr"})
            std::cout << " - " << name << ": " << ll->get(name) << "\n";
        std::cout << "\n";
    } catch (const std::exception &e) {
        std::cerr << "[Erro] Nao foi possivel ler os biases na camera: " << e.what() << "\n";
    }
}

bool CameraBiasController::write(const BiasSettings &s) const {
    auto *ll = cam_.get_device().get_facility<Metavision::I_LL_Biases>();
    if (!ll) {
        std::cerr << "[Erro] Nao foi possivel acessar a interface de Biases do hardware!\n";
        return false;
    }
    try {
        ll->set("bias_diff_on", s.diff_on);
        ll->set("bias_diff_off", s.diff_off);
        ll->set("bias_fo", s.fo);
        ll->set("bias_hpf", s.hpf);
        ll->set("bias_refr", s.refr);
    } catch (const std::exception &e) {
        std::cerr << "[Erro] Nao foi possivel gravar biases na camera: " << e.what() << "\n";
        return false;
    }
    const auto cfg = cam_.get_camera_configuration();
    std::cout << "Camera " << cfg.integrator << ": N Serie " << cfg.serial_number << " - Biases atualizados\n";
    return true;
}

bool CameraBiasController::apply(const BiasSettings &s) const {
    print();
    if (!write(s))
        return false;
    print();
    return true;
}
