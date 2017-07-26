#ifndef VECTORS_H
#define VECTORS_H


#include "types.h"


union V2
{
    struct { f32 x, y; };
    f32 E[2];

    static const u8 dim = 2;

    inline f32 &operator[](u32 indx) { return E[indx]; }
    inline f32 const &operator[](u32 indx) const { return E[indx]; }

    V2()             : x(0), y(0)           { }
    V2(f32 x, f32 y) : x(x), y(y)           { }
    V2(s32 x, s32 y) : V2((f32)x, (f32)y)   { }
    V2(u32 x, u32 y) : V2((f32)x, (f32)y)   { }
};

union V3
{
    struct { f32 x, y, z; };
    struct { f32 r, g, b; };
    f32 E[3];   

    static const u8 dim = 3;

    inline f32 &operator[](u32 indx) { return E[indx]; }
    inline f32 const &operator[](u32 indx) const { return E[indx]; }

    V3()                    : x(0), y(0), z(0)              { }
    V3(f32 x, f32 y, f32 z) : x(x), y(y), z(z)              { }
    V3(s32 x, s32 y, s32 z) : V3((f32)x, (f32)y, (f32)z)    { }
    V3(u32 x, u32 y, u32 z) : V3((f32)x, (f32)y, (f32)z)    { }

    V3(V2 xy, f32 z) : x(xy.x), y(xy.y), z(z)               { }
};

union V4
{
    struct { f32 x, y, z, w; };
    struct { f32 r, g, b, a; };
    f32 E[4];   
    
    static const u8 dim = 4;

    inline f32 &operator[](u32 indx) { return E[indx]; }
    inline f32 const &operator[](u32 indx) const { return E[indx]; }

    V4()                           : x(0), y(0), z(0), w(0)             { }
    V4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w)             { }
    V4(u32 x, u32 y, u32 z, u32 w) : V4((f32)x, (f32)y, (f32)z, (f32)w) { }
    V4(s32 x, s32 y, s32 z, s32 w) : V4((f32)x, (f32)y, (f32)z, (f32)w) { }

    V4(V3 xyz, f32 w) : x(xyz.x), y(xyz.y), z(xyz.z), w(w)              { }
};

//NOTE: These can be sped up by unrolling all loops when dealing with 
//      vectors of small known size. might be worth looking into down 
//      the road if performance becomes an issue.

////////////
//NEGATION//
////////////

template <typename T>
inline T
operator-(T A)
{
    T result = {};
    for(u32 index = 0; index < A.dim; index++)
    {
        result.E[index] = -A.E[index];
    }
    return result;
}


////////////
//ADDITION//
////////////

template <typename T>
inline T 
operator+(T A, T B)
{
    T result = {};
    for(u32 index = 0; index < A.dim; index++)
    {
        result.E[index] = A.E[index] + B.E[index];
    }
    return result;
}

template <typename T>
inline T &
operator+=(T &A, T B)
{
    A = A + B;
    return A;
}


///////////////
//SUBTRACTION//
///////////////

template <typename T>
inline T 
operator-(T A, T B)
{
    T result = {};
    for(u32 index = 0; index < B.dim; index++)
    {
        result.E[index] = A.E[index] - B.E[index];
    }
    return result;
}

template <typename T>
inline T &
operator-=(T &A, T B)
{
    A = A - B;
    return A;
} 


/////////////////////////
//SCALAR MULTIPLICATION//
/////////////////////////

template <typename T>
inline T 
operator*(T A, f32 B)
{
    T result = {};
    for(u32 index = 0; index < A.dim; index++)
    {
        result.E[index] = A.E[index]*B; 
    }
    return result;
}

template <typename T>
inline T 
operator*(f32 A, T B)
{
    return B * A;
}

template <typename T>
inline T &
operator*=(T &A, f32 B)
{
    A = B * A;
    return A;
}


/////////////////////////
//VECTOR MULTIPLICATION//
/////////////////////////

template <typename T>
inline f32
dotprod(T A, T B)
{
    f32 dotProd = 0;
    for(u32 index = 0; index < A.dim; index++)
    {
        dotProd += (A.E[index]*B.E[index]);
    }
    return dotProd;
}

template <typename T>
inline T
hadamard(T A, T B)
{
    T result = {};
    for(u32 index = 0; index < A.dim; index++)
    {
        result.E[index] = (A.E[index]*B.E[index]);
    }
    return result;
}


//////////
//LENGTH//
//////////

template <typename T>
inline f32
length_sq(T A)
{
    f32 result = dotprod(A, A);
    return result;
}

template <typename T>
inline f32
length(T A)
{
    f32 result = SquareRoot(length_sq(A));
    return result;
}


/////////////
//NORMALIZE//
/////////////

template <typename T>
inline T
normalize(T A)
{
    T result = A * (1.0f / length(A));
    return result;
}

/////////
//CLAMP//
/////////

template <typename T>
inline T
clamp01(T A)
{
    T result = {};
    for(u32 index = 0; index < A.dim; index++)
    {
        result.E[index] = clamp01(A.E[index]);
    }
    return result;
}



#endif
