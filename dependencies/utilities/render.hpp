#pragma once
#include <string>
#include "singleton.hpp"
#include "../interfaces/interfaces.hpp"

#include "..//..//core/menu/zgui/zgui.hpp"

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

class render : public singleton<render> {
public: // fonts
	DWORD main_font;

public: // basic renderer
	void setup_fonts() {
		static bool _o = false;
		if (!_o) {
			main_font = interfaces::surface->font_create();

			interfaces::surface->set_font_glyph(main_font, "Tahoma", 12, 500, 0, 0, font_flags::fontflag_outline);
			_o = true;
		}
	}
};