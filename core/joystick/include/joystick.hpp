#ifndef JOYSTICK_INTERFACE_HPP_
#define JOYSTICK_INTERFACE_HPP_

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <cerrno>
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>

namespace RF {

// Forward declarations for structs
struct RFCmd {
    double throttle;
    double aileron;
    double elevator; 
    double rudder;
    double flaps;
    double gear;
};


class Joystick {
public:
    explicit Joystick(const char* device = "/dev/input/event0");
    ~Joystick();

    bool start_reading();
    void stop_reading();
    bool is_reading();
    
    // Called from other threads
    RF::RFCmd getJoystickVals();

private:
    const char* CLASS = "JOYSTICK";
    const char* m_dev_path; 
    int m_fd = -1;

    std::atomic_bool m_reading{false};

    RFCmd m_state;
    std::thread m_joystick_read_thread;
    std::mutex m_state_mutex;

    static constexpr float AXIS_MIN = 0.0f;
    static constexpr float AXIS_MAX = 2040.0f;
    static constexpr float AXIS_CENTER = (AXIS_MIN + AXIS_MAX) / 2.0f;
    static constexpr float AXIS_RANGE = (AXIS_MAX - AXIS_CENTER);

    bool openDevice();
    bool closeDevice();
    
    // Map [0, 2047] to a toggle 
    bool readJoystickDisable(float val);
    
    // Map [0, 2047] to [0, 1]
    float normalize(float val);
    
    // Code# to control mapping:
    //  Throttle: Code 2
    //  Alieron/Roll: Code 0
    //  Rudder/Yaw: Code 3
    //  Elevator/Pitch:Code 1
    //  Code 5: 3-way switch on top left
    void readAbs(int code, int value);
    
    void pollForInputs();
};

}
#endif // JOYSTICK_INTERFACE_HPP_