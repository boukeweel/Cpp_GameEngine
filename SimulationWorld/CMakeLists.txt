file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
        Core/src/*.cpp
        GOAP/src/*.cpp
        Person/*.cpp
        Person/Goals/*.cpp
    )

add_executable(SimulationWorld ${GAME_SOURCES})

target_include_directories(SimulationWorld PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
        ${CMAKE_CURRENT_SOURCE_DIR}/GOAP/include
        ${CMAKE_CURRENT_SOURCE_DIR}/Person
        ${CMAKE_CURRENT_SOURCE_DIR}/Person/Goals
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