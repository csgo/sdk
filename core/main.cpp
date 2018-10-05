#include "../dependencies/common_includes.hpp"

unsigned long __stdcall initial_thread( void* reserved ) {
	AllocConsole( );
	freopen_s( ( FILE** ) stdin, "CONIN$", "r", stdin );
	freopen_s( ( FILE** ) stdout, "CONOUT$", "w", stdout );

	interfaces::initialize( );
	netvar_manager::get( ).initialize( interfaces::client->get_client_classes( ) );
	netvar_manager::get( ).dump_netvars( interfaces::client->get_client_classes( ) );
	hooks::initialize( );

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );

	hooks::shutdown( );
	std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	fclose( ( FILE* ) stdin );
	fclose( ( FILE* ) stdout );
	FreeConsole( );

	FreeLibraryAndExitThread( reinterpret_cast< HMODULE >( reserved ), 0 );
	return 0ul;
}

bool __stdcall DllMain( void* instance, unsigned long reason_to_call, void* reserved ) {
	if ( reason_to_call == DLL_PROCESS_ATTACH ) {
		CreateThread( 0, 0, initial_thread, instance, 0, 0 );
	}

	return true;
}