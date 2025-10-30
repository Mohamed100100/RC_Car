import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'dart:typed_data';
import 'dart:async';

class BluetoothManager {
  BluetoothConnection? _connection;
  bool _isConnected = false;
  Function(String)? onDataReceived;
  Function(bool)? onConnectionChanged;

  bool get isConnected => _isConnected;
  BluetoothConnection? get connection => _connection;

  // Get Bluetooth state
  Future<BluetoothState> getBluetoothState() async {
    try {
      return await FlutterBluetoothSerial.instance.state;
    } catch (e) {
      print('Error getting Bluetooth state: $e');
      return BluetoothState.UNKNOWN;
    }
  }

  // Request to enable Bluetooth
  Future<bool?> requestEnable() async {
    try {
      return await FlutterBluetoothSerial.instance.requestEnable();
    } catch (e) {
      print('Error requesting Bluetooth enable: $e');
      return false;
    }
  }

  // Get paired devices
  Future<List<BluetoothDevice>> getPairedDevices() async {
    try {
      print('Getting paired devices...');
      List<BluetoothDevice> devices =
      await FlutterBluetoothSerial.instance.getBondedDevices();
      print('Found ${devices.length} paired devices');
      for (var device in devices) {
        print('Device: ${device.name} - ${device.address}');
      }
      return devices;
    } catch (e) {
      print('Error getting paired devices: $e');
      return [];
    }
  }

  // Connect to device
  Future<Map<String, dynamic>> connect(String address) async {
    try {
      print('Attempting to connect to: $address');

      // Disconnect if already connected
      if (_isConnected) {
        print('Disconnecting existing connection...');
        await disconnect();
        await Future.delayed(const Duration(milliseconds: 500));
      }

      print('Creating connection...');
      _connection = await BluetoothConnection.toAddress(address);
      print('Connection created successfully');

      _isConnected = true;

      // Listen to incoming data
      _connection!.input!.listen(
            (Uint8List data) {
          String message = String.fromCharCodes(data);
          print('Received: $message');
          if (onDataReceived != null) {
            onDataReceived!(message);
          }
        },
        onDone: () {
          print('Connection closed by remote');
          _isConnected = false;
          if (onConnectionChanged != null) {
            onConnectionChanged!(false);
          }
        },
        onError: (error) {
          print('Connection error: $error');
          _isConnected = false;
          if (onConnectionChanged != null) {
            onConnectionChanged!(false);
          }
        },
      );

      if (onConnectionChanged != null) {
        onConnectionChanged!(true);
      }

      print('Connection established successfully');
      return {'success': true, 'message': 'Connected successfully'};

    } catch (e) {
      print('Connection failed: $e');
      _isConnected = false;

      String errorMessage = 'Connection failed';
      if (e.toString().contains('read failed')) {
        errorMessage = 'Device not responding.\n\nMake sure:\n• ESP32 is powered on\n• LED is blinking\n• Device is in range';
      } else if (e.toString().contains('socket')) {
        errorMessage = 'Connection timeout.\n\nTroubleshooting:\n• Restart ESP32\n• Unpair and pair again\n• Move closer to device';
      }

      return {'success': false, 'message': errorMessage};
    }
  }

  // Connect with retry
  Future<Map<String, dynamic>> connectWithRetry(String address, {int maxRetries = 3}) async {
    for (int attempt = 1; attempt <= maxRetries; attempt++) {
      print('Connection attempt $attempt of $maxRetries...');

      Map<String, dynamic> result = await connect(address);

      if (result['success']) {
        return result;
      }

      if (attempt < maxRetries) {
        print('Waiting 2 seconds before retry...');
        await Future.delayed(const Duration(seconds: 2));
      }
    }

    return {
      'success': false,
      'message': 'Connection failed after $maxRetries attempts.\n\n'
          'Troubleshooting:\n'
          '• Make sure ESP32 is powered on\n'
          '• Check if LED is blinking\n'
          '• Try unpairing and pairing again\n'
          '• Restart ESP32 and try again'
    };
  }

  // Send command
  void sendCommand(String command) {
    if (_isConnected && _connection != null) {
      try {
        print('Sending command: $command');
        _connection!.output.add(Uint8List.fromList('$command\n'.codeUnits));
      } catch (e) {
        print('Error sending command: $e');
      }
    } else {
      print('Cannot send command - not connected');
    }
  }

  // Disconnect
  Future<void> disconnect() async {
    try {
      print('Disconnecting...');
      if (_connection != null) {
        await _connection!.close();
        _connection = null;
      }
      _isConnected = false;
      if (onConnectionChanged != null) {
        onConnectionChanged!(false);
      }
      print('Disconnected successfully');
    } catch (e) {
      print('Error disconnecting: $e');
    }
  }
}