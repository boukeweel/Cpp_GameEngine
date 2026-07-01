#pragma once

#include <SDL.h>
#include "Scene.h"
#include "Singleton.h"

namespace GameEngine
{
    class Texture2D;
    class GameObject;
    class Scene;

    class Renderer final : public Singleton<Renderer>
    {
        SDL_Renderer* m_pRenderer = nullptr;
        SDL_Window* m_pWindow = nullptr;
        SDL_Color m_ClearColor = { 0, 0, 0, 255 };

    public:
        void Init(SDL_Window* window);
        void Render(const Scene& currentScene) const;
        void Destroy();

        void RenderRect(const SDL_Rect& rect);
        void RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const float angle = 0) const;
        void RenderTexture(const Texture2D& texture, float x, float y, const float angle = 0) const;

        SDL_Renderer* GetSDLRenderer() const { return m_pRenderer; }

        const SDL_Color& GetClearColor() const { return m_ClearColor; }
        void SetClearColor(const SDL_Color& color) { m_ClearColor = color; }
    };


}