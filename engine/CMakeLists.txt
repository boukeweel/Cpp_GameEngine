add_library(engine STATIC
    Core/src/Engine.cpp
    Core/src/EngineTime.cpp
    Core/src/Renderer.cpp
)

target_include_directories(engine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Components/include
)

target_link_libraries(engine PUBLIC
    SDL2::SDL2
    SDL2_image::SDL2_image
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
)


if(DEFINED GLM_INCLUDE_DIR)
    target_include_directories(engine PUBLIC ${GLM_INCLUDE_DIR})
endif()
