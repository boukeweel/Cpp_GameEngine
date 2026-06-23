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

add_subdirectory(engine)
add_subdirectory(game)
