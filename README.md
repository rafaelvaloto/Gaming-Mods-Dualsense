# DualSense Native Mods (Audio Haptics - Usb/Bluetooth)

![Banner Image](https://github.com/rafaelvaloto/Gaming-Mods-Dualsense/raw/main/banner.png)

## 🚀 Native Bluetooth Audio Haptics Mod
This project brings **native DualSense Audio Haptics support over Bluetooth** to PC games. 

Unlike other solutions, **this does NOT require paid software** like DSX running in the background. The logic is embedded directly into the game process via **[GamepadCore](https://github.com/rafaelvaloto/gamepad-core)**.

### ✨ Features
* **🔊 Audio Haptics over Bluetooth:** Captures game audio and converts it to HD vibration in real-time. Works wirelessly!
* **🎮 Plug & Play:** No complex configuration needed.
---

## 🛹 Session: Skate Sim Mod (Special Edition)
This version is tailored specifically for *Session: Skate Sim*.

* **Truck Physics on Triggers:** The Adaptive Triggers stiffen to simulate the resistance of the skate trucks. The harder you turn, the harder the trigger gets.
* **Texture Feel:** Feel the pop, the landing, and the grind through audio-based haptics.

### Installation (Session)
1.  Download and install **[ViGEmBus](https://github.com/nefarius/ViGEmBus/releases)** (Required for controller input).
2.  Download the `session-dualsense-mod.zip` from Releases.
3.  Extract the contents into your game folder (usually `SessionGame\Binaries\Win64\`).
    *   The folder structure should look like this:
        ```
        SessionGame\Binaries\Win64\
        ├── dxgi.dll
        └── UnrealModPlugins\
            └── session-dualsense-mod.dll
        ```
4.  *Ensure your DualSense is paired via Bluetooth or connected via USB.*

---

## 🎧 Generic Audio Haptics Mod (Universal)
This version only enables **Audio Haptics** based on the OS default audio device output. It does not touch triggers or inputs.

* **Use Case:** Use this for games that already support DualSense input natively but lack haptics over Bluetooth, or for any game where you want sound-reactive vibration.
* **Installation:** Inject the DLL into the target process (instructions may vary per game).

---

## 🛠️ For Developers: Build Your Own
These mods are built using the **GamepadCore** library. You can create your own native implementations.

### How it works
1.  **Audio Capture:** The DLL hooks into WASAPI (Windows Audio Session API) to capture the output loopback.
2.  **Processing:** GamepadCore processes the audio buffer.
3.  **Bluetooth Stream:** The processed buffer is sent directly to the DualSense HID endpoints, bypassing standard Windows driver limitations.

### Usage with GamepadCore
To create a custom mod (e.g., adding trigger support for Cyberpunk):

1.  Include `GamepadCore` in your project.
2.  Initialize the DualSense instance.
3.  Use the `IGamepadAudioHaptics` interface to feed the buffer.

---

## ⭐ Credits & Acknowledgments
This project is built with **[Gamepad-Core](https://github.com/rafaelvaloto/gamepad-core)**, an open-source library for native DualSense and DualShock 4 integration.

Special thanks to **[nefarius](https://github.com/nefarius)** for the amazing work on ViGEmBus and for supporting the community, and to all contributors for supporting open-source gaming mods.

## ⚖️ Legal & Trademarks
This software is an independent project and is not affiliated with Sony Interactive Entertainment Inc., Epic Games, Unity Technologies, Godot Engine, Nacon, creā-ture Studios, or any of their subsidiaries.

Trademarks belong to their respective owners:

*   **Sony:** PlayStation, DualSense, DualShock are trademarks of Sony Interactive Entertainment Inc.
*   **Microsoft:** Windows, Xbox are trademarks of Microsoft Corporation
*   **Apple:** macOS is a trademark of Apple Inc.
*   **Epic Games:** Unreal Engine is a trademark of Epic Games, Inc.
*   **Unity:** Unity is a trademark of Unity Technologies
*   **Godot:** Godot and the Godot logo are trademarks of the Godot Engine project
*   **Nacon:** Session: Skate Sim is a trademark of Nacon.
*   **creā-ture Studios:** creā-ture Studios is a trademark of creā-ture Studios Inc.

## 📜 License
This project is licensed under the **MIT License**. See the [LICENSE](LICENSE) file for details.
