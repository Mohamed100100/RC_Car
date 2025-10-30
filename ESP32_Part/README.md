
# 🚗 RC Car ESP32 Bluetooth Controller

## 📘 Overview

This project implements a **Bluetooth-based controller** for an RC car using an **ESP32**.
The ESP32 communicates with an **ATmega32** (or any microcontroller) through **UART**, sending commands that control the car’s behavior and operating modes.

The system supports **manual driving**, **autonomous obstacle avoidance**, **line following**, and **maze-solving** modes.
It also features **LED status indication**, **Bluetooth command parsing**, and **real-time UART transmission**.

---

## ⚙️ Features

✅ Bluetooth communication with Android or PC (via serial terminal or custom app)
✅ UART interface to communicate with the ATmega32
✅ 4 Operating Modes:

* **Mode 1:** Manual Control (Forward, Backward, Left, Right, Stop)
* **Mode 2:** Obstacle Avoidance
* **Mode 3:** Line Follower
* **Mode 4:** Maze Solver (future extension)
  ✅ LED indicator for connection and activity status
  ✅ Error handling and command validation
  ✅ Modular and extensible design

---

## 🧩 Hardware Connections

| Component                      | ESP32 Pin | Description                      |
| ------------------------------ | --------- | -------------------------------- |
| **Bluetooth (Built-in)**       | -         | Used for wireless communication  |
| **UART TX (to ATmega32 RX)**   | GPIO 17   | Transmit data to car controller  |
| **UART RX (from ATmega32 TX)** | GPIO 16   | Receive data from car controller |
| **LED (Built-in)**             | GPIO 2    | Status indication (onboard LED)  |

### 🔋 Power Notes

* The ESP32 can be powered via USB (5V).
* Ensure a **common ground (GND)** between ESP32 and ATmega32.
* The UART communication logic levels must be **3.3V compatible** (ESP32 is **not 5V-tolerant**).

---

## 🧠 Software Architecture

### 1. **Bluetooth Layer**

Handles Bluetooth initialization, connection status, and message reception using the **BluetoothSerial** library.

### 2. **Command Parser**

Receives strings from Bluetooth, validates them, and converts them into UART commands sent to the ATmega32.

### 3. **UART Layer**

Sends single-character commands over UART to the ATmega32, which interprets them as:

| Command | Function        |
| ------- | --------------- |
| `F`     | Move Forward    |
| `B`     | Move Backward   |
| `L`     | Turn Left       |
| `R`     | Turn Right      |
| `S`     | Stop            |
| `1`     | Enable Mode 1   |
| `2`     | Enable Mode 2   |
| `3`     | Enable Mode 3   |
| `4`     | Enable Mode 4   |
| `E`     | Enter Idle mode |

### 4. **LED Status**

* **Blinking** → Not connected via Bluetooth
* **Solid ON** → Connected successfully

---

## 🧰 Dependencies

This project uses the **Arduino framework** with the following built-in ESP32 libraries:

* `<BluetoothSerial.h>`
* `<HardwareSerial.h>`
* `<Arduino.h>`

No additional installations are required beyond the **ESP32 Arduino core**.

---

## 🪜 Setup & Installation

1. **Install ESP32 Support**

   * In Arduino IDE:
     `File → Preferences → Additional Boards Manager URLs:`

     ```
     https://dl.espressif.com/dl/package_esp32_index.json
     ```
   * Then go to:
     `Tools → Board → Boards Manager` → search for **ESP32** and install it.

2. **Select Your Board**

   * Choose your board:
     `Tools → Board → ESP32 Dev Module`
   * Set baud rate: **115200**

3. **Upload the Code**

   * Connect ESP32 via USB.
   * Upload the code.
   * Open the Serial Monitor (optional for debug).

4. **Pair Bluetooth**

   * Search for device **"RC_Car_ESP32"** on your smartphone or PC.
   * Pair and connect using a Bluetooth terminal app.
   * Send commands like `MODE1`, `F`, `L`, `S`, etc.

---

## 📲 Example Commands

| Command | Description                   |
| ------- | ----------------------------- |
| `MODE1` | Enter Manual Control mode     |
| `MODE2` | Enter Obstacle Avoidance mode |
| `MODE3` | Enter Line Follower mode      |
| `MODE4` | Enter Maze Solver mode        |
| `IDLE`  | Stop and go to idle           |
| `F`     | Move forward                  |
| `B`     | Move backward                 |
| `L`     | Turn left                     |
| `R`     | Turn right                    |
| `S`     | Stop movement                 |

---

## 💡 LED Indications

| LED Behavior   | Meaning                          |
| -------------- | -------------------------------- |
| **Blinking**   | Waiting for Bluetooth connection |
| **Solid ON**   | Connected via Bluetooth          |
---


## 👨‍💻 Author

**Eng. Mohamad Gamal (Eng.Gemy)**\
Embedded Systems Engineer\
Cairo University — Faculty of Engineering
2025
---
