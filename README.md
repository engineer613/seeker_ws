# Seeker Workspace

Seeker is a WIP project for GPS + IMU based autonomy software for RC Planes. The current plan is to use RealFlight Evolution to test out various modules and autonomy logic before running it on a real RC Plane with a BeagleBone Black on-board acting as a flight controller. 

A ROS2 based approach is planned for the initial simulation-based testing and validation of the autonomy features. On-board the real RC plane, the BeagleBone Black will run an embedded version of the application that does not use ROS2.  

This repo is intended to be a mono-repo for the core C++ libraries as well as the ROS2 wrappers used for the simulation. More documentation with detailed information about the hardware build and electronics is currently in the works.

## Architecture

```
seeker_ws/
├── core/               # Core C++ libraries (no ROS2 dependencies)
│   ├── joystick/       # Joystick interface library
│   └── rf_interface/   # RF communication library
├── ros2/               # ROS2 wrappers (for simulation/testing)
│   ├── joystick_ros/   # ROS2 wrapper for joystick
│   ├── rf_interface_ros/  # ROS2 wrapper for RealFlight interface
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
# Build ROS2 packages from repo root
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

