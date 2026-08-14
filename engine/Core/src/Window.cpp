#include "Window.h"

namespace GameEngine
{
    Window::Window(const std::string& title, int width, int height)
        : m_title(title), m_width(width), m_height(height) {}

    Window::~Window() { Shutdown(); }

    bool Window::Init()
    {
        m_window = SDL_CreateWindow(
            m_title.c_str(),
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            m_width, m_height,
            SDL_WINDOW_SHOWN
        );
        if (!m_window)
        {
            std::cerr << "SDL_CreateWindow Error: " << SDL_GetError() << '\n';
            return false;
        }
        return true;
    }

    void Window::Shutdown()
    {
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            m_window = nullptr;
        }
    }
}