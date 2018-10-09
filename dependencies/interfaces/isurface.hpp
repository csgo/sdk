#pragma once
#include "../../source-sdk/structs/vertex_t.hpp"

class i_surface {
public:
	void set_drawing_color( int r, int g, int b, int a = 255 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this )[ 15 ]( this, r, g, b, a );
	}
	void set_text_color( int r, int g, int b, int a = 255 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this )[ 25 ]( this, r, g, b, a );
	}
	void draw_polygon( int n, vertex_t *vertice, bool clip_vertices = true ) {
		using original_fn = void( __thiscall* )( i_surface*, int, vertex_t*, bool );
		return ( *( original_fn** ) this )[ 106 ]( this, n, vertice, clip_vertices );
	}
	void draw_filled_rectangle( int x, int y, int w, int h ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this )[ 16 ]( this, x, y, x + w, y + h );
	}
	void set_texture( int id ) {
		using original_fn = void( __thiscall* )( i_surface*, int );
		return ( *( original_fn** ) this )[ 38 ]( this, id );
	}
	void set_texture_rgba( int id, const unsigned char *rgba, int wide, int tall ) {
		using original_fn = void( __thiscall* )( i_surface*, int, const unsigned char *, int, int, int, bool );
		return ( *( original_fn** ) this )[ 37 ]( this, id, rgba, wide, tall, 0, false );
	}
	int create_new_texture_id( bool procedural = false ) {
		using original_fn = int( __thiscall* )( i_surface*, bool );
		return ( *( original_fn** ) this )[ 43 ]( this, procedural );
	}
	void draw_outlined_rect( int x, int y, int w, int h ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this )[ 18 ]( this, x, y, x + w, y + h );
	}
	void draw_line( int x1, int y1, int x2, int y2 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this )[ 19 ]( this, x1, y1, x2, y2 );
	}
	void draw_text_font( unsigned long font ) {
		using original_fn = void( __thiscall* )( i_surface*, unsigned long );
		return ( *( original_fn** ) this )[ 23 ]( this, font );
	}
	void draw_text_pos( int x, int y ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int );
		return ( *( original_fn** ) this )[ 26 ]( this, x, y );
	}
	void draw_render_text( const wchar_t* text, int textLen ) {
		using original_fn = void( __thiscall* )( i_surface*, const wchar_t*, int, int );
		return ( *( original_fn** ) this )[ 28 ]( this, text, textLen, 0 );
	}
	unsigned long font_create( ) {
		using original_fn = unsigned int( __thiscall* )( i_surface* );
		return ( *( original_fn** ) this )[ 71 ]( this );
	}
	void set_font_glyph( unsigned long font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags ) {
		using original_fn = void( __thiscall* )( i_surface*, unsigned long, const char*, int, int, int, int, int, int, int );
		return ( *( original_fn** ) this )[ 72 ]( this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0 );
	}
	void get_text_size( unsigned long font, const wchar_t* text, int& wide, int& tall ) {
		using original_fn = void( __thiscall* )( i_surface*, unsigned long, const wchar_t*, int&, int& );
		return ( *( original_fn** ) this )[ 79 ]( this, font, text, wide, tall );
	}
};