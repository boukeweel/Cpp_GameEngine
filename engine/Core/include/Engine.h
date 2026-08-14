#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>
#include <memory>
#include <string>
#include <utility>
#include "Scene.h"
#include "Window.h"

namespace GameEngine {

    class Scene;

    class Engine {
    public:
        Engine(const std::string& title, int width, int height);
        ~Engine();

        bool init(const std::string& resourcePath);
        void run();
        void shutdown();

    private:
        std::string m_title{"small engine"};
        int m_width{720};
        int m_height{480};
        Window m_window;
        bool m_running = false;
    };

}

#endif //ENGINE_H