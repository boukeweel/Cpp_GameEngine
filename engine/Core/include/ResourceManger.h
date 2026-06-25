#pragma once
#include <memory>
#include <string>

#include "Singleton.h"

namespace GameEngine
{

    class Texture2D;

    class ResourceManager final : public GameEngine::Singleton<ResourceManager>
    {
    public:
    	void SetResourcePath(const std::string& resourcePath);

    	[[nodiscard]] std::unique_ptr<Texture2D> loadTexture(const std::string& file) const;

    private:
    	std::string m_ResourcePath;
    };
}