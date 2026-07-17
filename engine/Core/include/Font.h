#ifndef FONT_H
#define FONT_H


#include <string>

struct TTF_Font;

namespace GameEngine {

    class Font final
	{
	public:
		TTF_Font* GetFont() const;
		explicit Font(const std::string& fullPath, unsigned int fontSize);

		~Font();

		Font(const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &) = delete;
		Font & operator= (const Font &&) = delete;
	private:
		TTF_Font* m_pFont;
	};

}

#endif //FONT_H