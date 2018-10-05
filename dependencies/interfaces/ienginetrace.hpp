#pragma once
#include "../../source-sdk/classes/trace.hpp"

class i_engine_trace {
public:
	void trace_ray( const ray_t& ray, unsigned int mask, i_trace_filter* filter, trace_t* trace ) {
		using original_fn = void( __thiscall* )( i_engine_trace*, const ray_t&, unsigned int, i_trace_filter*, trace_t* );
		return ( *( original_fn** ) this ) [ 5 ]( this, ray, mask, filter, trace );
	}
};