# Seeker Workspace

A ROS2 workspace for the Seeker project with a clean separation between core C++ libraries and ROS2 wrappers.

## Architecture

```
seeker_ws/
├── core/               # Core C++ libraries (no ROS2 dependencies)
│   ├── joystick/       # Joystick interface library
│   └── rf_interface/   # RF communication library
├── ros2/               # ROS2 wrappers (for simulation/testing)
│   ├── joystick_ros/   # ROS2 wrapper for joystick
│   ├── rf_interface_ros/  # ROS2 wrapper for RF interface
│   └── seeker_msgs/    # ROS2 message definitions
└── src/                # Symlinks to ros2/ for colcon build
```

## Installation

### Prerequisites
- ROS2 (Humble/Iron/Jazzy)
- CMake 3.8+
- Build tools: `sudo apt install build-essential`

### Building for ROS2 (Simulation/Testing)

```bash
cd ~/seeker_ws

# First, build core libraries
cd core/joystick
mkdir -p build && cd build
cmake .. && make && sudo make install
cd ../../..

cd core/rf_interface
mkdir -p build && cd build
cmake .. && make && sudo make install
cd ../../..

# Then build ROS2 packages
colcon build

# Source the workspace
source install/setup.bash
```

### Building for BBB

```bash
# Only build core libraries - no ROS2 dependencies
cd core
mkdir build && cd build
cmake ..
make -j
```

## Packages

### Core Libraries
- **joystick**: C++ joystick interface using Linux evdev
- **rf_interface**: C++ RealFlight communication library

### ROS2 Packages
- **seeker_msgs**: ROS2 message definitions
- **joystick_ros**: ROS2 wrapper node for joystick
- **rf_interface_ros**: ROS2 wrapper node for RealFlight interface

## Usage

### ROS2 Testing/Simulation

### Embedded Usage

