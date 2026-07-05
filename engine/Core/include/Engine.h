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

        glm::vec2 GetSize() const {return {m_width,m_height};}

    private:
        std::string m_title;
        int m_width;
        int m_height;
        SDL_Window* m_window = nullptr;
        bool m_running = false;

        std::unique_ptr<Scene> m_currentScene{};
    };

}
