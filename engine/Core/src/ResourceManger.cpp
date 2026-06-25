#include "ResourceManger.h"

#include <SDL.h>
#include <SDL_image.h>

#include "Renderer.h"
#include "Texture2D.h"

namespace GameEngine{

    void ResourceManager::SetResourcePath(const std::string& resourcePath)
    {
    	m_ResourcePath = resourcePath;	
    }

    std::unique_ptr<Texture2D> ResourceManager::loadTexture(const std::string& file) const
    {
    	const auto fullPath = m_ResourcePath + file;
	    auto texture = IMG_LoadTexture(Renderer::GetInstance().GetSDLRenderer(), fullPath.c_str());
	    if (texture == nullptr)
	    {
		    throw std::runtime_error(std::string("Failed to load texture: ") + IMG_GetError());

        }
	    return std::unique_ptr<Texture2D>(new Texture2D(texture));
    }
}