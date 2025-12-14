cmake_minimum_required(VERSION 3.8)
project(joystick_ros)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(seeker_msgs REQUIRED)
find_package(joystick REQUIRED)

# Create ROS2 node executable
add_executable(joystick_node
  src/joystick_ros.cpp
)

ament_target_dependencies(joystick_node
  rclcpp
  seeker_msgs
)

# Link against core joystick library
target_link_libraries(joystick_node
  joystick::joystick
)

# Install node
install(TARGETS joystick_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
