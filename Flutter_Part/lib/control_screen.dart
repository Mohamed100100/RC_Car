import 'package:flutter/material.dart';
import 'package:flutter_bluetooth_serial/flutter_bluetooth_serial.dart';
import 'package:permission_handler/permission_handler.dart';
import 'bluetooth_manager.dart';

class ControlScreen extends StatefulWidget {
  const ControlScreen({Key? key}) : super(key: key);

  @override
  State<ControlScreen> createState() => _ControlScreenState();
}

class _ControlScreenState extends State<ControlScreen> {
  final BluetoothManager _btManager = BluetoothManager();
  String _selectedMode = 'IDLE';
  String _statusMessage = 'Disconnected';
  bool _isConnecting = false;

  @override
  void initState() {
    super.initState();
    _initBluetooth();
    _btManager.onConnectionChanged = (isConnected) {
      if (mounted) {
        setState(() {
          _statusMessage = isConnected ? 'Connected' : 'Disconnected';
          if (!isConnected) {
            _selectedMode = 'IDLE';
          }
        });
      }
    };
    _btManager.onDataReceived = (data) {
      if (mounted) {
        setState(() {
          _statusMessage = data;
        });
      }
    };
  }

  Future<void> _initBluetooth() async {
    print('Initializing Bluetooth...');
    await _requestPermissions();

    BluetoothState state = await _btManager.getBluetoothState();
    print('Bluetooth state: $state');

    if (state == BluetoothState.STATE_OFF) {
      print('Bluetooth is OFF, requesting enable...');
      bool? enabled = await _btManager.requestEnable();
      if (enabled == true) {
        print('Bluetooth enabled by user');
      }
    }
  }

  Future<void> _requestPermissions() async {
    print('Requesting permissions...');
    await [
      Permission.bluetoothScan,
      Permission.bluetoothConnect,
      //Permission.location,
    ].request();
  }

