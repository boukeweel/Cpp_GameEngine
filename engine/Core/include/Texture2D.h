#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include <glm/vec2.hpp>


struct SDL_Texture;
namespace GameEngine {

    class Texture2D final
    {
    public:
	    explicit Texture2D(SDL_Texture* texture);
	    ~Texture2D();

	    SDL_Texture* GetSDLTexture() const;
	    glm::vec2 GetSize() const;

	    Texture2D(const Texture2D& other) = delete;
	    Texture2D(Texture2D&& other) = delete;
	    Texture2D& operator=(const Texture2D& other) = delete;
	    Texture2D& operator=(Texture2D&& other) = delete;

    private:
	    SDL_Texture* m_Texture;
};

}

#endif //TEXTURE2D_H