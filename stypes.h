#ifndef S_TYPES_H
#define S_TYPES_H



#include <stdint.h>

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef u32 b32;

typedef float f32;
typedef double f64;

#define F32_E 0.000001
#define F64_E 0.0000000000001

//TODO: Using a static epsilon when comparing for zero may be bad
//      In general a static epsilon could be improved on:
//          - relative epsilon based on size of comparators
//          - relative based on calculation
//          - dwarven magyks
inline b32 fiszero(f32 n, f32 e = F32_E) { return (n >= -e && n <= e); }
inline b32 fiszero(f64 n, f64 e = F64_E) { return (n >= -e && n <= e); }

#if ASSERT_OFF
    #define ASSERT(Expression)
    #define FORCE_FAIL()
#else
    #define ASSERT(Expression) if(!(Expression)) {*(int *)0 = 0;}
    #define FORCE_FAIL() {b32 fail = false; ASSERT(fail);}
#endif

#define Kilobytes(value) ((value)*1024LL)
#define Megabytes(value) (Kilobytes(value)*1024LL)
#define Gigabytes(value) (Megabytes(value)*1024LL)
#define Terabytes(value) (Gigabytes(value)*1024LL)

#define arraycount(Array) (sizeof(Array) / sizeof((Array)[0]))

#define PI32 3.141592653589793238462f
#define TAU32 6.28318530717958647692f



#endif
