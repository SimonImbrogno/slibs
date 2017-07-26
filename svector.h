#ifndef S_VECTORS_H
#define S_VECTORS_H


/* 
    SVECTOR_FAIL_ON_OOB
    - By default there is no bounds check enabled when accessing via the [] operator.
    - To enable, define SVECTOR_FAIL_ON_OOB. This causes FORCE_FAIL() on out of bounds access.
    - Obviously not the most elegant solution, but considering that they're fixed size vectors
      meant for geometric-like operations it's kinda wierd to access an arbitrary index at
      runtime anyways.
*/

#include <math.h>
#include "stypes.h"


union V2
{
    /////////////////////
    struct { f32 x, y; };
    f32 E[2];
    /////////////////////

#ifdef SVECTOR_FAIL_ON_OOB
    inline f32       &operator[](u32 indx)       { (indx < 2) ? return E[indx] : FORCE_FAIL(); }
    inline f32 const &operator[](u32 indx) const { (indx < 2) ? return E[indx] : FORCE_FAIL(); }
#else
    inline f32       &operator[](u32 indx)       { return E[indx]; }
    inline f32 const &operator[](u32 indx) const { return E[indx]; }
#endif

    V2()             : x(0), y(0)           { }
    V2(f32 x, f32 y) : x(x), y(y)           { }
    V2(s32 x, s32 y) : V2((f32)x, (f32)y)   { }
    V2(u32 x, u32 y) : V2((f32)x, (f32)y)   { }
};

union V3
{
    ////////////////////////
    struct { f32 x, y, z; };
    struct { f32 r, g, b; };
    f32 E[3];   
    ////////////////////////

#ifdef SVECTOR_FAIL_ON_OOB
    inline f32       &operator[](u32 indx)       { (indx < 3) ? return E[indx] : FORCE_FAIL(); }
    inline f33 const &operator[](u32 indx) const { (indx < 3) ? return E[indx] : FORCE_FAIL(); }
#else
    inline f32       &operator[](u32 indx)       { return E[indx]; }
    inline f32 const &operator[](u32 indx) const { return E[indx]; }
#endif

    V3()                    : x(0), y(0), z(0)              { }
    V3(f32 x, f32 y, f32 z) : x(x), y(y), z(z)              { }
    V3(s32 x, s32 y, s32 z) : V3((f32)x, (f32)y, (f32)z)    { }
    V3(u32 x, u32 y, u32 z) : V3((f32)x, (f32)y, (f32)z)    { }
    V3(V2 xy, f32 z)        : x(xy.x), y(xy.y), z(z)        { }
};

union V4
{
    ///////////////////////////
    struct { f32 x, y, z, w; };
    struct { f32 r, g, b, a; };
    f32 E[4];   
    ///////////////////////////
    
#ifdef SVECTOR_FAIL_ON_OOB
    inline f32       &operator[](u32 indx)       { (indx < 4) ? return E[indx] : FORCE_FAIL(); }
    inline f32 const &operator[](u32 indx) const { (indx < 4) ? return E[indx] : FORCE_FAIL(); }
#else
    inline f32       &operator[](u32 indx)       { return E[indx]; }
    inline f32 const &operator[](u32 indx) const { return E[indx]; }
#endif

    V4()                           : x(0), y(0), z(0), w(0)             { }
    V4(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w)             { }
    V4(u32 x, u32 y, u32 z, u32 w) : V4((f32)x, (f32)y, (f32)z, (f32)w) { }
    V4(s32 x, s32 y, s32 z, s32 w) : V4((f32)x, (f32)y, (f32)z, (f32)w) { }
    V4(V3 xyz, f32 w)              : x(xyz.x), y(xyz.y), z(xyz.z), w(w) { }
};


////////////
//NEGATION//
////////////

V2 operator-(V2 A) 
{
    V2 result; 
    result.x = -A.x;
    result.y = -A.y;
    return result;
}

V3 operator-(V3 A) 
{
    V3 result; 
    result.x = -A.x;
    result.y = -A.y;
    result.z = -A.z;
    return result;
}

V4 operator-(V4 A) 
{
    V4 result; 
    result.x = -A.x;
    result.y = -A.y;
    result.z = -A.z;
    result.w = -A.w;
    return result;
}


////////////
//ADDITION//
////////////

V2
operator+(V2 A, V2 B)
{
    V2 result;
    result.x = A.x + B.x;
    result.y = A.y + B.y;
    return result;
}

V3
operator+(V3 A, V3 B)
{
    V3 result;
    result.x = A.x + B.x;
    result.y = A.y + B.y;
    result.z = A.z + B.z;
    return result;
}

V4
operator+(V4 A, V4 B)
{
    V4 result;
    result.x = A.x + B.x;
    result.y = A.y + B.y;
    result.z = A.z + B.z;
    result.w = A.w + B.w;
    return result;
}

V2 & operator+=(V2 &A, V2 B) { A = A + B; return A; }
V3 & operator+=(V3 &A, V3 B) { A = A + B; return A; }
V4 & operator+=(V4 &A, V4 B) { A = A + B; return A; }


