#include "tex.h"

TextureHandler* textureHandler;

TextureHandler::TextureHandler(DV2& dv2, std::size_t first, std::size_t last) :
	first(first)
{
	textures.reserve(last + 1 - first);
	for (std::size_t i = first; i <= last; i++)
	{
		textures.push_back(dv2.createTexture(MAKEINTRESOURCEW(i), MAKEINTRESOURCEW(RSCT_DATA)));
	}
}

void Tex::draw(DV2& dv2, float x, float y, float angle) const
{
	dv2.draw((*textureHandler)[texture], x, y, this->x, this->y, getWidth(), getHeight(), angle);
}

void Tex::draw(DV2& dv2, float x, float y, float w, float h, float angle) const
{
	dv2.draw((*textureHandler)[texture], x, y, w, h, this->x, this->y, getWidth(), getHeight(), angle);
}