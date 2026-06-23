#include "Engine.h"
#include <iostream>

Engine::Engine(const std::string& title, int width, int height)
    : title_(title), width_(width), height_(height) {
}

Engine::~Engine() {
    shutdown();
}

bool Engine::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << '\n';
        return false;
    }

    window_ = SDL_CreateWindow(
        title_.c_str(),
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width_,
        height_,
        SDL_WINDOW_SHOWN
    );

    if (!window_) {
        std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << '\n';
        SDL_Quit();
        return false;
    }

    running_ = true;
    return true;
}

void Engine::run() {
    SDL_Event event;
    while (running_) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running_ = false;
            }
        }
        SDL_Delay(16);
    }
}

void Engine::shutdown() {
    if (window_) {
        SDL_DestroyWindow(window_);
        window_ = nullptr;
    }
    if (SDL_WasInit(SDL_INIT_VIDEO)) {
        SDL_Quit();
    }
}
