/*
 * RC Car ESP32 Bluetooth Controller
 * 
 * Features:
 * - Bluetooth Serial communication
 * - UART output (UART1)
 * - 4 Operating Modes
 * - Command parsing and validation
 * - LED status indicators
 * 
 * Hardware Connections:
 * - UART1: GPIO 17 (TX)
 * - LED: GPIO 2 (Built-in)
 * 
 * Author: Eng.gemy
 * Date: 2024
 */

#include "BluetoothSerial.h"

// ==================== Configuration ====================
// Bluetooth Configuration
#define BT_DEVICE_NAME "RC_Car_ESP32"
BluetoothSerial SerialBT;

// UART1 Configuration (Modes)
#define RXD1 16
#define TXD1 17
#define UART1_BAUD 115200

// LED Configuration
#define LED_PIN 2
#define LED_BLINK_INTERVAL 1000  // milliseconds

// Command Configuration
#define MAX_COMMAND_LENGTH 50
#define COMMAND_TIMEOUT 5000     // milliseconds

// ==================== Global Variables ====================
String receivedData = "";
String currentMode = "IDLE";
unsigned long lastHeartbeat = 0;
bool isConnected = false;

// ==================== Setup Function ====================

void setup() {
 
  // Initialize LED
  initializeLed();
  
  // Initialize Bluetooth
  initializeBluetooth();
  
  // Initialize UARTs
  initializeUARTs();
  
}

// ==================== Main Loop ====================

void loop() {
  // Check Bluetooth connection status
  checkBluetoothConnection();
  
  // Handle LED status
  updateLEDStatus();
  
  // Process Bluetooth data
  if (SerialBT.available()) {
    processBluetoothData();
  }
  
}

// ==================== Initialization Functions ====================

void initializeBluetooth() {
  
  // Start Bluetooth with device name
  if (!SerialBT.begin(BT_DEVICE_NAME)) {
    while(1) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      delay(100);
    }
  }
  // Register Bluetooth callback
  SerialBT.register_callback(bluetoothCallback);
}

void initializeLed(){
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void initializeUARTs() {
  
  // Initialize UART1
  Serial1.begin(UART1_BAUD, SERIAL_8N1, RXD1, TXD1);
  
}



// ==================== Bluetooth Functions ====================

void bluetoothCallback(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  if (event == ESP_SPP_SRV_OPEN_EVT) {
    isConnected = true;
    
    // Send welcome message
    SerialBT.println("Connected to RC_Car_ESP32");
    SerialBT.print("Current Mode: " + currentMode);
    
  } else if (event == ESP_SPP_CLOSE_EVT) {
    isConnected = false;
    currentMode = "IDLE";
    SerialBT.println("STATUS: Stopped");
    Serial1.print("E"); // send stop
  }
}

void checkBluetoothConnection() {
  bool clientConnected = SerialBT.hasClient();
  
  if (clientConnected && !isConnected) {
    isConnected = true;
  } else if (!clientConnected && isConnected) {
    isConnected = false;
    currentMode = "IDLE";
  }
}

void processBluetoothData() {
  while (SerialBT.available()) {
    char incomingChar = SerialBT.read();
    
    // Check for command terminators
    if (incomingChar == '\n' || incomingChar == '\r') {
      if (receivedData.length() > 0) {
        processCommand(receivedData);
        receivedData = "";
      }
    } 
    // Check for buffer overflow
    else if (receivedData.length() >= MAX_COMMAND_LENGTH) {
      receivedData = "";
    }
    // Add character to buffer
    else {
      receivedData += incomingChar;
    }
  }
}

// ==================== Command Processing ====================

void processCommand(String command) {
  command.trim();
  command.toUpperCase();
  
  // Validate command
  if (command.length() == 0) {
    return;
  }
  
  
  // Process specific commands
  if (command == "F") {
    SerialBT.print("STATUS: Moving FORWARD");
    Serial1.print("F");
  } 
  else if (command == "B") {
    SerialBT.print("STATUS: Moving BACKWARD");
    Serial1.print("B");
  } 
  else if (command == "L") {
    SerialBT.print("STATUS: Moving LEFT");
    Serial1.print("L");
  } 
  else if (command == "R") {
    SerialBT.print("STATUS: Moving RIGHT");
    Serial1.print("R");
  } 
  else if (command == "S") {
    SerialBT.print("STATUS: Stopped");
    Serial1.print("S");
  }
  else if (command == "IDLE"||
          command == "MODE1"||
          command == "MODE2"||
          command == "MODE3"||
          command == "MODE4") 
          {
            if(currentMode != command){
              currentMode = command;
              SerialBT.print(getPrintedMessageForEachMode(command));
              Serial1.write(command[command.length()-1]);
            }else{
              // do nothing (repeated clicks)
            }
          
          }
  else {
      SerialBT.print("ERROR: Unknown command \'"+command +"\'");
  }
}


// ==================== LED Functions ====================

void updateLEDStatus() {
  if (isConnected) {
    // Solid LED when connected
    digitalWrite(LED_PIN, HIGH);
  } else {
    // Blinking LED when disconnected (heartbeat)
    if (millis() - lastHeartbeat > LED_BLINK_INTERVAL) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      lastHeartbeat = millis();
    }
  }
}

// ==================== Utilities ====================

String getPrintedMessageForEachMode(String mode){
  if(mode == "IDLE") return "Idle Mode Active"; 
  if(mode == "MODE1") return "Manual Control - Touch to Drive"; 
  if(mode == "MODE2") return "Obstacle Avoidance - Auto Navigation"; 
  if(mode == "MODE3") return "Line Follower - Tracking Path"; 
  if(mode == "MODE4") return "Maze Solver - Finding Path"; 
}
