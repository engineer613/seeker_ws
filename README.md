# Seeker Workspace

Seeker is a WIP project for GPS + IMU based autonomy software for RC Planes. The current plan is to use RealFlight Evolution as a high-fidelity simulator to test out various modules and autonomy logic before running it on a real RC Plane. A ROS2 based approach is planned for the initial simulation-based testing and validation of the autonomy features. 

The real RC Plane will have a BeagleBone Black (BBB) on-board acting as the flight controller. The BBB will run an embedded version of the application that does not use ROS2.  

This repo is intended to be a mono-repo for the core C++ libraries as well as the ROS2 wrappers used for the simulation. More documentation with detailed information about the hardware build and electronics for V1 build is currently in the works, lagging behind the autonomy software module development.

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

