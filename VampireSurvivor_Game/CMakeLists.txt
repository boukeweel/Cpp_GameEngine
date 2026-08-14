file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    Core/src/*.cpp
)

add_executable(VampireSurvivor_Game ${GAME_SOURCES})

target_include_directories(VampireSurvivor_Game PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
)

target_link_libraries(VampireSurvivor_Game PRIVATE
    engine
)

set(GAME_RESOURCE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
set(GAME_RESOURCE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/VampireSurvivor_Game/Resources)
if(EXISTS ${GAME_RESOURCE_SOURCE_DIR})
    add_custom_target(copy_game_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${GAME_RESOURCE_SOURCE_DIR}
            ${GAME_RESOURCE_OUTPUT_DIR}
        COMMENT "Copy game resource files to build directory"
    )
    add_dependencies(VampireSurvivor_Game copy_game_resources)
endif()