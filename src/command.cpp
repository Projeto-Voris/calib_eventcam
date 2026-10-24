#include "command.h"

#include <iostream>

#include "terminal.h"

void Command::execute(AppContext &ctx) {
    terminal::clear();
    if (requires_biases() && !ctx.reload_biases())
        std::cout << "[Erro] Nao foi possivel carregar o arquivo: " << ctx.config.files.bias_file << "\n";
    run(ctx);
    terminal::wait_enter();
}
