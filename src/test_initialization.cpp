#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <memory>

#include "GCore/Interfaces/IPlatformHardwareInfo.h"
#include "GCore/Templates/TGenericHardwareInfo.h"
#include "GCore/Templates/TBasicDeviceRegistry.h"
#include "GCore/Interfaces/ISonyGamepad.h"
#include "../lib/Gamepad-Core/Examples/Adapters/Tests/test_device_registry_policy.h"
#include "../lib/Gamepad-Core/Examples/Platform_Windows/test_windows_hardware_policy.h"

using namespace GamepadCore;
using TestHardwareInfo = Ftest_windows_platform::Ftest_windows_hardware;
using TestDeviceRegistry = GamepadCore::TBasicDeviceRegistry<Ftest_device_registry_policy>;

int main() {
    std::cout << "--- DualSense Initialization Test ---" << std::endl;

    // 1. Inicializar Hardware Info
    auto HardwareImpl = std::make_unique<TestHardwareInfo>();
    IPlatformHardwareInfo::SetInstance(std::move(HardwareImpl));

    // 2. Inicializar Registro de Dispositivos
    auto Registry = std::make_unique<TestDeviceRegistry>();
    Registry->Policy.deviceId = 0;

    std::cout << "[System] Procurando controles DualSense..." << std::endl;
    Registry->RequestImmediateDetection();
    Registry->PlugAndPlay(2.0f); // Espera até 2 segundos por detecção

    // 3. Aguardar conexão
    ISonyGamepad* Gamepad = nullptr;
    for (int i = 0; i < 50; ++i) {
        Gamepad = Registry->GetLibrary(0);
        if (Gamepad && Gamepad->IsConnected()) {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    if (!Gamepad || !Gamepad->IsConnected()) {
        std::cerr << "[Erro] Nenhum controle DualSense detectado. Verifique a conexao USB ou Bluetooth." << std::endl;
        return 1;
    }

    std::cout << "[Sucesso] Controle conectado via " 
              << (Gamepad->GetConnectionType() == EDSDeviceConnection::Bluetooth ? "Bluetooth" : "USB") 
              << std::endl;

    // 4. Teste de Lightbar (Cores básicas)
    std::cout << "[Teste] Alterando cores do Lightbar..." << std::endl;
    
    DSCoreTypes::FDSColor colors[] = {
        {255, 0, 0},   // Vermelho
        {0, 255, 0},   // Verde
        {0, 0, 255},   // Azul
        {200, 160, 80} // Cor da Config (Skater)
    };

    for (const auto& color : colors) {
        std::cout << "  Definindo cor: R=" << (int)color.R << " G=" << (int)color.G << " B=" << (int)color.B << std::endl;
        Gamepad->SetLightbar(color);
        Gamepad->UpdateOutput();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 5. Teste de Player LED
    std::cout << "[Teste] Testando Player LED..." << std::endl;
    Gamepad->SetPlayerLed(EDSPlayer::One, 255);
    Gamepad->UpdateOutput();
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 6. Teste de Gatilhos Adaptáveis (Resistência)
    std::cout << "[Teste] Aplicando resistencia nos gatilhos (aperte L2/R2 para testar)..." << std::endl;
    auto Trigger = Gamepad->GetIGamepadTrigger();
    if (Trigger) {
        // Exemplo de resistência: Start=0, Strength=255 (máxima)
        Trigger->SetResistance(0, 255, EDSGamepadHand::Left);
        Trigger->SetResistance(0, 255, EDSGamepadHand::Right);
        Gamepad->UpdateOutput();
        
        std::cout << "  Resistencia aplicada. Aguardando 5 segundos..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
        
        std::cout << "  Limpando efeitos dos gatilhos..." << std::endl;
        Trigger->StopTrigger(EDSGamepadHand::Left);
        Trigger->StopTrigger(EDSGamepadHand::Right);
        Gamepad->UpdateOutput();
    } else {
        std::cerr << "  [Aviso] Interface de Gatilhos nao disponivel." << std::endl;
    }

    std::cout << "--- Teste Finalizado ---" << std::endl;
    Registry.reset();

    return 0;
}
