#include "fonts.h"

using enum CharSize;

const CharSize fontSizes[256]{
	cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50,
	cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50,
	cs25, cs40, cs25, cs05, cs25, cs05, cs10, cs45, cs25, cs25, cs35, cs00, cs40, cs15, cs40, cs15,
	cs15, cs30, cs20, cs20, cs15, cs15, cs15, cs10, cs20, cs15, cs40, cs40, cs20, cs15, cs20, cs20,
	cs00, cs05, cs25, cs10, cs20, cs15, cs20, cs10, cs15, cs40, cs20, cs10, cs15, cs10, cs15, cs10,
	cs20, cs10, cs15, cs15, cs10, cs15, cs10, cs05, cs10, cs10, cs10, cs20, cs15, cs20, cs25, cs15,
	cs30, cs20, cs20, cs25, cs20, cs20, cs20, cs15, cs20, cs40, cs35, cs20, cs40, cs10, cs20, cs15,
	cs20, cs20, cs25, cs25, cs25, cs20, cs10, cs05, cs20, cs10, cs10, cs30, cs45, cs30, cs05, cs50,
	cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50,
	cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50,
	cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50,
	cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50, cs50,
	cs05, cs05, cs50, cs50, cs05, cs05, cs50, cs50, cs15, cs15, cs15, cs50, cs50, cs50, cs50, cs50,
	cs50, cs50, cs50, cs50, cs50, cs50, cs10, cs50, cs50, cs50, cs50, cs15, cs15, cs50, cs50, cs50,
	cs20, cs20, cs50, cs50, cs20, cs20, cs50, cs50, cs20, cs20, cs20, cs50, cs50, cs50, cs50, cs50,
	cs50, cs50, cs50, cs50, cs50, cs50, cs15, cs50, cs50, cs50, cs50, cs20, cs20, cs50, cs50, cs50
};

Font* font;