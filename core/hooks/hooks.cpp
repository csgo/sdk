#pragma once

#include "../../dependencies/common_includes.hpp"
#include <algorithm>

bool renderer_initialized = false;

std::unique_ptr<vmt_hook> hooks::client_hook;
std::unique_ptr<vmt_hook> hooks::clientmode_hook;
std::unique_ptr<vmt_hook> hooks::panel_hook;
std::unique_ptr<vmt_hook> hooks::renderview_hook;
WNDPROC hooks::wndproc_original = NULL;

void hooks::initialize( ) {
	client_hook = std::make_unique<vmt_hook>( );
	clientmode_hook = std::make_unique<vmt_hook>( );
	panel_hook = std::make_unique<vmt_hook>( );
	renderview_hook = std::make_unique<vmt_hook>( );

	client_hook->setup( interfaces::client );
	client_hook->hook_index( 37, reinterpret_cast< void* >( frame_stage_notify ) );

	clientmode_hook->setup( interfaces::clientmode );
	clientmode_hook->hook_index( 24, reinterpret_cast< void* >( create_move ) );

	panel_hook->setup( interfaces::panel );
	panel_hook->hook_index( 41, reinterpret_cast< void* >( paint_traverse ) );

	renderview_hook->setup( interfaces::render_view );
	renderview_hook->hook_index( 9, reinterpret_cast< void* >( scene_end ) );

	wndproc_original = ( WNDPROC ) SetWindowLongPtrA( FindWindow( "Valve001", NULL ), GWL_WNDPROC, ( LONG ) wndproc );

	interfaces::console->get_convar( "mat_queue_mode" )->set_value( 0 );
	interfaces::console->get_convar( "viewmodel_fov" )->callbacks.SetSize( 0 );
	interfaces::console->get_convar( "mat_postprocess_enable" )->set_value( 0 );
	interfaces::console->get_convar( "crosshair" )->set_value( 1 );
}
void hooks::shutdown( ) {
	clientmode_hook->release( );
	client_hook->release( );
	panel_hook->release( );
	renderview_hook->release( );

	SetWindowLongPtrA( FindWindow( "Valve001", NULL ), GWL_WNDPROC, ( LONG ) wndproc_original );
}
bool __stdcall hooks::create_move( float frame_time, c_usercmd* user_cmd ) {
	reinterpret_cast< create_move_fn >( clientmode_hook->get_original( 24 ) )( interfaces::clientmode, frame_time, user_cmd );
	return false;
}

void __stdcall hooks::frame_stage_notify( int frame_stage ) {
	reinterpret_cast< frame_stage_notify_fn >( client_hook->get_original( 37 ) )( interfaces::client, frame_stage );
}
void __stdcall hooks::paint_traverse( unsigned int panel, bool force_repaint, bool allow_force ) {
	std::string panel_name = interfaces::panel->get_panel_name( panel );

	static unsigned int focus_overlay_panel = 0;
	static bool once = false;

	if ( !once ) {
		PCHAR panel_char = ( PCHAR ) interfaces::panel->get_panel_name( panel );
		if ( strstr( panel_char, "FocusOverlayPanel" ) ) {
			focus_overlay_panel = panel;
			once = true;
		}
	}
	else if ( focus_overlay_panel == panel ) {
		render::get( ).draw_filled_rect( 50, 50, 50, 10, color( 255, 255, 255, 255 ) ); // polish flag
		render::get( ).draw_filled_rect( 50, 60, 50, 10, color( 255, 0, 0, 255 ) ); // poland owns me and all
	}


	reinterpret_cast< paint_traverse_fn >( panel_hook->get_original( 41 ) )( interfaces::panel, panel, force_repaint, allow_force );
}
void __stdcall hooks::scene_end( ) {
	reinterpret_cast< scene_end_fn >( renderview_hook->get_original( 9 ) )( interfaces::render_view );
}
LRESULT __stdcall hooks::wndproc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam ) {
	return CallWindowProcA( wndproc_original, hwnd, message, wparam, lparam );
}