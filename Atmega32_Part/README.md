
# 🚗 ATmega32 Smart RC Car Firmware

This firmware powers a **Smart RC Car** controlled via **ESP32 Bluetooth**.
The ATmega32 acts as the main **embedded controller**, executing motion, sensing, and autonomous algorithms for four operation modes: **Manual**, **Obstacle Avoidance**, **Line Follower**, and **Maze Solver**.

---

## 🧱 Project Architecture

The firmware follows a **layered architecture**, organized as follows:

```
├── APP/                # Application Layer (high-level logic)
│   ├── CarMove.c/h          # Motor movement control interface
│   ├── Eyes.c/h             # Ultrasonic + Servo scanning control
│   ├── LineFollower.c/h     # Line following algorithm
│   ├── ModesHandler.c/h     # Mode selection & coordination
│
├── HAL/                # Hardware Abstraction Layer
│   ├── DCMOT_Driver/        # DC motor driver (L298N/L293D)
│   ├── IR_SENSOR_Driver/    # Infrared sensor driver
│   ├── SERVMOT_Driver/      # Servo motor driver
│   ├── ULTRASONIC_Driver/   # Ultrasonic sensor driver
│
├── MCAL/               # Microcontroller Abstraction Layer
│   ├── DIO_Driver/          # Digital I/O control
│   ├── ICU_Driver/          # Input Capture Unit (for ultrasonic timing)
│   ├── TIMER0_Driver/       # PWM for servo or timing tasks
│   ├── TIMER1_Driver/       # Timer used by ultrasonic driver
│   ├── UART_Driver/         # Communication with ESP32
│
├── LIB/                # Utility libraries
│   ├── BIT_MATH.h           # Common bit manipulation macros
│   ├── STD_TYPES.h          # Standard data types (u8, u16, etc.)
│
└── main.c              # System initialization and main control loop
```

---

## 🧠 System Overview

* **ESP32** handles Bluetooth communication and sends control commands (F, B, L, R, S, 1–4) over UART.
* **ATmega32** executes the commands by controlling DC motors, ultrasonic sensor, IR sensors, and servo motors.
* **ModesHandler** coordinates the behavior for each operating mode.

---

## ⚙️ Operating Modes

### 🕹️ Mode 1 – Manual Control

**File:** `CarMove.c/h`
**Description:**

* Direct control via Bluetooth commands (`F`, `B`, `L`, `R`, `S`).
* The ESP32 sends commands through UART; ATmega32 executes motor movements.
* Uses **DCMOT_Driver** for direction and speed control.

---

### 🚧 Mode 2 – Obstacle Avoidance

**Files:** `Eyes.c/h`, `CarMove.c/h`
**Description:**

* Automatically detects obstacles using ultrasonic sensor.
* The “Eyes” (servo + ultrasonic) scan **forward**, **left**, and **right**.
* Chooses the direction with no wall or longest free distance.
* Threshold distance defined in `Eyes.h` (`EYES_THRESHOLD = 40 cm`).
* Uses **ULTRASONIC_Driver** and **SERVMOT_Driver** for sensing and servo movement.

---

### ⚫ Mode 3 – Line Follower

**Files:** `LineFollower.c/h`
**Description:**

* Uses two or more **IR sensors** to detect a black line.
* Logic:

  * Left sensor active → Turn left
  * Right sensor active → Turn right
  * Both active → Move forward
  * None active → Stop
* Uses **IR_SENSOR_Driver** and **DCMOT_Driver**.

---

### 🧠 Mode 4 – Maze Solver
Not now

---

## 🔄 UART Command Table

| Command | Description             |
| ------- | ----------------------- |
| `F`     | Move Forward            |
| `B`     | Move Backward           |
| `L`     | Turn Left               |
| `R`     | Turn Right              |
| `S`     | Stop                    |
| `1`     | Manual Mode             |
| `2`     | Obstacle Avoidance Mode |
| `3`     | Line Follower Mode      |
| `4`     | Maze Solver Mode        |

---

## ⚡ Communication

* **UART Baud Rate:** 115200
* **ESP32 TX → ATmega32 RX**
* **ESP32 RX ← ATmega32 TX**
* **Protocol:** ASCII commands terminated with `\n`

---


## 👨‍💻 Author

**Eng. Mohamad Gamal (Eng.Gemy)**\
Embedded Systems Engineer\
📅 Created: 2025\
📍 Faculty of Engineering, Cairo University – ECE Dept.

---
