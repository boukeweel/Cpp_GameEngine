#pragma once

#include <SDL.h>
#include <string>

class Engine {
public:
    Engine(const std::string& title, int width, int height);
    ~Engine();

    bool init();
    void run();
    void shutdown();

private:
    std::string title_;
    int width_;
    int height_;
    SDL_Window* window_ = nullptr;
    bool running_ = false;
};
