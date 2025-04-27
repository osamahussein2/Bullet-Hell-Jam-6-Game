file(GLOB_RECURSE SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

include_directories(
    "${CMAKE_SOURCE_DIR}/src/"
    "${CMAKE_SOURCE_DIR}/external/"
    "${CMAKE_SOURCE_DIR}/external/glm/"
    "${CMAKE_SOURCE_DIR}/external/miniaudio/"
)