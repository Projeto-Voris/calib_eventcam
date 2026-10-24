#pragma once
#include <map>
#include <memory>

#include "command.h"

/// Console menu built from registered commands. Adding a feature = registering a new Command.
class Menu {
public:
    explicit Menu(AppContext &ctx) : ctx_(ctx) {}

    Menu &add(char key, std::unique_ptr<Command> cmd) {
        commands_[key] = std::move(cmd);
        return *this;
    }

    void run();

private:
    void show() const;

    AppContext &ctx_;
    std::map<char, std::unique_ptr<Command>> commands_;
};
