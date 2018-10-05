#pragma once
#include <cstdint>
#include "../../source-sdk/classes/client_class.hpp"

class prop_hook {
private:
	recv_var_proxy_fn original_fn;
	recv_prop* prop;

public:
	void setup( recv_prop* prop );
	void swap( recv_var_proxy_fn new_proxy );
	void release( );
	recv_var_proxy_fn get_original( );
};

class vmt_hook {
private:
	uintptr_t * * table_pointer;
	uintptr_t* original_table;
	uintptr_t* new_table_pointer;
	size_t estimated_table_size;

public:
	void setup( void* class_pointer );

	void hook_index( size_t fn_index, void* fn_pointer );
	void apply( );
	void release( );

	void* get_original( size_t fn_index );
};