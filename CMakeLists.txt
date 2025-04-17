cmake_minimum_required(VERSION 3.20)
project(BulletHellGame LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/CMake/Modules/")

find_package(glfw3 REQUIRED)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/"
    "${CMAKE_SOURCE_DIR}/external/"
    "${CMAKE_SOURCE_DIR}/external/glm/"
    "${CMAKE_SOURCE_DIR}/external/miniaudio/"
)

add_library(glad "${CMAKE_SOURCE_DIR}/external/glad/include/glad/glad.h" "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c")
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)

file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad PRIVATE ${CMAKE_DL_LIBS})
