add_executable(game
    src/main.cpp
    src/Game.cpp
)

target_include_directories(game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(game PRIVATE
    engine
)
