# Setup Guide

Quick guide to build and flash this project to your Raspberry Pi Pico.

## Prerequisites

### Install Tools
```bash
# Ubuntu/Debian
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib git

# macOS
brew install cmake
brew tap ArmMbed/homebrew-formulae
brew install arm-none-eabi-gcc
```

### Get Pico SDK
```bash
cd ~
git clone https://github.com/raspberrypi/pico-sdk.git
cd pico-sdk
git submodule update --init
export PICO_SDK_PATH=~/pico-sdk
```

Add to your `~/.bashrc` or `~/.zshrc`:
```bash
export PICO_SDK_PATH=~/pico-sdk
```

## Build

```bash
cd MazeRacers-Sensors
mkdir build && cd build
cmake ..
make
```

This produces `MazeRacers.uf2` in the build directory.

## Flash to Pico

1. Hold the BOOTSEL button on your Pico
2. Connect the USB cable (while still holding BOOTSEL)
3. Release BOOTSEL - Pico appears as USB drive "RPI-RP2"
4. Copy the UF2 file:
   ```bash
   cp MazeRacers.uf2 /media/$USER/RPI-RP2/
   ```
5. Pico automatically reboots and runs your code

## Hardware Wiring

### I²C Connection (Pico → PCA9685)
| Pico Pin | PCA9685 Pin | Notes |
|----------|-------------|-------|
| GP4 (SDA) | SDA | Add 4.7kΩ pull-up to 3.3V |
| GP5 (SCL) | SCL | Add 4.7kΩ pull-up to 3.3V |
| 3.3V | VCC | |
| GND | GND | |

### Ultrasonic Sensor (Pico → HC-SR04)
| Pico Pin | Sensor Pin |
|----------|------------|
| GP2 | TRIG |
| GP3 | ECHO |
| 5V | VCC |
| GND | GND |

### Important Notes
- **Pull-up resistors are required** for I²C communication
- Use 5V for the ultrasonic sensor
- Separate power supply recommended for motors

## Troubleshooting

**Code won't compile:**
- Verify `PICO_SDK_PATH` is set: `echo $PICO_SDK_PATH`
- Check all dependencies are installed
- Try `rm -rf build && mkdir build && cd build && cmake .. && make`

**Pico doesn't show up as USB drive:**
- Try a different USB cable (some are power-only)
- Hold BOOTSEL longer before connecting
- Try a different USB port

**Motors don't respond:**
- Check I²C pull-up resistors (4.7kΩ)
- Verify PCA9685 power LED is on
- Check all wiring connections
- Use a multimeter to verify voltages

## Resources

- [Pico Getting Started Guide](https://datasheets.raspberrypi.com/pico/getting-started-with-pico.pdf)
- [Pico C SDK Documentation](https://raspberrypi.github.io/pico-sdk-doxygen/)
- [RP2040 Datasheet](https://datasheets.raspberrypi.com/rp2040/rp2040-datasheet.pdf)
