#pragma once
#include "collideable.hpp"

enum entity_flags {
	fl_onground = ( 1 << 0 ),
	fl_ducking = ( 1 << 1 ),
	fl_waterjump = ( 1 << 2 ),
	fl_ontrain = ( 1 << 3 ),
	fl_inrain = ( 1 << 4 ),
	fl_frozen = ( 1 << 5 ),
	fl_atcontrols = ( 1 << 6 ),
	fl_client = ( 1 << 7 ),
	fl_fakeclient = ( 1 << 8 ),
	fl_inwater = ( 1 << 9 ),
	fl_fly = ( 1 << 10 ),
	fl_swim = ( 1 << 11 ),
	fl_conveyor = ( 1 << 12 ),
	fl_npc = ( 1 << 13 ),
	fl_godmode = ( 1 << 14 ),
	fl_notarget = ( 1 << 15 ),
	fl_aimtarget = ( 1 << 16 ),
	fl_partialground = ( 1 << 17 ),
	fl_staticprop = ( 1 << 18 ),
	fl_graphed = ( 1 << 19 ),
	fl_grenade = ( 1 << 20 ),
	fl_stepmovement = ( 1 << 21 ),
	fl_donttouch = ( 1 << 22 ),
	fl_basevelocity = ( 1 << 23 ),
	fl_worldbrush = ( 1 << 24 ),
	fl_object = ( 1 << 25 ),
	fl_killme = ( 1 << 26 ),
	fl_onfire = ( 1 << 27 ),
	fl_dissolving = ( 1 << 28 ),
	fl_transragdoll = ( 1 << 29 ),
	fl_unblockable_by_player = ( 1 << 30 )
};

enum item_definition_indexes {
	item_none = 0,
	weapon_deagle = 1,
	weapon_duals = 2,
	weapon_five7 = 3,
	weapon_glock = 4,
	weapon_ak47 = 7,
	weapon_aug = 8,
	weapon_awp = 9,
	weapon_famas = 10,
	weapon_g3sg1 = 11,
	weapon_galil = 13,
	weapon_m249 = 14,
	weapon_m4a1 = 16,
	weapon_mac10 = 17,
	weapon_p90 = 19,
	weapon_ump45 = 24,
	weapon_xm1014 = 25,
	weapon_bizon = 26,
	weapon_mag7 = 27,
	weapon_negev = 28,
	weapon_sawedoff = 29,
	weapon_tec9 = 30,
	weapon_taser = 31,
	weapon_p2000 = 32,
	weapon_mp7 = 33,
	weapon_mp9 = 34,
	weapon_nova = 35,
	weapon_p250 = 36,
	weapon_scar20 = 38,
	weapon_sg553 = 39,
	weapon_scout = 40,
	weapon_knife_t = 42,
	weapon_flash = 43,
	weapon_he = 44,
	weapon_smoke = 45,
	weapon_molotov = 46,
	weapon_decoy = 47,
	weapon_inc = 48,
	weapon_c4 = 49,
	weapon_knife_ct = 59,
	weapon_m4a1s = 60,
	weapon_usps = 61,
	weapon_cz75 = 63,
	weapon_revolver = 64,
	weapon_knife_bayonet = 500,
	weapon_knife_flip = 505,
	weapon_knife_gut = 506,
	weapon_knife_karambit = 507,
	weapon_knife_m9bayonet = 508,
	weapon_knife_huntsman = 509,
	weapon_knife_falchion = 512,
	weapon_knife_bowie = 514,
	weapon_knife_butterfly = 515,
	weapon_knife_dagger = 516,
	weapon_max
};

class entity_t {
public:
	void* animating( ) {
		return reinterpret_cast< void* >( uintptr_t( this ) + 0x4 );
	}

	void* networkable( ) {
		return reinterpret_cast< void* >( uintptr_t( this ) + 0x8 );
	}

	collideable_t* collideable( ) {
		using original_fn = collideable_t * ( __thiscall* )( void* );
		return ( *( original_fn** ) this )[ 3 ]( this );
	}

	client_class* clientclass( ) {
		using original_fn = client_class * ( __thiscall* )( void* );
		return ( *( original_fn** ) networkable( ) )[ 2 ]( networkable( ) );
	}

