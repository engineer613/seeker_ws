cmake_minimum_required(VERSION 3.8)
project(rf_interface_ros)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(seeker_msgs REQUIRED)
find_package(rf_interface REQUIRED)

add_executable(rf_interface_node
  src/rf_interface_ros.cpp
)

ament_target_dependencies(rf_interface_node
  rclcpp
  seeker_msgs
)

target_link_libraries(rf_interface_node
  rf_interface::rf_interface
)

install(TARGETS rf_interface_node
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
