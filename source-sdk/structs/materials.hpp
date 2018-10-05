#pragma once

using material_handle_t = unsigned short;
class i_material {
public:
	const char* get_name( ) {
		using original_fn = const char*( __thiscall* )( i_material* );
		return ( *( original_fn** ) this ) [ 0 ]( this );
	}
	const char* get_group_name( ) {
		using original_fn = const char*( __thiscall* )( i_material* );
		return ( *( original_fn** ) this ) [ 1 ]( this );
	}
	void set_alpha( float alpha ) {
		using original_fn = void( __thiscall* )( i_material*, float );
		return ( *( original_fn** ) this ) [ 27 ]( this, alpha );
	}
	void set_alpha( int alpha ) {
		using original_fn = void( __thiscall* )( i_material*, float );
		return ( *( original_fn** ) this ) [ 27 ]( this, static_cast< float >( alpha ) / 255.f );
	}
	void set_color( float r, float g, float b ) {
		using original_fn = void( __thiscall* )( i_material*, float, float, float );
		return ( *( original_fn** ) this ) [ 28 ]( this, r, g, b );
	}

	void set_color( int r, int g, int b ) {
		using original_fn = void( __thiscall* )( i_material*, float, float, float );
		return ( *( original_fn** ) this ) [ 28 ]( this, r / 255.f, g / 255.f, b / 255.f );
	}
	void set_color( int color32 ) {
		int r1 = ( color32 >> 16 ) & 0xff;
		int g1 = ( color32 >> 8 ) & 0xff;
		int b1 = color32 & 0xff;
		i_material::set_color( r1, g1, b1 );
	}
	void set_flag( int flag, bool on ) {
		using original_fn = void( __thiscall* )( i_material*, int, bool );
		return ( *( original_fn** ) this ) [ 29 ]( this, flag, on );
	}
};