	bool is_player( ) {
		using original_fn = bool( __thiscall* )( entity_t* );
		return ( *( original_fn** ) this )[ 152 ]( this );
	}

	bool is_weapon( ) {
		using original_fn = bool( __thiscall* )( entity_t* );
		return ( *( original_fn** ) this )[ 160 ]( this );
	}

	bool setup_bones( matrix_t* out, int max_bones, int mask, float time ) {
		using original_fn = bool( __thiscall* )( void*, matrix_t*, int, int, float );
		return ( *( original_fn** ) animating( ) )[ 13 ]( animating( ), out, max_bones, mask, time );
	}

	model_t* model( ) {
		using original_fn = model_t * ( __thiscall* )( void* );
		return ( *( original_fn** ) animating( ) )[ 8 ]( animating( ) );
	}

	void update( ) {
		using original_fn = void( __thiscall* )( entity_t* );
		( *( original_fn** ) this )[ 218 ]( this );
	}

	int draw_model( int flags, uint8_t alpha ) {
		using original_fn = int( __thiscall* )( void*, int, uint8_t );
		return ( *( original_fn** ) animating( ) )[ 9 ]( animating( ), flags, alpha );
	}

	void set_angles( vec3_t angles ) {
		using original_fn = void( __thiscall* )( void*, const vec3_t& );
		static original_fn set_angles_fn = ( original_fn ) ( ( DWORD ) utilities::pattern_scan( GetModuleHandleA( "client_panorama.dll" ), "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1" ) );
		set_angles_fn( this, angles );
	}

	void set_position( vec3_t position ) {
		using original_fn = void( __thiscall* )( void*, const vec3_t& );
		static original_fn set_position_fn = ( original_fn ) ( ( DWORD ) utilities::pattern_scan( GetModuleHandleA( "client_panorama.dll" ), "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" ) );
		set_position_fn( this, position );
	}

	netvar_fn( int, flags, "DT_BasePlayer->m_fFlags" );
	netvar_fn( unsigned long, owner_handle, "DT_BaseEntity->m_hOwnerEntity" );
	offset_fn( bool, dormant, 0xE9 );
	netvar_fn( float, simulation_time, "DT_BaseEntity->m_flSimulationTime" );
	offset_fn( vec3_t, origin, 0x134 );
	offset_fn( vec3_t, view_offset, 0x104 );
	netvar_fn( int, team, "DT_BaseEntity->m_iTeamNum" );
	netvar_fn( bool, spotted, "DT_BaseEntity->m_bSpotted" );
};

class viewmodel_t : public entity_t {
public:
	netvar_ptr_fn( int, model_index, "DT_BaseViewModel->m_nModelIndex" );
	netvar_ptr_fn( int, viewmodel_index, "DT_BaseViewModel->m_nViewModelIndex" );
};

class weapon_t : public entity_t {
public:
	netvar_fn( float, next_primary_attack, "DT_BaseCombatWeapon->m_flNextPrimaryAttack" );
	netvar_fn( float, next_secondary_attack, "DT_BaseCombatWeapon->m_flNextSecondaryAttack" );
	netvar_fn( int, clip1_count, "DT_BaseCombatWeapon->m_iClip1" );
	netvar_fn( int, clip2_count, "DT_BaseCombatWeapon->m_iClip2" );
	netvar_fn( float, recoil_index, "DT_WeaponCSBase->m_flRecoilIndex" );

	float get_innacuracy( ) {
		using original_fn = float( __thiscall* )( void* );
		return ( *( original_fn** ) this )[ 479 ]( this );
	}

	float get_spread( ) {
		using original_fn = float( __thiscall* )( void* );
		return ( *( original_fn** ) this )[ 449 ]( this );
	}

	void update_accuracy_penalty( ) {
		using original_fn = void( __thiscall* )( void* );
		( *( original_fn** ) this )[ 480 ]( this );
	}

	weapon_info_t* get_weapon_data( ) {
		using original_fn = weapon_info_t * ( __thiscall* )( void* );
		static original_fn return_func = ( original_fn ) ( ( DWORD ) utilities::pattern_scan( GetModuleHandleA( "client_panorama.dll" ), "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B" ) );

		return return_func( this );

	}

	bool is_knife( ) {
		return clientclass( )->class_id == cknife || clientclass( )->class_id == cknifegg;
	}
};

