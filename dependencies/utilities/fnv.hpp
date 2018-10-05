#pragma once
#include <string>

class fnv_hash {
private:
	struct wrapper {
		wrapper( const char* str ) : str( str ) { }
		const char* str;
	};

	static const unsigned int prime = 16777619u;
	static const unsigned int basis = 2166136261u;

	template <unsigned int n>
	static constexpr unsigned int fnv_hash_const( const char( &str ) [ n ], unsigned int i = n ) {
		return i == 1 ? ( basis ^ str [ 0 ] ) * prime : ( fnv_hash_const( str, i - 1 ) ^ str [ i - 1 ] ) * prime;
	}
	static unsigned int hash( const char* str ) {
		const size_t length = strlen( str ) + 1;
		unsigned int hash = basis;

		for ( size_t i = 0; i < length; ++i ) {
			hash ^= *str++;
			hash *= prime;
		}

		return hash;
	}

	unsigned int hash_value;
public:
	fnv_hash( wrapper wrap ) : hash_value( hash( wrap.str ) ) { }

	template <unsigned int n>
	constexpr fnv_hash( const char( &str ) [ n ] ) : hash_value( fnv_hash_const( str ) ) { }

	constexpr operator unsigned int( ) const {
		return this->hash_value;
	}
};