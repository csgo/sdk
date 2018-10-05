#pragma once
#include <cstdint>

class i_client_entity_list {
public:
	void* get_client_entity( int index ) {
		using original_fn = void*( __thiscall* )( i_client_entity_list*, int );
		return ( *( original_fn** ) this ) [ 3 ]( this, index );
	}
	void* get_client_entity( uintptr_t handle ) {
		using original_fn = void*( __thiscall* )( i_client_entity_list*, uintptr_t );
		return ( *( original_fn** ) this ) [ 4 ]( this, handle );
	}
};