class econ_view_item_t {
public:
	netvar_offset_fn( bool, is_initialized, "DT_ScriptCreatedItem->m_bInitialized", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( short, item_definition_index, "DT_ScriptCreatedItem->m_iItemDefinitionIndex", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, entity_level, "DT_ScriptCreatedItem->m_iEntityLevel", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, account_id, "DT_ScriptCreatedItem->m_iAccountID", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, item_id_low, "DT_ScriptCreatedItem->m_iItemIDLow", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, item_id_high, "DT_ScriptCreatedItem->m_iItemIDHigh", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
	netvar_offset_fn( int, entity_quality, "DT_ScriptCreatedItem->m_iEntityQuality", g_netvar_mgr.get_offset( fnv_hash( "DT_AttributeContainer->m_Item" ) ) + g_netvar_mgr.get_offset( fnv_hash( "DT_BaseAttributableItem->m_AttributeManager" ) ) );
};

class attributable_item_t : public entity_t {
public:
	netvar_fn( unsigned long, original_owner_xuid, "DT_BaseAttributableItem->m_OriginalOwnerXuidLow" );
	netvar_fn( int, original_owner_xuid_low, "DT_BaseAttributableItem->m_OriginalOwnerXuidLow" );
	netvar_fn( int, original_owner_xuid_high, "DT_BaseAttributableItem->m_OriginalOwnerXuidHigh" );
	netvar_fn( int, fallback_stattrak, "DT_BaseAttributableItem->m_nFallbackStatTrak" );
	netvar_fn( int, fallback_paint_kit, "DT_BaseAttributableItem->m_nFallbackPaintKit" );
	netvar_fn( int, fallback_seed, "DT_BaseAttributableItem->m_nFallbackSeed" );
	netvar_fn( float, fallback_wear, "DT_BaseAttributableItem->m_flFallbackWear" );
	netvar_fn( unsigned long, world_model_handle, "DT_BaseCombatWeapon->m_hWeaponWorldModel" );

	econ_view_item_t& item( ) {
		return *( econ_view_item_t* ) this;
	}
};

class player_t : public entity_t {
public:
	netvar_fn( bool, has_defuser, "DT_CSPlayer->m_bHasDefuser" );
	netvar_fn( bool, has_gun_game_immunity, "DT_CSPlayer->m_bGunGameImmunity" );
	netvar_fn( int, shots_fired, "DT_CSPlayer->m_iShotsFired" );
	netvar_fn( vec3_t, eye_angles, "DT_CSPlayer->m_angEyeAngles[0]" );
	netvar_fn( int, armor, "DT_CSPlayer->m_ArmorValue" );
	netvar_fn( bool, has_helmet, "DT_CSPlayer->m_bHasHelmet" );
	netvar_fn( bool, is_scoped, "DT_CSPlayer->m_bIsScoped" );;
	netvar_fn( float, lower_body_yaw, "DT_CSPlayer->m_flLowerBodyYawTarget" );
	netvar_fn( float, flash_duration, "DT_CSPlayer->m_flFlashDuration" );
	netvar_fn( int, health, "DT_BasePlayer->m_iHealth" );
	netvar_fn( int, life_state, "DT_BasePlayer->m_lifeState" );
	netvar_fn( int, flags, "DT_BasePlayer->m_fFlags" );
	netvar_fn( int, tick_base, "DT_BasePlayer->m_nTickBase" );
	netvar_fn( vec3_t, punch_angle, "DT_BasePlayer->m_viewPunchAngle" );
	netvar_fn( vec3_t, aim_punch_angle, "DT_BasePlayer->m_aimPunchAngle" );
	netvar_fn( vec3_t, velocity, "DT_BasePlayer->m_vecVelocity[0]" );
	netvar_fn( float, max_speed, "DT_BasePlayer->m_flMaxspeed" );
	netvar_fn( unsigned long, observer_target, "DT_BasePlayer->m_hObserverTarget" );
	netvar_fn( unsigned long, active_weapon_handle, "DT_BaseCombatCharacter->m_hActiveWeapon" );

	weapon_t* active_weapon( void ) {
		uintptr_t handle = active_weapon_handle( );
		return ( weapon_t* ) interfaces::entity_list->get_client_entity( handle );
	}

	int* weapons( ) {
		return ( int* ) ( uintptr_t( this ) + 0x2DE8 );
	}
};