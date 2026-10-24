#pragma once
#include <string>

#include "app_context.h"

/// A menu action. Template Method: execute() handles common steps (screen, biases, pause),
/// subclasses only implement run().
class Command {
public:
    virtual ~Command() = default;

    virtual std::string label() const = 0;

    void execute(AppContext &ctx);

protected:
    /// Override to return true if the command needs biases freshly loaded from disk.
    virtual bool requires_biases() const { return false; }

    virtual void run(AppContext &ctx) = 0;
};
