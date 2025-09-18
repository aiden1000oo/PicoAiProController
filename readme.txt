# Pico AI Pro Controller (Switch Ready)

This project turns a Raspberry Pi Pico into a Nintendo Switch Pro Controller clone
that plays entirely by itself using a simple AI.

## Features
- Appears as an official Pro Controller (VID=0x057E, PID=0x2009).
- HID descriptor matches Pro Controller layout (16 buttons, hat, 2 sticks).
- Reports are 64 bytes (padded) as required by the Switch.
- AI-driven inputs: FSM + randomizer + TinyML hook.

## Build
1. Install Pico SDK + TinyUSB (with submodules).
2. cmake -B build -S . -DPICO_SDK_PATH=$PICO_SDK_PATH
3. make -C build
4. Flash .uf2 to Pico.

## Usage
Plug into Nintendo Switch: it shows up as a Pro Controller, AI plays automatically.
