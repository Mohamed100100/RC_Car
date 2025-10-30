
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
## 🔌 Wiring Diagram
```
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




```
---

## 👨‍💻 Author

**Eng. Mohamad Gamal (Eng.Gemy)**\
Embedded Systems Engineer\
📅 Created: 2025\
📍 Faculty of Engineering, Cairo University – ECE Dept.

---
