#pragma once

#include <SDL.h>
#include "Singleton.h"

namespace GameEngine
{

    class Renderer final : public Singleton<Renderer>
    {
        SDL_Renderer* m_pRenderer = nullptr;
        SDL_Window* m_pWindow = nullptr;
        SDL_Color m_ClearColor = { 0, 0, 0, 255 };

    public:
        void Init(SDL_Window* window);
        void Render();
        void Destroy();

        void RenderRect(const SDL_Rect& rect);

        SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

        const SDL_Color& GetClearColor() const { return m_ClearColor; }
        void SetClearColor(const SDL_Color& color) { m_ClearColor = color; }
    };


}