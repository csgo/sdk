#pragma once
#include "../../source-sdk/classes/c_usercmd.hpp"

class i_input {
public:
	c_usercmd * get_user_cmd( int slot, int sequence_num ) {
		using original_fn = c_usercmd * ( __thiscall* )( void*, int, int );
		return ( *( original_fn** ) this )[ 8 ]( this, slot, sequence_num );
	}
};