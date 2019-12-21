#include "netvars.hpp"
#include <sstream>
#include <iomanip>

netvar_manager g_netvar_mgr;

void netvar_manager::dump_table_recursive( recv_table* table ) {
	for ( auto i = 0; i < table->props_count; ++i ) {
		auto prop = &table->props [ i ];

		if ( !prop || isdigit( prop->prop_name [ 0 ] ) )
			continue;
		if ( strcmp( prop->prop_name, "baseclass" ) == 0 )
			continue;

		if ( prop->prop_type == send_prop_type::_data_table && prop->data_table != nullptr && prop->data_table->table_name [ 0 ] == 'D' ) {
			dump_table_recursive( prop->data_table );
		}

		std::string hash_string = table->table_name;
		hash_string.append( "->" );
		hash_string.append( prop->prop_name );

		netvars_map [ fnv_hash( hash_string.c_str( ) ) ] = prop;
	}
}

void netvar_manager::dump_table_to_file_recursive( recv_table* table, std::ofstream& file ) {
	for ( auto i = 0; i < table->props_count; ++i ) {
		auto prop = &table->props [ i ];

		if ( !prop || isdigit( prop->prop_name [ 0 ] ) )
			continue;
		if ( strcmp( prop->prop_name, "baseclass" ) == 0 )
			continue;

		if ( prop->prop_type == send_prop_type::_data_table && prop->data_table != nullptr && prop->data_table->table_name [ 0 ] == 'D' ) {
			dump_table_to_file_recursive( prop->data_table, file );
		}

		std::string hash_string = table->table_name;
		hash_string.append( " -> " );
		hash_string.append( prop->prop_name );

		auto hash = fnv_hash( hash_string.c_str( ) );

		hash_string.append( " (" );
		hash_string.append( std::to_string( unsigned int( hash ) ) );
		hash_string.append( ") [" );
		std::stringstream stream;
		stream << "0x"
			<< std::setfill( '0' ) << std::setw( sizeof( int ) * 2 )
			<< std::hex << prop->offset;
		hash_string.append( stream.str( ) );
		hash_string.append( "]" );

		file << hash_string << std::endl;
	}
}

void netvar_manager::initialize( client_class* client_data ) {
	for ( auto data = client_data; data; data = data->next_ptr ) {
		if ( data->recvtable_ptr ) {
			dump_table_recursive( data->recvtable_ptr );
		}
	}
}

void netvar_manager::dump_netvars( client_class* client_data ) {
	std::ofstream output( "netvars_dump.txt" );

	for ( auto data = client_data; data; data = data->next_ptr ) {
		if ( data->recvtable_ptr ) {
			dump_table_to_file_recursive( data->recvtable_ptr, output );
		}
	}
}

unsigned short netvar_manager::get_offset( unsigned int hash ) {
	if ( !netvars_map [ hash ] ) return 0;
	return netvars_map [ hash ]->offset;
}

recv_prop* netvar_manager::get_prop( unsigned int hash ) {
	return netvars_map [ hash ];
}