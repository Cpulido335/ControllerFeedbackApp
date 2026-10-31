cmake_minimum_required(VERSION 3.23)

project(controller-gui LANGUAGES C)


if(NOT WIN32)
    message(FATAL_ERROR "This application supports Windows only.")
endif()



#Try to find SDL3 already installed on the machine
find_package(SDL3 CONFIG QUIET COMPONENTS SDL3-shared)

#If SDL3 isn't installed, automatically download and build it
if(NOT SDL3_FOUND)
    include(FetchContent)

    set(SDL_SHARED ON CACHE BOOL "" FORCE)
    set(SDL_STATIC OFF CACHE BOOL "" FORCE)
    set(SDL_TESTS OFF CACHE BOOL "" FORCE)

    FetchContent_Declare(
        SDL3
        URL https://www.libsdl.org/release/SDL3-3.4.18.zip
    )

    FetchContent_MakeAvailable(SDL3)
endif()




file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
    "${PROJECT_SOURCE_DIR}/src/*.c"
)

add_executable(MyProgram ${SRC_FILES})


target_include_directories(MyProgram PRIVATE
    "${PROJECT_SOURCE_DIR}/include"
)



target_link_libraries(MyProgram PRIVATE
    SDL3::SDL3
    xinput9_1_0
    user32
    gdi32
)


if(MINGW)
    target_link_libraries(MyProgram PRIVATE m)
endif()




add_custom_command(
    TARGET MyProgram POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        "$<TARGET_FILE:SDL3::SDL3-shared>"
        "$<TARGET_FILE_DIR:MyProgram>"
    VERBATIM
)



if(EXISTS "${PROJECT_SOURCE_DIR}/data")
    add_custom_command(
        TARGET MyProgram POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_directory
            "${PROJECT_SOURCE_DIR}/data"
            "$<TARGET_FILE_DIR:MyProgram>/data"
        VERBATIM
    )
endif()