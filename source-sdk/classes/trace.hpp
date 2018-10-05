#pragma once
#include "../math/vector3d.hpp"

enum content_flag {
	contents_empty = 0,
	contents_solid = 0x1,
	contents_window = 0x2,
	contents_aux = 0x4,
	contents_grate = 0x8,
	contents_slime = 0x10,
	contents_water = 0x20,
	contents_blocklos = 0x40,
	contents_opaque = 0x80,
	last_visible_contents = contents_opaque,
	all_visible_contents = ( last_visible_contents | ( last_visible_contents - 1 ) ),
	contents_testfogvolume = 0x100,
	contents_unused = 0x200,
	contents_blocklight = 0x400,
	contents_team1 = 0x800,
	contents_team2 = 0x1000,
	contents_ignore_nodraw_opaque = 0x2000,
	contents_moveable = 0x4000,
	contents_areaportal = 0x8000,
	contents_playerclip = 0x10000,
	contents_monsterclip = 0x20000,
	contents_current_0 = 0x40000,
	contents_current_90 = 0x80000,
	contents_current_180 = 0x100000,
	contents_current_270 = 0x200000,
	contents_current_up = 0x400000,
	contents_current_down = 0x800000,
	contents_origin = 0x1000000,
	contents_monster = 0x2000000,
	contents_debris = 0x4000000,
	contents_detail = 0x8000000,
	contents_translucent = 0x10000000,
	contents_ladder = 0x20000000,
	contents_hitbox = 0x40000000,
};
enum surface_flag {
	surf_light = 0x0001,
	surf_sky2d = 0x0002,
	surf_sky = 0x0004,
	surf_warp = 0x0008,
	surf_trans = 0x0010,
	surf_noportal = 0x0020,
	surf_trigger = 0x0040,
	surf_nodraw = 0x0080,
	surf_hint = 0x0100,
	surf_skip = 0x0200,
	surf_nolight = 0x0400,
	surf_bumplight = 0x0800,
	surf_noshadows = 0x1000,
	surf_nodecals = 0x2000,
	surf_nopaint = surf_nodecals,
	surf_nochop = 0x4000,
	surf_hitbox = 0x8000
};
enum trace_mask {
	mask_all = ( 0xffffffff ),
	mask_solid = ( contents_solid | contents_moveable | contents_window | contents_monster | contents_grate ),
	mask_playersolid = ( contents_solid | contents_moveable | contents_playerclip | contents_window | contents_monster | contents_grate ),
	mask_npcsolid = ( contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster | contents_grate ),
	mask_npcfluid = ( contents_solid | contents_moveable | contents_monsterclip | contents_window | contents_monster ),
	mask_water = ( contents_water | contents_moveable | contents_slime ),
	mask_opaque = ( contents_solid | contents_moveable | contents_opaque ),
	mask_opaque_and_npcs = ( mask_opaque | contents_monster ),
	mask_blocklos = ( contents_solid | contents_moveable | contents_blocklos ),
	mask_blocklos_and_npcs = ( mask_blocklos | contents_monster ),
	mask_visible = ( mask_opaque | contents_ignore_nodraw_opaque ),
	mask_visible_and_npcs = ( mask_opaque_and_npcs | contents_ignore_nodraw_opaque ),
	mask_shot = ( contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_hitbox ),
	mask_shot_brushonly = ( contents_solid | contents_moveable | contents_window | contents_debris ),
	mask_shot_hull = ( contents_solid | contents_moveable | contents_monster | contents_window | contents_debris | contents_grate ),
	mask_shot_portal = ( contents_solid | contents_moveable | contents_window | contents_monster ),
	mask_solid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_grate ),
	mask_playersolid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_playerclip | contents_grate ),
	mask_npcsolid_brushonly = ( contents_solid | contents_moveable | contents_window | contents_monsterclip | contents_grate ),
	mask_npcworldstatic = ( contents_solid | contents_window | contents_monsterclip | contents_grate ),
	mask_npcworldstatic_fluid = ( contents_solid | contents_window | contents_monsterclip ),
	mask_splitareaportal = ( contents_water | contents_slime ),
	mask_current = ( contents_current_0 | contents_current_90 | contents_current_180 | contents_current_270 | contents_current_up | contents_current_down ),
	mask_deadsolid = ( contents_solid | contents_playerclip | contents_window | contents_grate )
};
enum trace_type {
	trace_everything = 0,
	trace_world_only,
	trace_entities_only,
	trace_everything_filter_props
};

class vector_aligned : public vec3_t {
public:
	vector_aligned( ) { }
	vector_aligned( const vec3_t& vec ) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	float w;
};

struct ray_t {
	ray_t( ) { }

	vector_aligned start;
	vector_aligned delta;
	vector_aligned start_offset;
	vector_aligned extents;

	const matrix_t* world_transform_matrix;
	bool is_ray;
	bool is_swept;

	void init( vec3_t start, vec3_t end ) {
		this->delta = vector_aligned( end - start );
		this->is_swept = ( this->delta.length_sqr( ) != 0 );
		this->extents = vec3_t( );
		this->world_transform_matrix = 0;
		this->is_ray = true;
		this->start_offset = vec3_t( );
		this->start = start;
	}
};
struct cplane_t {
	vec3_t normal;
	float dist;
	char type;
	char signbits;
	char pad [ 2 ];
};

class entity_t;
class i_trace_filter {
public:
	virtual bool should_hit( entity_t* entity_handle, int content_mask ) {
		return !( entity_handle == skip );
	}
	virtual trace_type get_trace_type( ) {
		return trace_everything;
	}

	void* skip;
};
class c_trace_filter : public i_trace_filter {
public:
	virtual bool should_hit_entity( entity_t* entity_handle, int content_mask ) {
		return !( entity_handle == skip );
	}
	virtual trace_type get_trace_type( ) const {
		return trace_everything;
	}

	void* skip;
};

class c_base_trace {
public:
	vec3_t start;
	vec3_t end;
	cplane_t plane;

	float fraction;

	int contents;
	unsigned short dispFlags;

	bool allsolid;
	bool startsolid;

	c_base_trace( ) { }
};
struct csurface_t {
	const char* name;
	short props;
	unsigned short flags;
};

class c_game_trace : public c_base_trace {
public:
	bool hit_world( ) const;
	bool hit_non_world_entity( ) const;
	int get_entity_index( ) const;
	bool did_hit( ) const;
	bool is_visible( ) const;

public:

	float fraction_left_solid;
	csurface_t surface;
	int hit_group;
	short physics_bone;
	unsigned short world_surface_index;
	entity_t* entity;
	int hitbox;

	c_game_trace( ) { }

private:
	c_game_trace( const c_game_trace& vOther );
};
typedef c_game_trace trace_t;