#include "joystick.hpp"

namespace RF {

Joystick::Joystick(const char* device)
    : m_dev_path(device)
{
    if (openDevice()) {
        std::cout << "[SUCCESS] Joystick: Successfully opened device: " << m_dev_path << std::endl;
        if(start_reading()) {
            std::cout << "[SUCCESS] Joystick: Started Reading from " << m_dev_path << std::endl;
        }
    }
}

Joystick::~Joystick() {
    if (m_joystick_read_thread.joinable()) {
        m_joystick_read_thread.join();
    }
    closeDevice();
}

bool Joystick::start_reading() {
    if(m_fd > 0) {
        m_reading.store(true);
        m_joystick_read_thread = std::thread(&Joystick::pollForInputs, this);
        return true;
    }
    return false;
}

void Joystick::stop_reading() {
    if(m_reading) m_reading.store(false);
}

bool Joystick::is_reading() {
    return m_reading.load();
}

RF::RFCmd Joystick::getJoystickVals() {
    std::lock_guard<std::mutex> lock(m_state_mutex);
    RFCmd new_state = m_state;
    return new_state;
}

bool Joystick::openDevice() {
    m_fd = open(m_dev_path, O_RDONLY | O_NONBLOCK);
    if(m_fd < 0) {
        std::cerr << "[ERROR] Joystick: Failed to open " << m_dev_path << ": "
                  << strerror(errno) << "\n";
        return false;
    }
    return true;
}

bool Joystick::closeDevice() {
    if(m_fd >= 0) close(m_fd);
    m_fd = -1;
    return true;
}

bool Joystick::readJoystickDisable(float val) {
    return (val == 0);
}

float Joystick::normalize(float val) {
    if (val < AXIS_MIN) val = AXIS_MIN;
    if (val > AXIS_MAX) val = AXIS_MAX;
    return (val - AXIS_MIN) / (AXIS_MAX - AXIS_MIN);
}

void Joystick::readAbs(int code, int value) {
    std::lock_guard<std::mutex> lock(m_state_mutex);
    switch (code) {
        case 0:
            m_state.aileron = normalize(value);
            break;
        case 1:
            m_state.elevator = normalize(value);
            break;
        case 2:
            m_state.throttle = normalize(value);
            break;
        case 3:
            m_state.rudder = normalize(value);
            break;
        case 5:
            // TODO: pass this disable to RFInterface
            readJoystickDisable(value);
            break;
    }
}

void Joystick::pollForInputs() {
    std::cout << "[INFO] Joystick polling thread started" << std::endl;
    
    while(m_reading.load()) {
        if (m_fd < 0) {
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }

        struct input_event ev;
        ssize_t n = read(m_fd, &ev, sizeof(ev));
        
        if (n < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                // No data ready, wait a bit
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
                continue;
            } else {
                std::cerr << "[ERROR] Joystick read failed: " << strerror(errno) << std::endl;
                break;
            }
        }
        
        if (n == sizeof(ev)) {
            if (ev.type == EV_ABS) {
                readAbs(ev.code, ev.value);
            }
        }
    }
    
    std::cout << "[INFO] Joystick polling thread exiting" << std::endl;
}

} // namespace RF
