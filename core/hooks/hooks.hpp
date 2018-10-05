#pragma once

namespace hooks {
	extern std::unique_ptr<vmt_hook> client_hook;
	extern std::unique_ptr<vmt_hook> clientmode_hook;
	extern std::unique_ptr<vmt_hook> panel_hook;
	extern std::unique_ptr<vmt_hook> renderview_hook;
	extern WNDPROC wndproc_original;

	void initialize( );
	void shutdown( );

	using present_fn = long( __stdcall* )( IDirect3DDevice9*, RECT*, RECT*, HWND, RGNDATA* );
	using reset_fn = long( __stdcall* )( IDirect3DDevice9*, D3DPRESENT_PARAMETERS* );
	using create_move_fn = bool( __thiscall* )( i_client_mode*, float, c_usercmd* );
	using frame_stage_notify_fn = void( __thiscall* )( i_base_client_dll*, int );
	using paint_traverse_fn = void( __thiscall* )( i_panel*, unsigned int, bool, bool );
	using scene_end_fn = void( __thiscall* )( void* );

	long __stdcall present( IDirect3DDevice9* device, RECT* source_rect, RECT* dest_rect, HWND dest_window_override, RGNDATA* dirty_region );
	long __stdcall reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* present_parameters );
	bool __stdcall create_move( float frame_time, c_usercmd* user_cmd );
	void __stdcall frame_stage_notify( int frame_stage );
	void __stdcall paint_traverse( unsigned int panel, bool force_repaint, bool allow_force );
	void __stdcall scene_end( );
	LRESULT __stdcall wndproc( HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam );
}