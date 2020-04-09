#include <hashmap_algos.h>
#include <bstrlib.h>


// Setting taken from
// http:www.isthe.com/chongo/tech/comp/fnv/index.html#FNV-param


// FNV1A

const uint32_t FNV_PRIME		= 16777619;
const uint32_t FNV_OFFSET_BASIS	= 2166136261;

uint32_t Hashmap_fnv1a_hash(void *data)
{
	bstring s					= (bstring)data;
	uint32_t hash				= FNV_OFFSET_BASIS;
	int i						= 0;

	for (i = 0; i < blength(s); i++) {
		hash	^= bchare(s, i, 0);
		hash	*= FNV_PRIME;
	}

	return hash;
}


// ADLER32

const int MOD_ADLER				= 65521;

uint32_t Hashmap_adler32_hash(void *data)
{
	bstring s					= (bstring)data;
	uint32_t a	= 1, b	= 0;
	int i						= 0;
	
	for (i = 0; i < blength(s); i++) {
		a		= (a + bchare(s, i, 0)) % MOD_ADLER;
		b		= (b + a) % MOD_ADLER;
	}

	return (b << 16) | a;
}


// DJB

uint32_t Hashmap_djb_hash(void *data)
{
	bstring s					= (bstring)data;
	uint32_t hash				= 5381;
	int i						= 0;

	for (i = 0; i < blength(s); i++) {
		// hash * 33 + char
		hash	= ((hash << 5) + hash) + bchare(s, i, 0);
	}

	return hash;
}


// Jenkins 

uint32_t Hashmap_Jenkins_hash(void *data)
{
	bstring s				= (bstring)data;
	uint32_t hash			= 0;
	uint32_t i				= 0;

	/* it is generally better to use ++i for "for loops"
	 * compilers usually compile i++ and ++i as ++i but some don't
	 * the difference is that i++ will increment the value of i but return the original value that i held before being incremented.
	 */
	for (hash = i = 0; i < blength(s); ++i)
	{
		hash += bchare(s, i, 0);
		hash += (hash << 10);
		hash ^= (hash >> 6);
	}

	hash += (hash << 3);
	hash ^= (hash << 11);
	hash += (hash << 15);

	return hash;
}

