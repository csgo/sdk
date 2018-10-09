#pragma once
#include <string>
#include "singleton.hpp"
#include "../interfaces/interfaces.hpp"

class render : public singleton<render> {
public: // basic renderer
	void draw_line( int x1, int y1, int x2, int y2, color colour ) {
		interfaces::surface->set_drawing_color( colour.r, colour.g, colour.b, colour.a = 255 );
		interfaces::surface->draw_line( x1, y1, x2, y2 );
	}
	void draw_text( int x, int y, unsigned long font, const char* string, bool text_centered, color colour ) {
		va_list va_alist;
		char buf[ 1024 ];
		va_start( va_alist, string );
		_vsnprintf( buf, sizeof( buf ), string, va_alist );
		va_end( va_alist );
		wchar_t wbuf[ 1024 ];
		MultiByteToWideChar( CP_UTF8, 0, buf, 256, wbuf, 256 );

		int width, height;
		interfaces::surface->get_text_size( font, wbuf, width, height );

		interfaces::surface->set_text_color( colour.r, colour.g, colour.b, colour.a = 255 );
		interfaces::surface->draw_text_font( font );
		if ( text_centered )
			interfaces::surface->draw_text_pos( x - ( width / 2 ), y );
		else
			interfaces::surface->draw_text_pos( x, y );
		interfaces::surface->draw_render_text( wbuf, wcslen( wbuf ) );
	}
	void draw_text( int x, int y, unsigned long font, std::string string, bool text_centered, color colour ) {
		std::wstring text = std::wstring( string.begin( ), string.end( ) );
		const wchar_t* converted_text = text.c_str( );

		int width, height;
		interfaces::surface->get_text_size( font, converted_text, width, height );

		interfaces::surface->set_text_color( colour.r, colour.g, colour.b, colour.a = 255 );
		interfaces::surface->draw_text_font( font );
		if ( text_centered )
			interfaces::surface->draw_text_pos( x - ( width / 2 ), y );
		else
			interfaces::surface->draw_text_pos( x, y );
		interfaces::surface->draw_render_text( converted_text, wcslen( converted_text ) );
	}
	void draw_filled_rect( int x, int y, int w, int h, color colour ) {
		interfaces::surface->set_drawing_color( colour.r, colour.g, colour.b, colour.a = 255 );
		interfaces::surface->draw_filled_rectangle( x, y, w, h );
	}
	void draw_outline( int x, int y, int w, int h, color colour ) {
		interfaces::surface->set_drawing_color( colour.r, colour.g, colour.b, colour.a = 255 );
		interfaces::surface->draw_outlined_rect( x + 1, y + 1, w - 2, h - 2 );
		interfaces::surface->draw_outlined_rect( x - 1, y - 1, w + 2, h + 2 );
	}
};