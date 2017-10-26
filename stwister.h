#ifndef STWISTER_H
#define STWISTER_H


#include "stypes.h"


#define SLIBSMT__DEFAULT_SEED 5489
#define SLIBSMT__N 624
#define SLIBSMT__M 397
#define SLIBSMT__A 0x9908B0DFUL
#define SLIBSMT__F 1812433253UL
#define SLIBSMT__U 11
#define SLIBSMT__S 7
#define SLIBSMT__B 0x9D2C5680UL
#define SLIBSMT__T 15
#define SLIBSMT__C 0xEFC60000UL
#define SLIBSMT__L 18


struct MersenneTwister
{
    u32 state_vector[SLIBSMT__N];
    u16 index;
};

//External
inline void init_mersenne_twister  (MersenneTwister *mt, u32 seed = SLIBSMT__DEFAULT_SEED);
inline u32  rand_u32               (MersenneTwister *mt); //In range [0, 4294967295]
inline f64  rand_f64               (MersenneTwister *mt); //In range [0, 1)
inline f64  rand_f64_closed        (MersenneTwister *mt); //In range [0, 1]
inline f64  rand_f64_open          (MersenneTwister *mt); //In range (0, 1)
inline f64  rand_f64_hr            (MersenneTwister *mt); //In range [0, 1)

//Internal
inline void twist                  (MersenneTwister *mt);
inline u32  extract_u32            (MersenneTwister *mt);


inline void 
twist(MersenneTwister *mt)
{
    u32 *state = mt->state_vector;
    u32 x, xA;

    for(s32 i = 0; i < SLIBSMT__N; i++)
    {
        x = (state[i] & 0x80000000UL) + (state[(i + 1) % SLIBSMT__N] & 0x7FFFFFFFUL);
        xA = x >> 1; 
        if(x & 0x1UL) { xA ^= SLIBSMT__A; }
        state[i] = state[(i + SLIBSMT__M) % SLIBSMT__N] ^ xA;
    }

    mt->index = 0; // reset index
}

inline u32 
extract_u32(MersenneTwister *mt)
{
    if (mt->index >= SLIBSMT__N) twist(mt);
    u32 x = mt->state_vector[mt->index];
    x ^= (x >> SLIBSMT__U);
    x ^= (x << SLIBSMT__S) & SLIBSMT__B;
    x ^= (x << SLIBSMT__T) & SLIBSMT__C;
    return x ^ (x >> SLIBSMT__L);
}

inline void
init_mersenne_twister(MersenneTwister *mt, u32 seed)
{
    u32 *state = mt->state_vector;
    state[0] = seed;
    
    for(u32 i = 1; 
        i < SLIBSMT__N; 
        i++)
    {
        state[i] = (SLIBSMT__F * (state[i - 1] ^ (state[i - 1] >> 30)) + i);
    }

    // force twist on next random
    mt->index = SLIBSMT__N;
    state[SLIBSMT__N] = 0;
}

inline u32
rand_u32(MersenneTwister *mt)
{
    return extract_u32(mt);
}

inline f64
rand_f64(MersenneTwister *mt)
{
    return (f64)extract_u32(mt) * (1.0 / 4294967296.0); // divided by 2^32
}

inline f64
rand_f64_closed(MersenneTwister *mt)
{
    return (f64)extract_u32(mt) * (1.0 / 4294967295.0); // divided by 2^32 - 1
}

inline f64
rand_f64_open(MersenneTwister *mt)
{
    return ((f64)(extract_u32(mt)) + .5) * (1. / 4294967296.);  // divided by 2^32
}

inline f64
rand_f64_hr(MersenneTwister *mt)
{
    return ((f64)(extract_u32(mt) >> 5) * 67108864.0 + 
            (f64)(extract_u32(mt) >> 6)) * (1. / 9007199254740992.0);
}


#undef SLIBSMT__DEFAULT_SEED
#undef SLIBSMT__N
#undef SLIBSMT__M
#undef SLIBSMT__A
#undef SLIBSMT__F
#undef SLIBSMT__U
#undef SLIBSMT__S
#undef SLIBSMT__B
#undef SLIBSMT__T
#undef SLIBSMT__C
#undef SLIBSMT__L


#endif //STWISTER_H
