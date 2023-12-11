cmake_minimum_required(VERSION 3.5)
project(socket_server)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_BUILD_TYPE "Release")

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

file(GLOB_RECURSE SRC_DIR_LIST CONFIGURE_DEPENDS "server/*.cc" "server/*.cpp" "server/*.c")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/server)

add_executable(${PROJECT_NAME} ${SRC_DIR_LIST})
