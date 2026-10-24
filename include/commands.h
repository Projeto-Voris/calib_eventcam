#pragma once
#include "command.h"

class TestConnectionCommand : public Command {
public:
    std::string label() const override { return "Testar conexao com a SilkyEvCam"; }
protected:
    void run(AppContext &ctx) override;
};

class FocusCommand : public Command {
public:
    std::string label() const override { return "Ajustar foco da lente"; }
protected:
    bool requires_biases() const override { return true; }
    void run(AppContext &ctx) override;
};

class RecordFramesCommand : public Command {
public:
    std::string label() const override { return "Calibracao - Aquisicao de frames"; }
protected:
    bool requires_biases() const override { return true; }
    void run(AppContext &ctx) override;
};

class ComputeIntrinsicsCommand : public Command {
public:
    std::string label() const override { return "Calibracao - Gerar parametros intrinsecos"; }
protected:
    void run(AppContext &ctx) override;
};

class ShowBiasesCommand : public Command {
public:
    std::string label() const override { return "Exibir biases do .yaml"; }
protected:
    bool requires_biases() const override { return true; }
    void run(AppContext &) override {}
};

class ReloadParamsCommand : public Command {
public:
    std::string label() const override { return "Ler parametros do .yaml"; }
protected:
    void run(AppContext &ctx) override;
};
