#pragma once
#include <cstdint>
#include "../../source-sdk/math/vector3d.hpp"

#define M_PI 3.14159265358979323846

namespace utilities {
	namespace math {
		template <typename t> t clamp_value( t value, t min, t max ) {
			if ( value > max ) {
				return max;
			}
			if ( value < min ) {
				return min;
			}
			return value;
		}
	}
	namespace game {
		void* capture_interface( const char* mod, const char* iface );
	}
	std::uint8_t* pattern_scan( void* module, const char* signature );
}