  Future<void> _showBluetoothDialog() async {
    print('Opening Bluetooth dialog...');

    setState(() => _isConnecting = true);
    List<BluetoothDevice> devices = await _btManager.getPairedDevices();
    setState(() => _isConnecting = false);

    if (!mounted) return;

    if (devices.isEmpty) {
      _showErrorDialog(
        'No Devices Found',
        'Please pair your ESP32:\n\n'
            '1. Settings → Bluetooth\n'
            '2. Look for "RC_Car_ESP32"\n'
            '3. Tap to pair\n'
            '4. Return to app',
      );
      return;
    }

    showModalBottomSheet(
      context: context,
      backgroundColor: const Color(0xFF1a1f3a),
      isScrollControlled: true,
      shape: const RoundedRectangleBorder(
        borderRadius: BorderRadius.vertical(top: Radius.circular(20)),
      ),
      builder: (context) {
        return SafeArea(
          child: Container(
            padding: const EdgeInsets.all(20),
            constraints: BoxConstraints(
              maxHeight: MediaQuery.of(context).size.height * 0.6,
            ),
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                Row(
                  mainAxisAlignment: MainAxisAlignment.spaceBetween,
                  children: [
                    Row(
                      children: [
                        Icon(Icons.bluetooth, color: Colors.blue.shade300, size: 28),
                        const SizedBox(width: 10),
                        const Text(
                          'Select Device',
                          style: TextStyle(
                            fontSize: 20,
                            fontWeight: FontWeight.bold,
                            color: Colors.white,
                          ),
                        ),
                      ],
                    ),
                    IconButton(
                      icon: const Icon(Icons.close, color: Colors.grey),
                      onPressed: () => Navigator.pop(context),
                    ),
                  ],
                ),
                const SizedBox(height: 20),
                Flexible(
                  child: ListView.separated(
                    shrinkWrap: true,
                    itemCount: devices.length,
                    separatorBuilder: (context, index) => const SizedBox(height: 10),
                    itemBuilder: (context, index) {
                      BluetoothDevice device = devices[index];
                      return Card(
                        color: const Color(0xFF0a0e27),
                        child: ListTile(
                          leading: const Icon(Icons.devices, color: Colors.cyan, size: 32),
                          title: Text(
                            device.name ?? 'Unknown Device',
                            style: const TextStyle(
                              color: Colors.white,
                              fontWeight: FontWeight.bold,
                              fontSize: 16,
                            ),
                          ),
                          subtitle: Text(
                            device.address,
                            style: TextStyle(color: Colors.grey.shade500, fontSize: 12),
                          ),
                          trailing: Container(
                            padding: const EdgeInsets.symmetric(horizontal: 12, vertical: 6),
                            decoration: BoxDecoration(
                              color: Colors.blue.withOpacity(0.2),
                              borderRadius: BorderRadius.circular(20),
                              border: Border.all(color: Colors.blue),
                            ),
                            child: const Text(
                              'CONNECT',
                              style: TextStyle(
                                color: Colors.blue,
                                fontWeight: FontWeight.bold,
                                fontSize: 12,
                              ),
                            ),
                          ),
                          onTap: () {
                            Navigator.pop(context);
                            _connectToDevice(device);
                          },
                        ),
                      );
                    },
                  ),
                ),
              ],
            ),
          ),
        );
      },
    );
  }

  Future<void> _connectToDevice(BluetoothDevice device) async {
    print('Connecting to: ${device.name} (${device.address})');

    // Show loading
    showDialog(
      context: context,
      barrierDismissible: false,
      builder: (dialogContext) => WillPopScope(
        onWillPop: () async => false,
        child: Center(
          child: Container(
            padding: const EdgeInsets.all(30),
            decoration: BoxDecoration(
              color: const Color(0xFF1a1f3a),
              borderRadius: BorderRadius.circular(20),
            ),
            child: Column(
              mainAxisSize: MainAxisSize.min,
              children: [
                const CircularProgressIndicator(
                  valueColor: AlwaysStoppedAnimation<Color>(Colors.cyan),
                ),
                const SizedBox(height: 20),
                Text(
                  'Connecting to\n${device.name}...',
                  style: const TextStyle(color: Colors.white, fontSize: 16),
                  textAlign: TextAlign.center,
                ),
                const SizedBox(height: 10),
                Text(
                  'Attempting connection...\nThis may take up to 10 seconds',
                  style: TextStyle(color: Colors.grey.shade400, fontSize: 12),
                  textAlign: TextAlign.center,
                ),
              ],
            ),
          ),
        ),
      ),
    );

    // Use retry logic
    Map<String, dynamic> result = await _btManager.connectWithRetry(
      device.address,
      maxRetries: 3,
    );

    // Close loading
    if (mounted) Navigator.pop(context);

    // Show result
    if (mounted) {
      if (result['success']) {
        ScaffoldMessenger.of(context).showSnackBar(
          SnackBar(
            content: Row(
              children: [
                const Icon(Icons.check_circle, color: Colors.white),
                const SizedBox(width: 10),
                Expanded(
                  child: Text('Connected to ${device.name}!'),
                ),
              ],
            ),
            backgroundColor: Colors.green,
            duration: const Duration(seconds: 3),
          ),
        );
        setState(() {
          _statusMessage = 'Connected to ${device.name}';
        });
      } else {
        _showErrorDialog('Connection Failed', result['message']);
      }
    }
  }

  void _showErrorDialog(String title, String message) {
    showDialog(
      context: context,
      builder: (context) => AlertDialog(
        backgroundColor: const Color(0xFF1a1f3a),
        shape: RoundedRectangleBorder(
          borderRadius: BorderRadius.circular(20),
        ),
        title: Row(
          children: [
            const Icon(Icons.error_outline, color: Colors.red, size: 28),
            const SizedBox(width: 10),
            Expanded(
              child: Text(
                title,
                style: const TextStyle(color: Colors.white, fontSize: 18),
              ),
            ),
          ],
        ),
        content: Text(
          message,
          style: TextStyle(color: Colors.grey.shade400, fontSize: 14),
        ),
        actions: [
          TextButton(
            onPressed: () => Navigator.pop(context),
            child: Text(
              'OK',
              style: TextStyle(color: Colors.blue.shade300, fontSize: 16),
            ),
          ),
        ],
      ),
    );
  }

  void _sendCommand(String command) {
    if (_btManager.isConnected) {
      _btManager.sendCommand(command);
    }
  }

  void _setMode(String mode) {
    if (_btManager.isConnected) {
      // Only send command if mode is actually changing
      if (_selectedMode != mode) {
        setState(() => _selectedMode = mode);
        _sendCommand(mode);
      }
    }
  }

  @override
  void dispose() {
    _btManager.disconnect();
    super.dispose();
  }

  @override
    Widget build(BuildContext context) {
      return Scaffold(
        body: Container(
          decoration: const BoxDecoration(
            gradient: LinearGradient(
              begin: Alignment.topLeft,
              end: Alignment.bottomRight,
              colors: [
                Color(0xFF0a0e27),
                Color(0xFF1a1f3a),
              ],
            ),
          ),
          child: SafeArea(
            child: SingleChildScrollView(
              child: ConstrainedBox(
                constraints: BoxConstraints(
                  minHeight: MediaQuery.of(context).size.height -
                      MediaQuery.of(context).padding.top -
                      MediaQuery.of(context).padding.bottom,
                ),
                child: IntrinsicHeight(
                  child: Column(
                    children: [
                      _buildHeader(),
                      const SizedBox(height: 10),
                      _buildBluetoothButton(),
                      const SizedBox(height: 15),
                      _buildModeButtons(),
                      const SizedBox(height: 15),
                      Expanded(child: _buildDirectionControls()),
                      _buildStatusBar(),
                    ],
                  ),
                ),
              ),
            ),
          ),
        ),
      );
    }

  Widget _buildHeader() {
    return Padding(
      padding: const EdgeInsets.all(16),
      child: Row(
        children: [
          // Logo from assets
          Container(
            width: 45,
            height: 45,
            decoration: BoxDecoration(
              shape: BoxShape.circle,
              color: Colors.white,
              boxShadow: [
                BoxShadow(
                  color: Colors.blue.withOpacity(0.3),
                  blurRadius: 8,
                  spreadRadius: 2,
                ),
              ],
            ),
            child: ClipOval(
              child: Image.asset(
                'assets/images/logo.png',
                fit: BoxFit.cover,
                errorBuilder: (context, error, stackTrace) {
                  // Fallback if image not found
                  return Icon(
                    Icons.directions_car_rounded,
                    color: Colors.blue,
                    size: 24,
                  );
                },
              ),
            ),
          ),
          const SizedBox(width: 12),
          const Expanded(
            child: Column(
              crossAxisAlignment: CrossAxisAlignment.start,
              children: [
                Text(
                  'RC CAR',
                  style: TextStyle(
                    fontSize: 20,
                    fontWeight: FontWeight.bold,
                    color: Colors.white,
                  ),
                ),
                Text(
                  'By Eng. Gemy',
                  style: TextStyle(
                    fontSize: 12,
                    color: Colors.cyan,
                    fontWeight: FontWeight.w500,
                  ),
                ),
              ],
            ),
          ),
          Container(
            padding: const EdgeInsets.symmetric(horizontal: 10, vertical: 5),
            decoration: BoxDecoration(
              color: _btManager.isConnected
                  ? Colors.green.withOpacity(0.2)
                  : Colors.red.withOpacity(0.2),
              borderRadius: BorderRadius.circular(20),
              border: Border.all(
                color: _btManager.isConnected ? Colors.green : Colors.red,
                width: 1,
              ),
            ),
            child: Row(
              mainAxisSize: MainAxisSize.min,
              children: [
                Container(
                  width: 6,
                  height: 6,
                  decoration: BoxDecoration(
                    shape: BoxShape.circle,
                    color: _btManager.isConnected ? Colors.green : Colors.red,
                  ),
                ),
                const SizedBox(width: 5),
                Text(
                  _btManager.isConnected ? 'ONLINE' : 'OFFLINE',
                  style: TextStyle(
                    fontSize: 10,
                    fontWeight: FontWeight.bold,
                    color: _btManager.isConnected ? Colors.green : Colors.red,
                  ),
                ),
              ],
            ),
          ),
        ],
      ),
    );
  }

    Widget _buildBluetoothButton() {
      return Padding(
        padding: const EdgeInsets.symmetric(horizontal: 16),
        child: Material(
          color: Colors.transparent,
          child: InkWell(
            onTap: _isConnecting
                ? null
                : () {
              if (_btManager.isConnected) {
                _btManager.disconnect();
                setState(() => _selectedMode = 'IDLE');
              } else {
                _showBluetoothDialog();
              }
            },
            borderRadius: BorderRadius.circular(12),
            child: Container(
              padding: const EdgeInsets.symmetric(vertical: 14),
              decoration: BoxDecoration(
                gradient: LinearGradient(
                  colors: _btManager.isConnected
                      ? [Colors.red.shade600, Colors.red.shade800]
                      : [Colors.blue.shade600, Colors.blue.shade800],
                ),
                borderRadius: BorderRadius.circular(12),
                boxShadow: [
                  BoxShadow(
                    color:
                    (_btManager.isConnected ? Colors.red : Colors.blue)
                        .withOpacity(0.4),
                    blurRadius: 12,
                    offset: const Offset(0, 4),
                  ),
                ],
              ),
              child: Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  if (_isConnecting)
                    const SizedBox(
                      width: 20,
                      height: 20,
                      child: CircularProgressIndicator(
                        strokeWidth: 2,
                        valueColor: AlwaysStoppedAnimation<Color>(Colors.white),
                      ),
                    )
                  else
                    Icon(
                      _btManager.isConnected
                          ? Icons.bluetooth_connected
                          : Icons.bluetooth,
                      color: Colors.white,
                      size: 24,
                    ),
                  const SizedBox(width: 10),
                  Text(
                    _btManager.isConnected
                        ? 'DISCONNECT'
                        : 'CONNECT BLUETOOTH',
                    style: const TextStyle(
                      fontSize: 16,
                      fontWeight: FontWeight.bold,
                      color: Colors.white,
                      letterSpacing: 1,
                    ),
                  ),
                ],
              ),
            ),
          ),
        ),
      );
    }

    Widget _buildModeButtons() {
      return Padding(
        padding: const EdgeInsets.symmetric(horizontal: 16),
        child: Column(
          children: [
            Row(
              children: [
                Expanded(
                  child: _buildModeButton('IDLE', Icons.power_settings_new,
                      Colors.grey, 'IDLE'),
                ),
                const SizedBox(width: 8),
                Expanded(
                  child: _buildModeButton(
                      'MODE1', Icons.touch_app, Colors.blue, 'MODE1'),
                ),
                const SizedBox(width: 8),
                Expanded(
                  child: _buildModeButton(
                      'MODE2', Icons.sensors, Colors.green, 'MODE2'),
                ),
              ],
            ),
            const SizedBox(height: 8),
            Row(
              children: [
                Expanded(
                  child: _buildModeButton(
                      'MODE3', Icons.linear_scale, Colors.orange, 'MODE3'),
                ),
                const SizedBox(width: 8),
                Expanded(
                  child: _buildModeButton(
                      'MODE4', Icons.explore, Colors.purple, 'MODE4'),
                ),
              ],
            ),
          ],
        ),
      );
    }

    Widget _buildModeButton(
        String label, IconData icon, Color color, String mode) {
      bool isSelected = _selectedMode == mode;
      bool isEnabled = _btManager.isConnected || mode == 'IDLE';

      return Opacity(
        opacity: isEnabled ? 1.0 : 0.3,
        child: Material(
          color: Colors.transparent,
          child: InkWell(
            onTap: isEnabled ? () => _setMode(mode) : null,
            borderRadius: BorderRadius.circular(12),
            child: Container(
              padding: const EdgeInsets.symmetric(vertical: 12),
              decoration: BoxDecoration(
                color: isSelected
                    ? color.withOpacity(0.3)
                    : const Color(0xFF1a1f3a),
                borderRadius: BorderRadius.circular(12),
                border: Border.all(
                  color: isSelected ? color : Colors.grey.shade800,
                  width: 2,
                ),
                boxShadow: isSelected
                    ? [
                  BoxShadow(
                    color: color.withOpacity(0.4),
                    blurRadius: 12,
                    offset: const Offset(0, 4),
                  ),
                ]
                    : null,
              ),
              child: Column(
                children: [
                  Icon(
                    icon,
                    color: isSelected ? color : Colors.grey.shade600,
                    size: 28,
                  ),
                  const SizedBox(height: 6),
                  Text(
                    label,
                    style: TextStyle(
                      fontSize: 11,
                      fontWeight: FontWeight.bold,
                      color: isSelected ? color : Colors.grey.shade600,
                    ),
                  ),
                ],
              ),
            ),
          ),
        ),
      );
    }

    Widget _buildDirectionControls() {
      bool isEnabled = _btManager.isConnected && _selectedMode == 'MODE1';

      return Center(
        child: Padding(
          padding: const EdgeInsets.symmetric(vertical: 10),
          child: Column(
            mainAxisAlignment: MainAxisAlignment.center,
            mainAxisSize: MainAxisSize.min,
            children: [
              _buildDirectionButton(
                Icons.arrow_upward_rounded,
                'FORWARD',
                'F',
                isEnabled,
              ),
              const SizedBox(height: 15),
              Row(
                mainAxisAlignment: MainAxisAlignment.center,
                children: [
                  _buildDirectionButton(
                    Icons.arrow_back_rounded,
                    'LEFT',
                    'L',
                    isEnabled,
                  ),
                  const SizedBox(width: 15),
                  _buildStopButton(isEnabled),
                  const SizedBox(width: 15),
                  _buildDirectionButton(
                    Icons.arrow_forward_rounded,
                    'RIGHT',
                    'R',
                    isEnabled,
                  ),
                ],
              ),
              const SizedBox(height: 15),
              _buildDirectionButton(
                Icons.arrow_downward_rounded,
                'BACKWARD',
                'B',
                isEnabled,
              ),
            ],
          ),
        ),
      );
    }

    Widget _buildDirectionButton(
        IconData icon, String label, String command, bool isEnabled) {
      return Opacity(
        opacity: isEnabled ? 1.0 : 0.3,
        child: GestureDetector(
          onTapDown: isEnabled ? (_) => _sendCommand(command) : null,
          onTapUp: isEnabled ? (_) => _sendCommand('S') : null,
          onTapCancel: isEnabled ? () => _sendCommand('S') : null,
          child: Container(
            width: 85,
            height: 85,
            decoration: BoxDecoration(
              gradient: LinearGradient(
                begin: Alignment.topLeft,
                end: Alignment.bottomRight,
                colors: isEnabled
                    ? [Colors.blue.shade600, Colors.blue.shade800]
                    : [Colors.grey.shade800, Colors.grey.shade900],
              ),
              borderRadius: BorderRadius.circular(16),
              boxShadow: isEnabled
                  ? [
                BoxShadow(
                  color: Colors.blue.withOpacity(0.4),
                  blurRadius: 15,
                  offset: const Offset(0, 6),
                ),
              ]
                  : null,
            ),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(
                  icon,
                  size: 40,
                  color: Colors.white,
                ),
                const SizedBox(height: 4),
                Text(
                  label,
                  style: const TextStyle(
                    fontSize: 10,
                    fontWeight: FontWeight.bold,
                    color: Colors.white,
                  ),
                ),
              ],
            ),
          ),
        ),
      );
    }

    Widget _buildStopButton(bool isEnabled) {
      return Opacity(
        opacity: isEnabled ? 1.0 : 0.3,
        child: GestureDetector(
          onTap: isEnabled ? () => _sendCommand('S') : null,
          child: Container(
            width: 85,
            height: 85,
            decoration: BoxDecoration(
              gradient: LinearGradient(
                begin: Alignment.topLeft,
                end: Alignment.bottomRight,
                colors: isEnabled
                    ? [Colors.red.shade600, Colors.red.shade800]
                    : [Colors.grey.shade800, Colors.grey.shade900],
              ),
              borderRadius: BorderRadius.circular(16),
              boxShadow: isEnabled
                  ? [
                BoxShadow(
                  color: Colors.red.withOpacity(0.4),
                  blurRadius: 15,
                  offset: const Offset(0, 6),
                ),
              ]
                  : null,
            ),
            child: Column(
              mainAxisAlignment: MainAxisAlignment.center,
              children: [
                Icon(
                  Icons.stop_rounded,
                  size: 40,
                  color: Colors.white,
                ),
                const SizedBox(height: 4),
                const Text(
                  'STOP',
                  style: TextStyle(
                    fontSize: 10,
                    fontWeight: FontWeight.bold,
                    color: Colors.white,
                  ),
                ),
              ],
            ),
          ),
        ),
      );
    }

    Widget _buildStatusBar() {
      return Container(
        padding: const EdgeInsets.all(16),
        decoration: BoxDecoration(
          color: const Color(0xFF1a1f3a),
          boxShadow: [
            BoxShadow(
              color: Colors.black.withOpacity(0.3),
              blurRadius: 10,
              offset: const Offset(0, -5),
            ),
          ],
        ),
        child: Column(
          mainAxisSize: MainAxisSize.min,
          children: [
            Row(
              children: [
                Icon(
                  Icons.info_outline,
                  color: Colors.cyan.shade300,
                  size: 18,
                ),
                const SizedBox(width: 8),
                const Text(
                  'STATUS',
                  style: TextStyle(
                    fontSize: 11,
                    fontWeight: FontWeight.bold,
                    color: Colors.grey,
                    letterSpacing: 1,
                  ),
                ),
              ],
            ),
            const SizedBox(height: 8),
            Container(
              width: double.infinity,
              padding: const EdgeInsets.all(10),
              decoration: BoxDecoration(
                color: const Color(0xFF0a0e27),
                borderRadius: BorderRadius.circular(8),
                border: Border.all(
                  color: Colors.cyan.withOpacity(0.3),
                  width: 1,
                ),
              ),
              child: Text(
                _statusMessage,
                style: TextStyle(
                  fontSize: 13,
                  color: Colors.cyan.shade300,
                  fontFamily: 'Courier',
                ),
                textAlign: TextAlign.center,
                maxLines: 2,
                overflow: TextOverflow.ellipsis,
              ),
            ),
          ],
        ),
      );
    }
  }