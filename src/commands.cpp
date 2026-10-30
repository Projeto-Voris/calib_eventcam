#include "commands.h"

#include <iostream>
#include <metavision/sdk/base/utils/log.h>
#include <metavision/sdk/driver/camera.h>

#include "argv_builder.h"
#include "calibration_steps.h"

void TestConnectionCommand::run(AppContext &) {
    try {
        auto camera = Metavision::Camera::from_first_available();
        const auto cfg = camera.get_camera_configuration();
        std::cout << "Camera conectada:\n****************************\n"
                  << " - Serial number: " << cfg.serial_number << "\n"
                  << " - Firmware: " << cfg.firmware_version << "\n"
                  << " - Fabricante: " << cfg.integrator << "\n"
                  << "****************************\n";
    } catch (const Metavision::CameraException &e) {
        MV_LOG_ERROR() << e.what();
        std::cout << "Camera nao conectada!!!\n";
    }
}

void FocusCommand::run(AppContext &ctx) {
    std::cout << " Chamando funcao para ajustar o foco...\n";
    ArgvBuilder args("blink-pattern");
    args.add("--pattern-image-path", ctx.config.files.pattern_image);
    blinking_pattern_focus(args.argc(), args.argv(), ctx.biases);
}

void RecordFramesCommand::run(AppContext &ctx) {
    const auto &c = ctx.config.calibration;
    std::cout << "Chamando funcao para captura de frames....\n";
    ArgvBuilder args(c.program_name);
    args.add("--pattern-type", c.pattern_type)
        .add("--cols", c.cols)
        .add("--rows", c.rows)
        .add("-o", ctx.config.files.output_path);
    calibration_recording(args.argc(), args.argv(), ctx.biases);
}

void ComputeIntrinsicsCommand::run(AppContext &ctx) {
    const auto &c = ctx.config.calibration;
    ArgvBuilder args(c.program_name);
    args.add("-i", ctx.config.files.output_path);
    if (c.refine_calibration)
        args.add("-r", "REFINE_AND_SHOW_IMAGES");
    extract_intrinsics_parameters(args.argc(), args.argv());
}

void ReloadParamsCommand::run(AppContext &ctx) {
    if (!ctx.config.load())
        std::cout << " [Erro] Nao foi possivel carregar o arquivo: " << ctx.config.files.params_file << "\n";
}
