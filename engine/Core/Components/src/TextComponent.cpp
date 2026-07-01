#include "TextComponent.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include <memory>
#include <string>
#include <utility>
#include "GameObject.h"
#include "Transform.h"
#include "Renderer.h"


namespace GameEngine
{
    TextComponent::TextComponent(GameObject* pparentObject,const std::string& text, std::shared_ptr<Font> font, SDL_Color color):
	Component(pparentObject), m_needsUpdate(true), m_text(text), m_pfont(std::move(font)), m_ptextTexture(nullptr), m_fontSize{1}, m_color{color}
    {}


    void TextComponent::Update()
    {
        if(!m_needsUpdate) return;

        const auto surf = TTF_RenderText_Blended(m_pfont->GetFont(), m_text.c_str(),m_color);
        if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_ptextTexture = std::make_unique<Texture2D>(texture);
		m_needsUpdate = false;

    }

    void TextComponent::Render() const
    {
        if(m_ptextTexture != nullptr)
        {
            const auto pos =  m_Owner->GetTransform().GetWorldPosition();
            Renderer::GetInstance().RenderTexture(*m_ptextTexture, pos.x, pos.y);
        }
    }

    void TextComponent::SetText(const std::string& newText)
    {
        m_text = newText;
        m_needsUpdate = true;
    }

    void TextComponent::SetFont(std::shared_ptr<Font> newFont)
    {
        m_pfont = std::move(newFont);
        m_needsUpdate = true;
    }

    void TextComponent::SetColor(SDL_Color newColor)
    {
        m_color = newColor;
    }
}