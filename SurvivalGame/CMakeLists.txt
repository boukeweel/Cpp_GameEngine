file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    Core/src/*.cpp
    Player/src/*.cpp
    Enemies/src/*.cpp
)

add_executable(SurvivalGame ${GAME_SOURCES})

target_include_directories(SurvivalGame PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Player/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Enemies/include
)

target_link_libraries(SurvivalGame PRIVATE
    engine
)

set(GAME_RESOURCE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
set(GAME_RESOURCE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/SurvivalGame/Resources)
if(EXISTS ${GAME_RESOURCE_SOURCE_DIR})
    add_custom_target(copy_Survival_game_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${GAME_RESOURCE_SOURCE_DIR}
            ${GAME_RESOURCE_OUTPUT_DIR}
        COMMENT "Copy game resource files to build directory"
    )
    add_dependencies(SurvivalGame copy_Survival_game_resources)
endif()