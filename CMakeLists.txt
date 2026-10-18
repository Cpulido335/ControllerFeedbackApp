cmake_minimum_required(VERSION 3.23)

# Project definition
project(controller-gui C)


# Include directories (all headers live under include/)
include_directories(${PROJECT_SOURCE_DIR}/include)

# Recursively collect all .c source files under src/
file(GLOB_RECURSE SRC_FILES
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

# Create the executable
add_executable(MyProgram ${SRC_FILES})


target_link_libraries(MyProgram PRIVATE xinput9_1_0)