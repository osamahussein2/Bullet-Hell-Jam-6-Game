cmake_minimum_required(VERSION 3.20)
project(BulletHellGame LANGUAGES C CXX)

if (NOT DEFINED BUILD_TARGET)
  set(BUILD_TARGET "desktop"
  CACHE STRING "Choose build target: desktop or web")
endif()

if (NOT BUILD_TARGET STREQUAL "desktop" AND
    NOT BUILD_TARGET STREQUAL "web")
  message(FATAL_ERROR "Invalid BUILD_TARGET: ${BUILD_TARGET}")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

include("${CMAKE_SOURCE_DIR}/${BUILD_TARGET}.cmake")