#include "menu.h"

#include <iostream>
#include <limits>

#include "terminal.h"

void terminal::wait_enter() {
    std::cout << "\nDigite \"Enter\" para retornar ao menu:\n";
    std::cin.get();
}

void Menu::show() const {
    std::cout << "\n\n";
    terminal::green(true);
    std::cout << "************** Menu de Calibracao ***************\n";
    terminal::green(false);
    for (const auto &[key, cmd] : commands_)
        std::cout << "\n   " << key << "-> " << cmd->label() << "\n";
    terminal::green(true);
    std::cout << "\n   Q-> Sair\n\n*************************************************\n";
    std::cout << " \033[1m  Digite a opcao: \033[0m";
}

void Menu::run() {
    while (true) {
        terminal::clear();
        show();

        char choice = 0;
        if (!(std::cin >> choice))
            return;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 'q' || choice == 'Q' || choice == 27)
            return;
        if (auto it = commands_.find(choice); it != commands_.end())
            it->second->execute(ctx_);
    }
}
