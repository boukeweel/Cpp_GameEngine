#include "UITextElement.h"
#include "CanvasObject.h"
#include "UIElement.h"
#include "Renderer.h"
#include "UITransform.h"
#include "Font.h"
#include "Texture2D.h"
#include <SDL_ttf.h>
#include <memory>
#include <string>
#include <utility>

namespace GameEngine
{
    UITextElement::UITextElement(CanvasObject* pParentObject, const std::string& text, 
        std::shared_ptr<Font> font,SDL_Color color)
        : UIElement(pParentObject), m_needsUpdate(true), m_text(text), m_pfont(std::move(font)), m_ptextTexture(nullptr), m_fontSize{1}, m_color{color}
        {}

    void UITextElement::Update()
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

    void UITextElement::Render() const
    {
        if(m_ptextTexture != nullptr)
        {
            const glm::vec2 pos =  m_owner->GetTransform().GetLocation();
            const glm::vec2 Size = m_owner->GetTransform().GetSize();
            Renderer::GetInstance().RenderTextureUI(*m_ptextTexture, pos.x, pos.y,Size.x,Size.y);
        }
    }
    
    void UITextElement::SetText(const std::string& newText)
    {
        m_text = newText;
        m_needsUpdate = true;
    }

    void UITextElement::SetFont(std::shared_ptr<Font> newFont)
    {
        m_pfont = std::move(newFont);
        m_needsUpdate = true;
    }

    void UITextElement::SetColor(SDL_Color newColor)
    {
        m_color = newColor;
        m_needsUpdate = true;
    }
}