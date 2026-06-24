cmake_minimum_required(VERSION 3.10)
project(GameEngine LANGUAGES CXX)

# Export compile commands for editor IntelliSense / clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)


include(FetchContent)

# Prefer system-installed glm; otherwise fetch the header-only library from GitHub
find_package(glm QUIET)
if(NOT glm_FOUND)
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 0.9.9.8
    )
    FetchContent_GetProperties(glm)
    if(NOT glm_POPULATED)
        # Allow using FetchContent_Populate without the newer FetchContent_MakeAvailable
        # to avoid invoking glm's CMake which can trigger policy/version issues.
        cmake_policy(SET CMP0169 OLD)
        FetchContent_Populate(glm)
    endif()

    # GLM is header-only; expose its source dir (it contains the `glm/` folder)
    set(GLM_INCLUDE_DIR ${glm_SOURCE_DIR} CACHE PATH "GLM source directory for headers")
endif()

add_subdirectory(engine)
add_subdirectory(game)
