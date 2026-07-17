#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <memory>
#include <string>

#include "Singleton.h"

namespace GameEngine
{
    class Font;
    class Texture2D;

    class ResourceManager final : public GameEngine::Singleton<ResourceManager>
    {
    public:
    	void Init(const std::string& resourcePath);

    	[[nodiscard]] std::unique_ptr<Texture2D> loadTexture(const std::string& file) const;

        [[nodiscard]] std::shared_ptr<Font> LoadFont(const std::string& file, unsigned int fontSize) const;

    private:
    	std::string m_ResourcePath;
    };
}

#endif //RESOURCE_MANAGER_H