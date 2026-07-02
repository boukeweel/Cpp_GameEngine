#pragma once

#include "Component.h"
#include <SDL_pixels.h>
#include <memory>
#include <string>

namespace GameEngine{
    class Font;
    class Texture2D;
    class GameObject;
    class TextComponent final : public Component{
    public:
        TextComponent(GameObject* pParentObject, const std::string& text, std::shared_ptr<Font> font,SDL_Color color = { 255,255,255,255 });
    
        void Update() override;
        void Render() const override;

        void SetText(const std::string& newText);
        void SetFont(std::shared_ptr<Font> newFont);
        void SetColor(SDL_Color newColor);
        //void SetFontSize(unsigned int newSize);
    private:
        bool m_needsUpdate{};
        std::string m_text{};
        std::shared_ptr<Font> m_pfont{};
        std::unique_ptr<Texture2D> m_ptextTexture;
        unsigned int m_fontSize{11};
        SDL_Color m_color{};
    public:
        virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;
    };
}