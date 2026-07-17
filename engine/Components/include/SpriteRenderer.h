#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H
#include "Component.h"
#include <string>
#include <SDL.h>
#include <memory>
#include "Texture2D.h"


namespace GameEngine {
    class GameObject;

    class SpriteRenderer final : public Component
    {
    public:
        SpriteRenderer(GameObject* owner, const std::string& texturePath);
        SpriteRenderer(GameObject* owner, std::unique_ptr<Texture2D> texture);
       
        void Render() const override;

        void SetTexture(const std::string& texturePath);
        void SetTexture(std::unique_ptr<Texture2D> texture);
        [[nodiscard]] Texture2D* GetTexture() const { return m_Texture.get(); }

    private:
        std::string m_TexturePath;
        std::unique_ptr<Texture2D> m_Texture;

    public:
        ~SpriteRenderer() override;
    	SpriteRenderer(const SpriteRenderer&) = delete;
    	SpriteRenderer& operator=(const SpriteRenderer&) = delete;
    	SpriteRenderer(SpriteRenderer&&) = delete;
    	SpriteRenderer& operator=(SpriteRenderer&&) = delete;
    };

}

#endif //SPRITE_RENDERER_H