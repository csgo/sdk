#include "../dependencies/common_includes.hpp"

unsigned long __stdcall initial_thread( void* reserved ) {

	AllocConsole( );
	SetConsoleTitleW( L"Counter-Strike: Global Offensive" );
	freopen_s( reinterpret_cast< FILE** >stdin, "CONIN$", "r", stdin );
	freopen_s( reinterpret_cast< FILE** >stdout, "CONOUT$", "w", stdout );

	interfaces::initialize( );

	g_netvar_mgr.initialize( interfaces::client->get_client_classes( ) );

	hooks::initialize( );

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 50 ) );

	hooks::shutdown( );
	std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	FreeLibraryAndExitThread( reinterpret_cast< HMODULE >( reserved ), 0 );
	return 0ul;
}

bool __stdcall DllMain( void* instance, unsigned long reason_to_call, void* reserved ) {
	if ( reason_to_call == DLL_PROCESS_ATTACH ) {
		CreateThread( 0, 0, initial_thread, instance, 0, 0 );
	}

	return true;
}
