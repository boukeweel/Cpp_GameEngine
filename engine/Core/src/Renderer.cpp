#include "Renderer.h"
#include "Camera.h"
#include "Texture2D.h"
#include <SDL_render.h>
#include <SDL.h>
#include <memory>
#include "Scene.h"
#include "glm/ext/vector_float2.hpp"

namespace GameEngine
{
	int GetOpenGLDriverIndex()
	{
		auto openglIndex = -1;
		const auto driverCount = SDL_GetNumRenderDrivers();
		for (auto i = 0; i < driverCount; i++)
		{
			SDL_RendererInfo info;
			if (!SDL_GetRenderDriverInfo(i, &info))
				if (!strcmp(info.name, "opengl"))
					openglIndex = i;
		}
		return openglIndex;
	}

	void Renderer::Init(SDL_Window *window)
	{
    	m_pWindow = window;
    	m_pRenderer = SDL_CreateRenderer(m_pWindow, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
    	if(!m_pRenderer)
    	{
        	SDL_Log("Failed to create renderer: %s", SDL_GetError());
    	}
		CreateCamera();
	}

	void Renderer::CreateCamera()
	{
		int width{};
		int height{};
		SDL_GetWindowSize(m_pWindow, &width, &height);
		m_camera = std::make_unique<Camera>(glm::vec2{width,height});
	}

	void Renderer::Render(const Scene& currentScene) const
	{
    	const auto& clearColor = GetClearColor();
    	SDL_SetRenderDrawColor(m_pRenderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    	SDL_RenderClear(m_pRenderer);

    	currentScene.Render();

    	SDL_RenderPresent(m_pRenderer);
	}

	void Renderer::Destroy()
	{
    	if (m_pRenderer != nullptr)
		{
			SDL_DestroyRenderer(m_pRenderer);
			m_pRenderer = nullptr;
		}
	}

	void Renderer::RenderRect(const SDL_Rect &rect)
	{
    	SDL_SetRenderDrawColor(GetSDLRenderer(), 255, 0, 0, 255);
		SDL_RenderDrawRect(GetSDLRenderer(), &rect);
	}

	void Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height, const float angle) const
	{			
		glm::vec2 screenPos = m_camera->WorldToScreen({x,y});;
		SDL_Rect dst{};
		dst.x = static_cast<int>(screenPos.x);
		dst.y = static_cast<int>(screenPos.y);
		dst.w = static_cast<int>(width);
		dst.h = static_cast<int>(height);

		SDL_Point center{};
		center.x = dst.w / 2;
		center.y = dst.h / 2;

		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_NONE);
	}

	void Renderer::RenderTexture(const Texture2D& texture, float x, float y, const float angle) const
	{
		SDL_Rect dst{};
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		
		RenderTexture(texture,x,y,dst.w,dst.h,angle);
	}

	void Renderer::RenderTextureUI(const Texture2D& texture, float x, float y, float width, float height, const float angle) const
	{
		SDL_Rect dst{};
		dst.x = static_cast<int>(x);
		dst.y = static_cast<int>(y);
		dst.w = static_cast<int>(width);
		dst.h = static_cast<int>(height);

		SDL_Point center{};
		center.x = dst.w / 2;
		center.y = dst.h / 2;

		SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, angle, &center, SDL_FLIP_NONE);
	}
	void Renderer::RenderTextureUI(const Texture2D& texture, float x, float y, const float angle) const
	{
		SDL_Rect dst{};
		SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
		RenderTextureUI(texture,x,y,dst.w,dst.h,angle);
	}
}


