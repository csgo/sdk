#pragma once
#include <limits>

template <typename T>
T clip_number( const T& n, const T& lower, const T& upper ) {
	if ( n < lower ) return lower;
	if ( n > upper ) return upper;
	return n;
}

class vec3_t {
public:
	vec3_t( );
	vec3_t( float, float, float );
	~vec3_t( );

	float x, y, z;

	vec3_t& operator+=( const vec3_t& v ) {
		x += v.x; y += v.y; z += v.z; return *this;
	}
	vec3_t& operator-=( const vec3_t& v ) {
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}
	vec3_t& operator*=( float v ) {
		x *= v; y *= v; z *= v; return *this;
	}
	vec3_t operator+( const vec3_t& v ) {
		return vec3_t { x + v.x, y + v.y, z + v.z };
	}
	vec3_t operator-( const vec3_t& v ) {
		return vec3_t { x - v.x, y - v.y, z - v.z };
	}
	vec3_t operator*( float v ) const {
		return vec3_t { x * v, y * v, z * v };
	}

	float& operator[]( int i ) {
		return ( ( float* ) this ) [ i ];
	}
	float operator[]( int i ) const {
		return ( ( float* ) this ) [ i ];
	}

	void clamp( );
	vec3_t normalized( );
	void normalize( );
	float length( );
	float length_sqr( );
	float dot( const vec3_t other );
};
typedef float matrix_t [ 3 ] [ 4 ];