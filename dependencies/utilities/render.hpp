#pragma once
#include <string>
#include "../interfaces/interfaces.hpp"
#include "..//..//source-sdk/misc/color.hpp"

namespace render {
	enum font_flags {
		fontflag_none,
		fontflag_italic = 0x001,
		fontflag_underline = 0x002,
		fontflag_strikeout = 0x004,
		fontflag_symbol = 0x008,
		fontflag_antialias = 0x010,
		fontflag_gaussianblur = 0x020,
		fontflag_rotary = 0x040,
		fontflag_dropshadow = 0x080,
		fontflag_additive = 0x100,
		fontflag_outline = 0x200,
		fontflag_custom = 0x400,
		fontflag_bitmap = 0x800,
	};

	extern unsigned long main_font;

	void setup_fonts();

	void line(int x, int y, int x2, int y2, color c) noexcept;
	void rect(int x, int y, int x2, int y2, color c) noexcept;
	void filled_rect(int x, int y, int x2, int y2, color c) noexcept;
	void text(int x, int y, color color, int font, bool center, std::string str) noexcept;
	void get_text_size(unsigned long font, std::string str, int& width, int& height) noexcept;
	float get_frametime() noexcept;
};