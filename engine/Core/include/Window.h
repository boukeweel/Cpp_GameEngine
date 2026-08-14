#ifndef WINDOW_H
#define WINDOW_H

#include "IWindowInfo.h"
#include <SDL.h>
#include <string>
#include <glm/glm.hpp>
#include "IWindowInfo.h"
#include <iostream>

namespace GameEngine
{
    class Window : public IWindowInfo
    {
    public:
        Window(const std::string& title, int width, int height);
        ~Window();

        bool Init();
        void Shutdown();

        SDL_Window* GetHandle() const { return m_window; } // for Renderer::Init only

        glm::vec2 GetSize() const override { return { m_width, m_height }; }

    private:
        std::string m_title;
        int m_width;
        int m_height;
        SDL_Window* m_window = nullptr;
    };
}

#endif