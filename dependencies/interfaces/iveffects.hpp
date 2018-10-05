#pragma once
#include "../../source-sdk/structs/dlight.hpp"

class iv_effects {
public:
	dlight_t * alloc( int key ) {
		using original_fn = dlight_t * ( __thiscall* )( void*, int );
		return ( *( original_fn** ) this ) [ 4 ]( this, key );
	}
};