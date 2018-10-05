#pragma once

class game_event {
public:
	const char* get_name( ) {
		using original_fn = const char*( __thiscall* )( game_event* );
		return ( *( original_fn** ) this ) [ 1 ]( this );
	}
	int get_int( const char* name ) {
		using original_fn = int( __thiscall* )( game_event*, const char*, int );
		return ( *( original_fn** ) this ) [ 6 ]( this, name, 0 );
	}
};

class game_event_listener {
public:
	virtual ~game_event_listener( ) { }

	virtual void fire_game_event( game_event* event ) = 0;
	virtual int get_debug_id( ) = 0;

public:
	int debug_id;
};