///////////////
//SUBTRACTION//
///////////////

V2
operator-(V2 A, V2 B)
{
    V2 result;
    result.x = A.x - B.x;
    result.y = A.y - B.y;
    return result;
}

V3
operator-(V3 A, V3 B)
{
    V3 result;
    result.x = A.x - B.x;
    result.y = A.y - B.y;
    result.z = A.z - B.z;
    return result;
}

V4
operator-(V4 A, V4 B)
{
    V4 result;
    result.x = A.x - B.x;
    result.y = A.y - B.y;
    result.z = A.z - B.z;
    result.w = A.w - B.w;
    return result;
}

V2 & operator-=(V2 &A, V2 B) { A = A - B; return A; }
V3 & operator-=(V3 &A, V3 B) { A = A - B; return A; }
V4 & operator-=(V4 &A, V4 B) { A = A - B; return A; }


/////////////////////////
//SCALAR MULTIPLICATION//
/////////////////////////

V2 
operator*(V2 A, f32 B)
{
    V2 result;
    result.x = A.x*B;
    result.y = A.y*B;
    return result;
}

V3 
operator*(V3 A, f32 B)
{
    V3 result;
    result.x = A.x*B;
    result.y = A.y*B;
    result.z = A.z*B;
    return result;
}

V4 
operator*(V4 A, f32 B)
{
    V4 result;
    result.x = A.x*B;
    result.y = A.y*B;
    result.z = A.z*B;
    result.w = A.w*B;
    return result;
}

V2 operator*(f32 A, V2 B) { return B * A; }
V3 operator*(f32 A, V3 B) { return B * A; }
V4 operator*(f32 A, V4 B) { return B * A; }

V2 & operator*=(V2 &A, f32 B) { A = B * A; return A; }
V3 & operator*=(V3 &A, f32 B) { A = B * A; return A; }
V4 & operator*=(V4 &A, f32 B) { A = B * A; return A; }


/////////////////////////
//VECTOR MULTIPLICATION//
/////////////////////////

inline f32 dotprod(V2 A, V2 B) { return (A.x*B.x) + (A.y*B.y); }
inline f32 dotprod(V3 A, V3 B) { return (A.x*B.x) + (A.y*B.y) + (A.z*B.z); }
inline f32 dotprod(V4 A, V4 B) { return (A.x*B.x) + (A.y*B.y) + (A.z*B.z) + (A.w*B.w); }

inline V2
hadamard(V2 A, V2 B)
{
    V2 result;
    result.x = (A.x*B.x);
    result.y = (A.y*B.y);
    return result;
}

inline V3
hadamard(V3 A, V3 B)
{
    V3 result;
    result.x = (A.x*B.x);
    result.y = (A.y*B.y);
    result.z = (A.z*B.z);
    return result;
}

inline V4
hadamard(V4 A, V4 B)
{
    V4 result;
    result.x = (A.x*B.x);
    result.y = (A.y*B.y);
    result.z = (A.z*B.z);
    result.w = (A.w*B.w);
    return result;
}


//////////
//LENGTH//
//////////

inline f32 length(V2 A) { return sqrtf(dotprod(A, A));}
inline f32 length(V3 A) { return sqrtf(dotprod(A, A));}
inline f32 length(V4 A) { return sqrtf(dotprod(A, A));}

inline f32 length_sq(V2 A) { return dotprod(A, A); }
inline f32 length_sq(V3 A) { return dotprod(A, A); }
inline f32 length_sq(V4 A) { return dotprod(A, A); }


/////////////
//NORMALIZE//
/////////////

V2 normalize(V2 A) { return A * (1.0f / length(A)); }
V3 normalize(V3 A) { return A * (1.0f / length(A)); }
V4 normalize(V4 A) { return A * (1.0f / length(A)); }


/////////
//CLAMP//
/////////

V2
clamp01(V2 A)
{
    V2 result;
    result.x = A.x > 1.0 ? 1.0 : A.x < 0.0 ? 0.0 : A.x;
    result.y = A.y > 1.0 ? 1.0 : A.y < 0.0 ? 0.0 : A.y;
    return result;
}

V3
clamp01(V3 A)
{
    V3 result;
    result.x = A.x > 1.0 ? 1.0 : A.x < 0.0 ? 0.0 : A.x;
    result.y = A.y > 1.0 ? 1.0 : A.y < 0.0 ? 0.0 : A.y;
    result.z = A.z > 1.0 ? 1.0 : A.z < 0.0 ? 0.0 : A.z;
    return result;
}

V4
clamp01(V4 A)
{
    V4 result;
    result.x = A.x > 1.0 ? 1.0 : A.x < 0.0 ? 0.0 : A.x;
    result.y = A.y > 1.0 ? 1.0 : A.y < 0.0 ? 0.0 : A.y;
    result.z = A.z > 1.0 ? 1.0 : A.z < 0.0 ? 0.0 : A.z;
    result.w = A.w > 1.0 ? 1.0 : A.w < 0.0 ? 0.0 : A.w;
    return result;
}



#endif
