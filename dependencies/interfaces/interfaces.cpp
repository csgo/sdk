#include "interfaces.hpp"
#include "../common_includes.hpp"

i_base_client_dll* interfaces::client = nullptr;
i_input* interfaces::input = nullptr;
i_client_entity_list* interfaces::entity_list = nullptr;
iv_engine_client* interfaces::engine = nullptr;
i_client_mode* interfaces::clientmode = nullptr;
i_client_state* interfaces::clientstate = nullptr;
i_panel* interfaces::panel = nullptr;
i_surface* interfaces::surface = nullptr;
c_global_vars_base* interfaces::globals = nullptr;
i_material_system* interfaces::material_system = nullptr;
iv_model_info* interfaces::model_info = nullptr;
iv_model_render* interfaces::model_render = nullptr;
void* interfaces::render_view = nullptr;
iv_effects* interfaces::effects = nullptr;
i_console* interfaces::console = nullptr;
i_localize* interfaces::localize = nullptr;
i_game_event_manager* interfaces::event_manager = nullptr;
iv_debug_overlay* interfaces::debug_overlay = nullptr;
IDirect3DDevice9* interfaces::directx = nullptr;

void interfaces::initialize( ) {
	client = reinterpret_cast< i_base_client_dll* >( utilities::game::capture_interface( "client_panorama.dll", "VClient018" ) );
	entity_list = reinterpret_cast< i_client_entity_list* >( utilities::game::capture_interface( "client_panorama.dll", "VClientEntityList003" ) );
	engine = reinterpret_cast< iv_engine_client* >( utilities::game::capture_interface( "engine.dll", "VEngineClient014" ) );
	panel = reinterpret_cast< i_panel* >( utilities::game::capture_interface( "vgui2.dll", "VGUI_Panel009" ) );
	surface = reinterpret_cast< i_surface* >( utilities::game::capture_interface( "vguimatsurface.dll", "VGUI_Surface031" ) );
	material_system = reinterpret_cast< i_material_system* >( utilities::game::capture_interface( "materialsystem.dll", "VMaterialSystem080" ) );
	model_info = reinterpret_cast< iv_model_info* >( utilities::game::capture_interface( "engine.dll", "VModelInfoClient004" ) );
	model_render = reinterpret_cast< iv_model_render* >( utilities::game::capture_interface( "engine.dll", "VEngineModel016" ) );
	render_view = reinterpret_cast< void* >( utilities::game::capture_interface( "engine.dll", "VEngineRenderView014" ) );
	console = reinterpret_cast< i_console* >( utilities::game::capture_interface( "vstdlib.dll", "VEngineCvar007" ) );
	localize = reinterpret_cast< i_localize* >( utilities::game::capture_interface( "localize.dll", "Localize_001" ) );
	event_manager = reinterpret_cast< i_game_event_manager* >( utilities::game::capture_interface( "engine.dll", "GAMEEVENTSMANAGER002" ) );
	debug_overlay = reinterpret_cast< iv_debug_overlay* >( utilities::game::capture_interface( "engine.dll", "VDebugOverlay004" ) );
	effects = reinterpret_cast< iv_effects* >( utilities::game::capture_interface( "engine.dll", "VEngineEffects001" ) );

	clientmode = **reinterpret_cast< i_client_mode*** >( ( *reinterpret_cast< uintptr_t** >( client ) ) [ 10 ] + 5 );
	clientstate = **( i_client_state*** ) ( utilities::pattern_scan( GetModuleHandleA( "engine.dll" ), "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) + 1 );
	globals = **reinterpret_cast< c_global_vars_base*** >( ( *reinterpret_cast< uintptr_t** >( client ) [ 0 ] + 27 ) );
	directx = **( IDirect3DDevice9*** ) ( utilities::pattern_scan( GetModuleHandleA( "shaderapidx9.dll" ), "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 1 );
	input = *( i_input** ) ( utilities::pattern_scan( GetModuleHandleA( "client_panorama.dll" ), "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) + 1 );
}