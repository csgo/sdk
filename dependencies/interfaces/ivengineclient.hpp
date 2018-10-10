#pragma once
#include <cstdint>
#include "../../source-sdk/math/vector3d.hpp"

struct player_info_t {
	int64_t __pad0;
	union {
		int64_t xuid;
		struct {
			int xuidlow;
			int xuidhigh;
		};
	};
	char name [ 128 ];
	int userid;
	char guid [ 33 ];
	unsigned int friendsid;
	char friendsname [ 128 ];
	bool fakeplayer;
	bool ishltv;
	unsigned int customfiles [ 4 ];
	unsigned char filesdownloaded;
};

class iv_engine_client {
public:
	int get_local_player( ) {
		using original_fn = int( __thiscall* )( iv_engine_client* );
		return ( *( original_fn** ) this ) [ 12 ]( this );
	}
	int get_player_for_user_id( int user_id ) {
		using original_fn = int( __thiscall* )( iv_engine_client*, int );
		return ( *( original_fn** ) this ) [ 9 ]( this, user_id );
	}
	void get_player_info( int index, player_info_t* info ) {
		using original_fn = void( __thiscall* )( iv_engine_client*, int, player_info_t* );
		return ( *( original_fn** ) this ) [ 8 ]( this, index, info );
	}
	void get_screen_size( int& width, int& height ) {
		using original_fn = void( __thiscall* )( iv_engine_client*, int&, int& );
		return ( *( original_fn** ) this ) [ 5 ]( this, width, height );
	}
	void execute_cmd( const char* cmd ) {
		using original_fn = void( __thiscall* )( iv_engine_client*, const char* );
		return ( *( original_fn** ) this ) [ 108 ]( this, cmd ); // this always seems to crash whilst debugging, just feel free to continue.
	}
	void set_view_angles( vec3_t& angles ) {
		using original_fn = void( __thiscall* )( iv_engine_client*, vec3_t& );
		return ( *( original_fn** ) this ) [ 19 ]( this, angles );
	}
	vec3_t get_view_angles( ) {
		vec3_t temp;
		using original_fn = void( __thiscall* )( iv_engine_client*, vec3_t& );
		( *( original_fn** ) this ) [ 18 ]( this, temp );
		return temp;
	}
};