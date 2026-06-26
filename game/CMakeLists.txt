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


set(GAME_RESOURCE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
set(GAME_RESOURCE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/Resources)
if(EXISTS ${GAME_RESOURCE_SOURCE_DIR})
    add_custom_target(copy_game_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${GAME_RESOURCE_SOURCE_DIR}
            ${GAME_RESOURCE_OUTPUT_DIR}
        COMMENT "Copy game resource files to build directory"
    )
    add_dependencies(game copy_game_resources)
endif()