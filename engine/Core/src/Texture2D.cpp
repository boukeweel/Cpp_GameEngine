#include "Texture2D.h"
#include <SDL.h>

namespace GameEngine {

    Texture2D::Texture2D(SDL_Texture* texture)
    {
    	m_Texture = texture;
    }

    Texture2D::~Texture2D()
    {
        if(m_Texture)
    	    SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
    }

    SDL_Texture* Texture2D::GetSDLTexture() const
    {
    	return m_Texture;
    }

    glm::vec2 Texture2D::GetSize() const
    {
    	int w, h;
        if (SDL_QueryTexture(m_Texture, nullptr, nullptr, &w, &h) != 0)
        {
            SDL_Log("Getting Texture size gone wrong: %s", SDL_GetError());
            return { 0, 0 };
        }
        return { w, h };
    }
}