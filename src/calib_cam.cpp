/*
 * Event camera: SilkyEvCam Centuri Arks (VGA).  SDK: Metavision 4.6.2.
 * Entry point: wires configuration and commands together.
 */
#include <iostream>
#include <memory>

#include "app_context.h"
#include "commands.h"
#include "menu.h"
#include "terminal.h"

int main() {
    AppContext ctx;
    terminal::clear();

    if (!ctx.config.load())
        std::cerr << "[Erro] Nao foi possivel carregar o arquivo: " << ctx.config.files.params_file << "\n";
    if (!ctx.reload_biases())
        std::cerr << "[Erro] Nao foi possivel carregar o arquivo: " << ctx.config.files.bias_file << "\n";

    Menu menu(ctx);
    menu.add('1', std::make_unique<TestConnectionCommand>())
        .add('2', std::make_unique<FocusCommand>())
        .add('3', std::make_unique<RecordFramesCommand>())
        .add('4', std::make_unique<ComputeIntrinsicsCommand>())
        .add('5', std::make_unique<ShowBiasesCommand>())
        .add('6', std::make_unique<ReloadParamsCommand>());
    menu.run();
    return 0;
}
