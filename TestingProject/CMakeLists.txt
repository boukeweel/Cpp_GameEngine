file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS
    Core/src/*.cpp
    Components/src/*.cpp
    Interfaces/src/*.cpp
    Commands/src/*.cpp
)

add_executable(TestingProject ${GAME_SOURCES})

target_include_directories(TestingProject PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Components/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Interfaces/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Commands/include
)

target_link_libraries(TestingProject PRIVATE
    engine
)

set(GAME_RESOURCE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources)
set(GAME_RESOURCE_OUTPUT_DIR ${CMAKE_BINARY_DIR}/TestingProject/Resources)
if(EXISTS ${GAME_RESOURCE_SOURCE_DIR})
    add_custom_target(copy_game_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${GAME_RESOURCE_SOURCE_DIR}
            ${GAME_RESOURCE_OUTPUT_DIR}
        COMMENT "Copy game resource files to build directory"
    )
    add_dependencies(TestingProject copy_game_resources)
endif()