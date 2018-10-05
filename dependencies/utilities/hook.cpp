#include "hook.hpp"
#include "../common_includes.hpp"

void prop_hook::setup( recv_prop* prop ) {
	this->prop = prop;
	this->original_fn = prop->proxy_fn;
}

void prop_hook::swap( recv_var_proxy_fn new_proxy ) {
	this->prop->proxy_fn = new_proxy;
}

void prop_hook::release( ) {
	this->prop->proxy_fn = this->original_fn;
}

recv_var_proxy_fn prop_hook::get_original( ) {
	return this->original_fn;
}

void vmt_hook::setup( void* class_pointer ) {
	this->table_pointer = reinterpret_cast< uintptr_t** >( class_pointer );
	this->original_table = *this->table_pointer;

	while ( this->original_table [ this->estimated_table_size ] )
		this->estimated_table_size++;

	this->new_table_pointer = new uintptr_t [ this->estimated_table_size * sizeof( uintptr_t ) ];
	memcpy( this->new_table_pointer, this->original_table, this->estimated_table_size * sizeof( uintptr_t ) );
}

void vmt_hook::hook_index( size_t fn_index, void* fn_pointer ) {
	this->new_table_pointer [ fn_index ] = reinterpret_cast< uintptr_t >( fn_pointer );
}

void vmt_hook::apply( ) {
	*this->table_pointer = this->new_table_pointer;
}

void vmt_hook::release( ) {
	*this->table_pointer = this->original_table;
}

void* vmt_hook::get_original( size_t fn_index ) {
	return reinterpret_cast< void* >( this->original_table [ fn_index ] );
}