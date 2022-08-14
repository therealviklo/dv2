#pragma once
#include <vector>
#include "dv2.h"

class TextureHandler
{
private:
	std::vector<Texture> textures;
	std::size_t first;
public:
	TextureHandler(DV2& dv2, std::size_t first, std::size_t last);

	Texture& operator[](std::size_t texture)
	{
		return textures[texture - first];
	}
};

/* Om man vill kunna använda Texar med olika DV2:er så kan man
   använda t.ex. en std::map från const DV2* till TextureHandler*,
   men det behövs inte nu och jag bryr mig mer om effektivitet. */
extern TextureHandler* textureHandler;

struct Tex
{
	std::size_t texture;
	float x;
	float y;
	float w;
	float h;

	void draw(DV2& dv2, float x, float y, float angle = 0.0f) const;
	void draw(DV2& dv2, float x, float y, float w, float h, float angle = 0.0f) const;

	float getWidth() const noexcept { return w ? w : (*textureHandler)[texture].getWidth(); }
	float getHeight() const noexcept { return h ? h : (*textureHandler)[texture].getHeight(); }
};
