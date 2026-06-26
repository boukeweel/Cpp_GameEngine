#pragma once

#include <SDL.h>
#include <memory>
#include <string>
#include <utility>
#include "Scene.h"

namespace GameEngine {

    class Scene;

    class Engine {
    public:
        Engine(const std::string& title, int width, int height);
        ~Engine();

        bool init(const std::string& resourcePath);
        void run();
        void shutdown();

        //temp until scene manager
        void SetScene(std::unique_ptr<Scene> newScene){m_currentScene = std::move(newScene);}

    private:
        std::string title_;
        int width_;
        int height_;
        SDL_Window* window_ = nullptr;
        bool running_ = false;

        std::unique_ptr<Scene> m_currentScene{};
    };

}
