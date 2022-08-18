#pragma once
#include <map>
#include "dv2.h"
#include "tex.h"

enum struct TextAlign
{
	left,
	centre,
	right
};

enum struct CharSize
{
	cs50,
	cs45,
	cs40,
	cs35,
	cs30,
	cs25,
	cs20,
	cs15,
	cs10,
	cs05,
	cs00
};

struct FontSpritesheet
{
	std::size_t texture;
	const CharSize* sizes;
};

class Font
{
private:
	std::map<char32_t, FontSpritesheet> spritesheets;
	float extraWidth;
public:
	Font(std::map<char32_t, FontSpritesheet> spritesheets, float extraWidth = 0.0f) :
		spritesheets(std::move(spritesheets)),
		extraWidth(extraWidth) {}

	float getCharWidth(char32_t c, float height);
	float getTextWidth(const char32_t* str, float height);
	float getTextWidth(const char* str, float height);
	
	// Returnerar bredden
	float drawChar(DV2& dv2, char32_t c, float x, float y, float h, float angle = 0.0f, Colour clrShift = Colour{1.0f, 1.0f, 1.0f, 1.0f});
	void drawText(DV2& dv2, const char* str, float x, float y, float h, TextAlign align, float angle = 0.0f, Colour clrShift = Colour{1.0f, 1.0f, 1.0f, 1.0f});
};