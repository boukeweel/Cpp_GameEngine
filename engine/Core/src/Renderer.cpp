#include "Renderer.h"

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
	}

	void Renderer::Render()
	{
    	const auto& clearColor = GetClearColor();
    	SDL_SetRenderDrawColor(m_pRenderer, clearColor.r, clearColor.g, clearColor.b, clearColor.a);
    	SDL_RenderClear(m_pRenderer);

    	//todo: Render things here

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
}


