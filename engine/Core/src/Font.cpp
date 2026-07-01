#include "Font.h"
#include <stdexcept>
#include <SDL_ttf.h>

namespace GameEngine {

    TTF_Font* Font::GetFont() const
    {
        return m_pFont;
    }

    Font::Font(const std::string& fullPath, unsigned int fontSize)
    {
        m_pFont = TTF_OpenFont(fullPath.c_str(), fontSize);
        if (m_pFont == nullptr)
        {
            throw std::runtime_error(std::string("Failed to load font: ") + TTF_GetError());
        }
    }

    Font::~Font()
    {
        if (m_pFont)
        {
            TTF_CloseFont(m_pFont);
            m_pFont = nullptr;
        }
    }
}