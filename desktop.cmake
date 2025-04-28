include(common.cmake)

if(WIN32)
    find_package(GLFW3 REQUIRED)
endif()
if(UNIX AND NOT APPLE)
    find_package(glfw3 REQUIRED)
endif()


add_library(glad STATIC "${CMAKE_SOURCE_DIR}/external/glad/include/glad/glad.h" "${CMAKE_SOURCE_DIR}/external/glad/src/glad.c")
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad/include)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad ${CMAKE_DL_LIBS})