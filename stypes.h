#ifndef TYPES_H
#define TYPES_H



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

//Assert for looking at variable contents in MSVC
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



#endif
