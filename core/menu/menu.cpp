#include "menu.hpp"

c_menu g_menu;

void c_menu::render( ) {
	static bool checkbox;
	static float sliderf;
	static int slideri, dropdown;

	zgui::poll_input( "Counter-Strike: Global Offensive" );

	if ( zgui::begin_window( "sdk for counter-strike: global offensive", { 500, 350 }, render::main_font ) ) {
		zgui::begin_groupbox( "Example groupbox", { 468, 311 } );
		{
			zgui::checkbox( "Example checkbox", checkbox );
			zgui::slider_float( "Example slider (float)", 0.0f, 100.0f, sliderf );
			zgui::slider_int( "Example slider (int)", 0, 100, slideri );
			zgui::combobox( "Example dropdown", { "aaaa", "bbbb", "cccc", "dddd" }, dropdown );
		}
		zgui::end_groupbox( );

		zgui::end_window( );
	}
}