#pragma once

class i_surface {
public:
	void set_drawing_color( int r, int g, int b, int a = 255 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this ) [ 15 ]( this, r, g, b, a );
	}
	void set_text_color( int r, int g, int b, int a = 255 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this ) [ 25 ]( this, r, g, b, a );
	}
	void draw_filled_rect( int x, int y, int w, int h ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this ) [ 16 ]( this, x, y, x + w, y + h );
	}
	void draw_outlined_rect( int x, int y, int w, int h ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this ) [ 18 ]( this, x, y, x + w, y + h );
	}
	void draw_line( int x1, int y1, int x2, int y2 ) {
		using original_fn = void( __thiscall* )( i_surface*, int, int, int, int );
		return ( *( original_fn** ) this ) [ 19 ]( this, x1, y1, x2, y2 );
	}
};