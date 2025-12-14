cmake_minimum_required(VERSION 3.8)
project(rf_interface)

# Set C++ standard
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find required packages
find_package(Threads REQUIRED)

# Include directories
include_directories(src)

# Create core library (no ROS2 dependencies)
add_library(${PROJECT_NAME} STATIC
    src/RFInterface.cpp
    src/RFInterface.hpp
    src/socketpool.hpp
    src/joystick.hpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)

# Link pthread for threading support
target_link_libraries(${PROJECT_NAME} PUBLIC Threads::Threads)

# Create standalone test executable (no ROS2)
add_executable(rf_test src/main.cpp)
target_link_libraries(rf_test ${PROJECT_NAME} Threads::Threads)

# Installation rules
install(TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(TARGETS rf_test
  DESTINATION bin
)

install(DIRECTORY src/
  DESTINATION include
  FILES_MATCHING PATTERN "*.hpp"
)

# Export targets for downstream packages
install(EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION share/${PROJECT_NAME}/cmake
)

export(TARGETS ${PROJECT_NAME}
  FILE ${PROJECT_NAME}Config.cmake
  NAMESPACE ${PROJECT_NAME}::
)
