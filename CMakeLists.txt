CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

project(serial)
message(${CMAKE_PROJECT_NAME})

set(CMAKE_VERBOSE_MAKEFILE true)
set(CMAKE_BUILD_TYPE Debug)
# ADD_COMPILE_OPTIONS(-g -Wall)
# SET(CMAKE_C_FLAGS_RELEASE "-DCONFIG_RELEASE -O3")

# gcc -I./path
include_directories(INC
    inc
)

file(GLOB SRC_FILES
    src/event.cpp
    src/queue.cpp
    src/serial.cpp
)

add_library(SRC
    ${SRC_FILES}
)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME}
    pthread SRC
)