include(common.cmake)

add_library(glad STATIC "${CMAKE_SOURCE_DIR}/external/glad_web/include/glad/glad.h" "${CMAKE_SOURCE_DIR}/external/glad_web/src/glad.c")
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/external/glad_web/include)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE glad)

#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -sMAX_WEBGL_VERSION=2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s USE_GLFW=3 -s ASSERTIONS=1 -s WASM=1 -s ASYNCIFY -sMAX_WEBGL_VERSION=2 --preload-file assets --shell-file shell.html")

#set(CMAKE_EXECUTABLE_SUFFIX ".html")

set_target_properties(${PROJECT_NAME} PROPERTIES
    OUTPUT_NAME "index"
    SUFFIX ".html"
)