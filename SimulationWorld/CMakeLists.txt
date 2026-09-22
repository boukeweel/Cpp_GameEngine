file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
        Core/*.cpp
        Core/Scenes/*.cpp
        GOAP/*.cpp
        Person/*.cpp
        Person/Goals/*.cpp
        Person/Actions/*.cpp
        Person/Components/*.cpp
        Items/Food/*.cpp
        Objects/*.cpp
    )

add_executable(SimulationWorld ${GAME_SOURCES})

target_include_directories(SimulationWorld PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Core
        ${CMAKE_CURRENT_SOURCE_DIR}/GOAP
        ${CMAKE_CURRENT_SOURCE_DIR}/Person
        ${CMAKE_CURRENT_SOURCE_DIR}/Person/Goals
        ${CMAKE_CURRENT_SOURCE_DIR}/Person/Actions
        ${CMAKE_CURRENT_SOURCE_DIR}/Person/Components
        ${CMAKE_CURRENT_SOURCE_DIR}/Items/Food
        ${CMAKE_CURRENT_SOURCE_DIR}/Objects

    )

target_link_libraries(SimulationWorld PRIVATE
    engine
)

set(GAME_RESOURCE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
set(GAME_RESOURCE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/SimulationWorld/Resources)
if(EXISTS ${GAME_RESOURCE_SOURCE_DIR})
    add_custom_target(copy_Simulation_World_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${GAME_RESOURCE_SOURCE_DIR}
            ${GAME_RESOURCE_OUTPUT_DIR}
        COMMENT "Copy game resource files to build directory"
    )
    add_dependencies(SimulationWorld copy_Simulation_World_resources)
endif()