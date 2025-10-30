# RC Car Controller - Complete System

<div align="center">

<img src="Flutter_Part/assets/images/logo.png" alt="RC Car Controller" style="width:150px;">

**A Complete Multi-Mode RC Car System with Bluetooth Control**

[![Flutter](https://img.shields.io/badge/Flutter-3.0+-02569B?logo=flutter)](https://flutter.dev)
[![ESP32](https://img.shields.io/badge/ESP32-Arduino-00979D?logo=espressif)](https://www.espressif.com)
[![ATmega32](https://img.shields.io/badge/ATmega32-AVR-E34F26?logo=microchip)](https://www.microchip.com)

**Developed by Eng. Gemy | ITI Intake 46**

</div>

---

## 🎯 Project Overview

This is a comprehensive **4-mode RC Car Control System** that combines modern mobile app development, IoT communication, and embedded systems programming. The project consists of three main components working together to provide autonomous and manual control capabilities.

### 🚗 What Does It Do?

The RC car can operate in four different modes:
- **MODE 1**: Manual control via mobile app (Forward, Backward, Left, Right)
- **MODE 2**: Autonomous obstacle avoidance using ultrasonic sensor
- **MODE 3**: Line following using IR sensors
- **MODE 4**: Maze solving with pathfinding algorithms

---

## 🏗️ System Architecture

```
┌─────────────────────────────────────────────────────────────────────┐
│                         SYSTEM OVERVIEW                             │
└─────────────────────────────────────────────────────────────────────┘

     ┌──────────────┐                             ┌──────────────┐
     │              │             Bluetooth       │              │
     │   Flutter    │◄───────────────────────────►│    ESP32     │
     │  Mobile App  │     Commands & Status       │   Dev Module │
     │              │                             │              │
     └──────────────┘                             └───────┬──────┘
                                                          │
                                                    UART1 │ (TX/RX)
                                                  115200 baud
                                                          │
                                                   ┌──────▼──────┐
                                                   │  ATmega32   │
                                                   │     MCU     │
                                                   │  (40-pin)   │
                                                   └──────┬──────┘
                                                          │
                          ┌───────────────────────────────┼─────────────────┼───────────────┐
                          │                               │                 │               │
                    ┌─────▼──────┐                ┌───────▼─────┐     ┌─────▼──────┐  ┌─────▼───────┐
                    │   L298N    │                │    Servo    │     │    3x IR   │  │   Sensors   │
                    │  H-Bridge  │                │    Motor    │     └────────────┘  │  Ultrasonic │ 
                    │   Motor    │                │  (Direction)│                     └─────────────┘
                    │   Driver   │                └─────────────┘                    
                    └─────┬──────┘                                   
                          │
                    ┌─────┴──────┐
                    │            │
                  Motor       Motor
                  Left        Right
                 (Rear)      (Rear)


          ┌──────────────────────────────────────────────┐
          │               POWER DISTRIBUTION             │
          │----------------------------------------------│
          │         Battery 12.0V                        │
          │                │                             │
          │         ┌──────┴──────┐                      │
          │         │             │                      │
          │    ┌────▼────┐   ┌────▼───┐                  │
          │    │ H-Bridge│   |  Buck  |                  | 
          |    │  L298N  │   │ Convert|                  |
          │    │ 12V In  │   │ 5V Out │                  │
          │    └────┬────┘   └───┬────┘                  │
          │         |            |                       │
          │         │            │                       │
          │      2x DC     ┌─────┴───┼──────────┐        │
          │      Motors    │         |          │        │
          │           ┌────▼───┐ ┌───▼────┐ ┌───▼──────┐ |        
          │           │ ESP32  │ │ATmega32│ |  Servo   | |      
          │           │  (5V)  │ │  (5V)  │ |  3x IR   | |     
          │           └────────┘ └────────┘ |Ultrasonic| │
          |                                 └──────────┘ │
          └──────────────────────────────────────────────┘
```

---

## 📦 Project Components

This project is divided into **three main parts**, each with its own detailed documentation:

### 1️⃣ Flutter Mobile Application
**Location**: `/Flutter_Part/`

**Purpose**: User interface for controlling the RC car

**Key Features**:
- Beautiful gradient UI with dark theme
- 4 operating modes with color-coded buttons
- Real-time Bluetooth communication
- Touch-based directional controls
- Status monitoring and feedback

**📖 Documentation**: [Flutter App README](Flutter_Part/README.md)
- ✅ Complete app screenshots (10+ screens)
- ✅ Installation guide
- ✅ Usage instructions
- ✅ UI/UX details

---

### 2️⃣ ESP32 Bluetooth Bridge
**Location**: `/ESP32_Part/`

**Purpose**: Bluetooth communication hub and command processor

**Key Features**:
- Bluetooth Serial (SPP) server
- UART1 communication to ATmega32
- Command parsing and validation
- Status LED indicator
- Connection monitoring

**📖 Documentation**: [ESP32 README](ESP32_Part/README.md)
- ✅ Pin configuration diagrams
- ✅ Arduino IDE setup
- ✅ Code explanation
- ✅ Bluetooth protocol details

---

### 3️⃣ ATmega32 Motor Controller
**Location**: `/Atmega32_Part/`

**Purpose**: Motor control, servo control, and sensor processing

**Key Features**:
- UART command reception from ESP32
- L298N H-Bridge motor driver control
- Servo motor control for steering/direction
- PWM speed control for DC motors
- Ultrasonic sensor for obstacle detection
- 3x IR sensors for line following
- Autonomous mode algorithms

**📖 Documentation**: [ATmega32 README](Atmega32_Part/README.md)
- ✅ Complete circuit diagrams
- ✅ Motor control code
- ✅ Servo control implementation
- ✅ Sensor integration
- ✅ Algorithm explanations

---

## ✨ System Features

### 📱 Mobile App Features
- 🎨 Modern gradient-based dark UI
- 📡 Bluetooth device discovery and pairing
- 🎮 Touch-based manual control
- 🤖 4 autonomous modes
- 📊 Real-time status monitoring
- 🔒 Safety features (auto-stop, connection monitoring)
- 🌐 Multi-language ready

### 🔌 ESP32 Features
- 📶 Bluetooth SPP (Serial Port Profile)
- 🔄 Single UART port to ATmega32 (9600 baud)
- ⚡ Fast command processing
- 💾 Command queuing and validation
- 🚨 LED status indicators
- 🔁 Auto-reconnect support

### 🎛️ ATmega32 Features
- 🚗 2-wheel drive with servo steering
- ⚙️ PWM speed control (0-255)
- 🎯 Servo motor control (0-180°)
- 📏 Ultrasonic obstacle detection (HC-SR04)
- 👁️ IR line tracking (3 sensors)
- 🧭 Maze navigation algorithms
- ⚠️ Emergency stop capability

---

## 🔧 Complete Hardware Setup

### System Components

#### Electronics
- **1x ESP32 Dev Module**
- **1x ATmega32 Microcontroller** (40-pin DIP)
- **1x L298N H-Bridge Motor Driver Module**
- **2x DC Motors** (6V-12V with wheels) - Rear wheels
- **1x Servo Motor** Front steering
- **1x Ultrasonic Sensor**
- **3x IR Obstacle/Line Sensors**
- **4x 3.7V Li-Po Battery**
- **Jumper wires** (male-to-male, male-to-female)
- **RC Car Chassis** (2WD platform with front steering)
- **Breadboard** (for prototyping)
- **LED indicators**
---

### 🔌 Complete Wiring Diagram

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                     COMPLETE SYSTEM WIRING DIAGRAM                           │
└─────────────────────────────────────────────────────────────────────────────┘

                              POWER DISTRIBUTION
                              ─────────────────
                         4*3.7V Li-Po Battery
                                   │
                    ┌──────────────────────────────────┐
                    │                                  │
              Buck Converter                         Direct       
                (5V, 3A)                            to L298N      
                    │                                12V In           
        ┌─────┼─────┼──────────┼────────────┐          │
        │     |     │          │            │          │
      ESP32   |  ATmega32   Ultrasonic     Servo    2xDC Motors
      (5V)    |   (5V)       (5V)         (5V)         
              |                                 
            3xIR sensors

                         BLUETOOTH & CONTROL
                         ──────────────────

┌──────────────┐                    ┌──────────────────┐
│   Android    │    Bluetooth SPP   │      ESP32       │
│    Phone     │◄──────────────────►│  GPIO 2 (LED)    │
│ (Flutter App)│      Commands      │                  │
└──────────────┘                    └───────┬──────────┘
                                            │
                                      UART1 │ (Single UART)
                                   GPIO 17 (TX1, Pin 30)
                                       115200 baud
                                            │
                                            │
                                    ┌───────▼──────────┐
                                    │    ATmega32      │
                                    │    40-PIN DIP    │
                                    │                  │
                                    │ PD0: RX (Pin 14) │◄── From ESP32 TX
                                    └──────────────────┘


                                    ATmega32 COMPLETE PIN MAPPING
                                    ─────────────────────────────

                                      ATmega32 (40-Pin DIP)
                                ┌─────────────────────────────────┐
                                │                                 │
Ultrasonic TRIG  ◄─ (XCK/T0) PB0│1  ●                         ● 40│PA0 (ADC0)      → DC Motor Right 1
                        (T1) PB1│2  ●                         ● 39│PA1 (ADC1)      → DC Motor Right 2
                 (INT2/AIN0) PB2│3  ●                         ● 38│PA2 (ADC2)      → DC Motor left 1
                  (OC0/AIN1) PB3│4  ●      ATmega32           ● 37│PA3 (ADC3)      → DC Motor left 2
                        (SS) PB4│5  ●      40-PIN DIP         ● 36│PA4 (ADC4)      → IR sensor left
                      (MOSI) PB5│6  ●                         ● 35│PA5 (ADC5)      → IR sensor center
                      (MISO) PB6│7  ●                         ● 34│PA6 (ADC6)      → IR sensor right
                       (SCK) PB7│8  ●                         ● 33│PA7 (ADC7)      
              5V ◄─        RESET│9  ●                         ● 32│AREF           
              5V ◄─          VCC│10 ●                         ● 31│GND            
             GND ◄─          GND│11 ●                         ● 30│AVCC           
                           XTAL2│12 ●                         ● 29│PC7 (TOSC2)    
                           XTAL1│13 ●                         ● 28│PC6 (TOSC1)    
   From ESP32 TX ◄─    (RXD) PD0│14 ●                         ● 27│PC5 (TDI)      
                       (TXD) PD1│15 ●                         ● 26│PC4 (TDO)      
 Ultrasonic ECHO ◄─   (INT0) PD2│16 ●                         ● 25│PC3 (TMS)     
                      (INT1) PD3│17 ●                         ● 24│PC2 (TCK)      
 Servo Motor PWM ◄─   (OC1B) PD4│18 ●                         ● 23│PC1 (SDA)     
                      (OC1A) PD5│19 ●                         ● 22│PC0 (SCL)      
                       (ICP) PD6│20 ●                         ● 21│PD7 (OC2)      
                                │                                 │
                                └─────────────────────────────────┘



                         MOTOR DRIVER CONNECTIONS
                         ────────────────────────

                    ┌─────────────────────────┐
                    │    L298N H-Bridge       │
                    │    Motor Driver         │
                    ├─────────────────────────┤
                    │                         │
          IN1 ◄─────┤ PA0 (Pin 1)             │
          IN2 ◄─────┤ PA1 (Pin 2)             │
          IN3 ◄─────┤ PA2 (Pin 3)             │
          IN4 ◄─────┤ PA3 (Pin 4)             │
          ENA ◄─────┤ 5V (Max speed) PWM      │
          ENB ◄─────┤ 5V (Max speed) PWM      │
                    │                         │
       4*3.7V ◄─────┤ Battery                 │
          GND ◄─────┤ Common Ground           │
          5V  ──────┤ To ESP32 & ATmega32     │
                    └─────────────────────────┘


                         SERVO MOTOR CONNECTION
                         ─────────────────────

                    ┌──────────────────────────┐
                    │   Servo Motor (SG90)     │
                    ├──────────────────────────┤
                    │                          │
          Signal ◄──┤ (OC1B) PD4 PWM ATmega32  │ 
          VCC   ◄───┤ 5V from Buck Converter   │
          GND   ◄───┤ Common Ground            │
                    └──────────────────────────┘

                    Function: Front wheel steering
                    Angle: 0° (Left), 90° (Center), 180° (Right)


                         SENSOR CONNECTIONS
                         ─────────────────

                    ULTRASONIC SENSOR (HC-SR04)
                    ──────────────────────────
                    ┌──────────────────────────┐
                    │      HC-SR04             │
                    ├──────────────────────────┤
                    │                          │
          VCC   ◄───┤ 5V Power                 │
          TRIG  ◄───┤ (XCK/T0) PB0 ATmega32    │
          ECHO  ─►──┤ (INT0)   PD2 ATmega32    │
          GND   ◄───┤ Common Ground            │
                    └──────────────────────────┘

                    Function: Obstacle detection (MODE 2)
                    Range: 2cm - 400cm
                    Trigger: 10µs pulse
                    Echo: Returns pulse width


                    IR SENSORS (Line Following)
                    ──────────────────────────

                    ┌────────────────────────────────────────┐
                    │  IR1 (Left)   IR2 (Center)  IR3 (Right)│
                    ├────────────────────────────────────────┤
                    │                                        │
          VCC   ◄───┤ 5V Power (all 3 sensors)               │
          OUT   ─►──┤ PA6          ───────────┐              │
          OUT   ─►──┤ PA5          ────────┐  │              │
          OUT   ─►──┤ PA4          ─────┐  │  │              │
          GND   ◄───┤ Common Ground     │  │  │              │
                    └───────────────────┼──┼──┼──────────────┘
                                        │  │  │
                                        │  │  └─► ATmega32  (Right Sensor)
                                        │  └────► ATmega32  (Center Sensor)
                                        └───────► ATmega32  (Left Sensor)

                    Function: Line detection (MODE 3)
                    Output: Digital (0 = White, 1 = Black)
                    Detection Range: 2-10cm
```

---

## 🎥 Demo Video

🎬 **Watch the full RC Car Test Video**
👉 [Click Here to View Demo](Flutter_Part/docs/screenshots/rc_car.mp4)
---
