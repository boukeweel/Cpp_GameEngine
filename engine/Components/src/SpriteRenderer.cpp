#include "SpriteRenderer.h"
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"
#include "ResourceManger.h"


namespace GameEngine {

    SpriteRenderer::SpriteRenderer(GameObject* owner, const std::string& texturePath)
        : Component(owner), m_TexturePath(texturePath)
    {
        SetTexture(texturePath);
    }

    SpriteRenderer::SpriteRenderer(GameObject* owner, std::unique_ptr<Texture2D> texture)
        : Component(owner), m_Texture(std::move(texture))
    {
    }

    SpriteRenderer::~SpriteRenderer()
    {
        
    }

    void SpriteRenderer::Render() const
    {
        if (!m_Texture)
        {
            SDL_Log("SpriteRenderer::Render called without texture");
            return;
        }

        const glm::vec3& position = m_Owner->GetTransform().GetWorldPosition();
        const glm::vec2& scale = m_Owner->GetTransform().GetScale();
        const float rotation = m_Owner->GetTransform().GetRotation().z;

        const glm::vec2 textureSize = m_Texture->GetSize();
        const glm::vec2 drawSize = textureSize * scale;

        if (drawSize.x <= 0.0f || drawSize.y <= 0.0f)
        {
            SDL_Log("SpriteRenderer::Render has invalid draw size: %f x %f", drawSize.x, drawSize.y);
            return;
        }

        Renderer::GetInstance().RenderTexture(*m_Texture, position.x, position.y, drawSize.x, drawSize.y, rotation);
    }

    void SpriteRenderer::SetTexture(const std::string& texturePath)
    {
        m_TexturePath = texturePath;
        m_Texture = GameEngine::ResourceManager::GetInstance().loadTexture(texturePath);
    }

    void SpriteRenderer::SetTexture(std::unique_ptr<Texture2D> texture)
    {
        m_Texture = std::move(texture);
    }

    

    

}