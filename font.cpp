#include "font.h"

char32_t readUtf8Char(const char*& cur)
{
	if (static_cast<unsigned char>(*cur) < 0b1000'0000)
		return *cur++;
	char32_t ret = 0;
	int numConts = 0;
	if (static_cast<unsigned char>(*cur) >= 0b1111'1000)
	{
		cur++;
		return U'\uFFFD';
	}
	if (static_cast<unsigned char>(*cur) >= 0b1111'0000)
	{
		ret = *cur++ & 0b0000'0111;
		numConts = 3;
	}
	else if (static_cast<unsigned char>(*cur) >= 0b1110'0000)
	{
		ret = *cur++ & 0b0000'1111;
		numConts = 2;
	}
	else if (static_cast<unsigned char>(*cur) >= 0b110'0000)
	{
		ret = *cur++ & 0b0001'1111;
		numConts = 1;
	}
	else
	{
		cur++;
		return U'\uFFFD';
	}
	while (static_cast<unsigned char>(*cur) >= 0b1000'0000 && static_cast<unsigned char>(*cur) < 0b1100'0000)
	{
		if (numConts-- == 0)
			return U'\uFFFD';
		ret <<= 6;
		ret |= *cur++ & 0b0011'1111;
	}
	if (numConts != 0 || ret >= 0x110000)
		return U'\uFFFD';
	return ret;
}

float getCharSize(CharSize cs)
{
	switch (cs)
	{
		case CharSize::cs50:
		return 0.0f;
		case CharSize::cs45:
		return 0.1f;
		case CharSize::cs40:
		return 0.2f;
		case CharSize::cs35:
		return 0.3f;
		case CharSize::cs30:
		return 0.4f;
		case CharSize::cs25:
		return 0.5f;
		case CharSize::cs20:
		return 0.6f;
		case CharSize::cs15:
		return 0.7f;
		case CharSize::cs10:
		return 0.8f;
		case CharSize::cs05:
		return 0.9f;
		case CharSize::cs00:
		return 1.0f;
	}
}

float Font::getCharWidth(char32_t c, float height)
{
	if (!spritesheets.contains(c >> 8u))
		return 0.0f;
	FontSpritesheet& ss = spritesheets.at(c >> 8u);
	Texture& tex = (*textureHandler)[ss.texture];
	return height * tex.getWidth() / tex.getHeight() * (getCharSize(ss.sizes[c & 0xFFu]) + extraWidth);
}

float Font::getTextWidth(const char32_t* str, float height)
{
	float width = 0.0f;
	while (*str)
	{
		width += getCharWidth(*str, height);
		str++;
	}
	return width;
}

float Font::getTextWidth(const char* str, float height)
{
	std::u32string str32;
	while (const char32_t c = readUtf8Char(str))
		str32 += c;
	return getTextWidth(str32.c_str(), height);
}

float Font::drawChar(DV2& dv2, char32_t c, float x, float y, float h, float angle, Colour clrShift)
{
	if (spritesheets.contains(c >> 8u))
	{
		FontSpritesheet& ss = spritesheets.at(c >> 8u);
		Texture& tex = (*textureHandler)[ss.texture];
		const float charsize = getCharSize(ss.sizes[c & 0xFFu]);
		const float charw = tex.getWidth() / 16.0f;
		const float charh = tex.getHeight() / 16.0f;
		const float w = h * tex.getWidth() / tex.getHeight();
		const float spacewidth = h * tex.getWidth() / tex.getHeight() * (charsize + extraWidth);
		dv2.draw(
			tex,
			x + spacewidth / 2.0f,
			y,
			w,
			h,
			(c & 0xFu) * charw,
			((c & 0xFFu) >> 4u) * charh,
			charw,
			charh,
			angle,
			clrShift
		);
		return spacewidth;
	}
	return 0.0f;
}

void Font::drawText(DV2& dv2, const char* str, float x, float y, float h, TextAlign align, float angle, Colour clrShift)
{
	std::u32string str32;
	while (const char32_t c = readUtf8Char(str))
		str32 += c;
	float currx;
	switch (align)
	{
		case TextAlign::left:
			currx = x;
		break;
		case TextAlign::centre:
			currx = x - getTextWidth(str32.c_str(), h) / 2.0f;
		break;
		case TextAlign::right:
			currx = x - getTextWidth(str32.c_str(), h);
		break;
	}
	for (const auto& c : str32)
		currx += drawChar(dv2, c, currx, y, h, angle, clrShift);
}