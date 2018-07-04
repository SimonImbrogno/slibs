#include "stypes.h"

#include <stdio.h>

struct Xoroshiro
{
	u64 state[2];
};

static inline u64
rotl(u64 x, u32 k) {
	return (x << k) | (x >> (64 - k));
}

void
seed(Xoroshiro &gen, s64 seed) 
{
	//Cheeky 64b LCG to seed (Newlib)
	u64 m = 6364136223846793005;
	gen.state[0] = (m * seed) + 1;
	gen.state[1] = (m * gen.state[0]) + 1;
} 

static inline u64 
extract_u64(Xoroshiro &gen) {
  u64 a = 24;
  u64 b = 16;
  u64 c = 37;

	u64 s0 = gen.state[0];
	u64 s1 = gen.state[1];

	s1 ^= s0;
	gen.state[0] = rotl(s0, a) ^ s1 ^ (s1 << b);
	gen.state[1] = rotl(s1, c);

	return s0 + s1;
}

inline u64 rand_u64(Xoroshiro &gen) { return       extract_u64(gen);        }
inline u32 rand_u32(Xoroshiro &gen) { return (u32)(extract_u64(gen) >> 32); }
inline u16 rand_u16(Xoroshiro &gen) { return (u16)(extract_u64(gen) >> 48); }
inline u8  rand_u8 (Xoroshiro &gen) { return (u8) (extract_u64(gen) >> 56); }

inline s64 rand_s64(Xoroshiro &gen) { return (s64) extract_u64(gen);        }
inline s32 rand_s32(Xoroshiro &gen) { return (s32)(extract_u64(gen) >> 32); }
inline s16 rand_s16(Xoroshiro &gen) { return (s16)(extract_u64(gen) >> 48); }
inline s8  rand_s8 (Xoroshiro &gen) { return (s8) (extract_u64(gen) >> 56); }

//In range [0, 1)
inline f64 rand_f64 			(Xoroshiro &gen) { return (f64)rand_u32(gen) / 4294967296.0;          }
//In range [0, 1]
inline f64 rand_f64_closed(Xoroshiro &gen) { return (f64)rand_u32(gen) / 4294967295.0;          }
//In range (0, 1)
inline f64 rand_f64_open 	(Xoroshiro &gen) { return ((f64)(rand_u32(gen)) + .5) / 4294967296.0; }
//In range [0, 1), high resolution
inline f64 rand_f64_hr 		(Xoroshiro &gen)
{
  return ((f64)(rand_u32(gen) >> 5) * 67108864.0 + 
          (f64)(rand_u32(gen) >> 6)) * (1.0 / 9007199254740992.0);
}

inline u64 rand_b32(Xoroshiro &gen) { return (extract_u64(gen) > 0); }
