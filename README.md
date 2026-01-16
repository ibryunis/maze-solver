# 🤖 Autonomous Maze-Solving Robot

An autonomous robot car built with Raspberry Pi Pico that navigates complex mazes using ultrasonic sensors. Developed as part of the Autonomous Systems module at Saxion University of Applied Sciences.

## Overview

This robot autonomously navigates through mazes without any human intervention. It uses ultrasonic sensors to detect walls, makes intelligent turning decisions, and successfully completes maze challenges including finding the treasure chamber and returning to the start.

## Features

- **Autonomous Navigation** - Drives forward, backward, and laterally without human control
- **Obstacle Avoidance** - Detects walls using HC-SR04 ultrasonic sensor (15cm threshold)
- **Precise Turning** - Executes 90° and 180° turns with calibrated timing
- **Complete Maze Solving** - Successfully navigates from entry to treasure chamber and back
- **Extended Battery Life** - Operates for 30+ minutes on single charge

## Tech Stack

- **Hardware**: Raspberry Pi Pico (RP2040)
- **Language**: C++
- **Build System**: CMake
- **Motor Control**: PCA9685 PWM controller via I²C
- **Sensors**: HC-SR04 Ultrasonic distance sensor
- **Communication**: I²C protocol for motor control

## Hardware Components

- Raspberry Pi Pico
- PCA9685 16-channel PWM driver
- HC-SR04 Ultrasonic sensor
- L298N Motor drivers
- 4x DC motors
- 7.4V LiPo battery

## How It Works

The robot continuously reads distance measurements from the ultrasonic sensor. When an obstacle is detected within 15cm, it stops, backs up, performs a 180° turn, and continues in a new direction. This simple but effective algorithm allows it to navigate complex mazes without getting stuck.

```cpp
// Core navigation loop
while (true) {
    float distance = ReadDistance();
    if (distance < OBSTACLE_CM) {
        StopMotors();
        MoveBackward();
        Turn180();
        MoveForward();
    } else {
        MoveForward();
    }
}
```

## Building & Running

### Prerequisites
```bash
# Install ARM toolchain and CMake
sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi

# Set up Pico SDK
git clone https://github.com/raspberrypi/pico-sdk.git
export PICO_SDK_PATH=/path/to/pico-sdk
```

### Build
```bash
cd MazeRacers-Sensors
mkdir build && cd build
cmake ..
make
```

### Flash to Pico
1. Hold BOOTSEL button on Pico
2. Connect USB cable
3. Copy `MazeRacers.uf2` to the Pico drive
4. Pico will automatically reboot and start running

## Project Structure

```
MazeRacers-Sensors/
├── MazeRacers.cpp          # Main entry point
├── library/
│   ├── objects/            # RobotCar, Servo, Timer classes
│   ├── devices/            # Motor and PWM drivers
│   └── config/             # Hardware configuration
└── CMakeLists.txt          # Build configuration
```

## Pin Configuration

| Component | Pico Pin |
|-----------|----------|
| PCA9685 SDA | GP4 (I²C0 SDA) |
| PCA9685 SCL | GP5 (I²C0 SCL) |
| Ultrasonic TRIG | GP2 |
| Ultrasonic ECHO | GP3 |

**Note**: I²C lines require 4.7kΩ pull-up resistors to 3.3V.

## Team

**Team 35**
- Alnur Suleimenov
- Yaroslav Mitev
- Yunis Ibrahimov
- Abdihamid Mohamad Hashi
- Thijs Kaarls

**Project Details**
- Institution: Saxion University of Applied Sciences, Enschede
- Program: Applied Computer Science (Year 1)
- Period: April 2024 - May 2024
- Course: Autonomous Systems Module

---

*Developed as part of the first-year Autonomous Systems module, this project demonstrates embedded systems programming, hardware integration, and autonomous navigation algorithms.*
