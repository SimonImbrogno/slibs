#ifndef S_QUAT_H
#define S_QUAT_H


#include <math.h>
#include "stypes.h"
#include "svector.h"

#define SQUAT_DTOR(deg) (deg)*PI32/180.0f
#define SQUAT_RTOD(rad) (rad)*180.0f/PI32

union Quat
{
    struct { f32 x, y, z, w; };
    
    Quat()                           : x(0), y(0), z(0), w(1.0f) { }
    Quat(f32 x, f32 y, f32 z, f32 w) : x(x), y(y), z(z), w(w)    { }
    Quat(V3 axis, f32 angle)
    {
        axis = normalize(axis);

        f32 hr_hangle = 0.5f*SQUAT_DTOR(angle);
        f32 sin_hr_hangle = sinf(hr_hangle);
        
        w = cosf(hr_hangle);
        x = sin_hr_hangle*axis.x;
        y = sin_hr_hangle*axis.y;
        z = sin_hr_hangle*axis.z;
    }
    
    //Euler angles
    // Quat(f32 x, f32 y, f32 z)
    // {
    //     f64 theta;

    //     theta = x * 0.5;
    //     const f64 sr = sin(theta);
    //     const f64 cr = cos(theta);

    //     theta = y * 0.5;
    //     const f64 sp = sin(theta);
    //     const f64 cp = cos(theta);

    //     theta = z * 0.5;
    //     const f64 sy = sin(theta);
    //     const f64 cy = cos(theta);

    //     const f64 cpcy = cp * cy;
    //     const f64 spcy = sp * cy;
    //     const f64 cpsy = cp * sy;
    //     const f64 spsy = sp * sy;

    //     X = (f32)(sr * cpcy - cr * spsy);
    //     Y = (f32)(cr * spcy + sr * cpsy);
    //     Z = (f32)(cr * cpsy - sr * spcy);
    //     W = (f32)(cr * cpcy + sr * spsy);

    //     return normalize();
    // }
};

////////////
//ADDITION//
////////////

Quat operator+(Quat A, Quat B) { return Quat(A.x + B.x, A.y + B.y, A.z + B.z, A.w + B.w); }

///////////////
//SUBTRACTION//
///////////////

Quat operator-(Quat A, Quat B) { return Quat(A.x - B.x, A.y - B.y, A.z - B.z, A.w - B.w); }

/////////////////////////////
//QUATERNION MULTIPLICATION//
/////////////////////////////

//  q1 * q2 = [(a*e-b*f-c*g-d*h) + i(b*e+a*f+c*h-d*g) + j(a*g-b*h+c*e+d*f) + k(a*h+b*g-c*f+d*e)]
//OR EQUIV:
//  (sa,va) * (sb,vb) = (sa*sb-va•vb, va×vb + sa*vb + sb*va)
Quat operator*(Quat A, Quat B)
{ 
    return Quat((A.w * B.x) + (A.x * B.w) + (A.y * B.z) - (A.z * B.y),
                (A.w * B.y) - (A.x * B.z) + (A.y * B.w) + (A.z * B.x),
                (A.w * B.z) + (A.x * B.y) - (A.y * B.x) + (A.z * B.w),
                (A.w * B.w) - (A.x * B.x) - (A.y * B.y) - (A.z * B.z));
}

Quat operator*=(Quat &A, Quat B) { A = A * B; return A; }

inline f32 dotprod(Quat A, Quat B) { return A.x*B.x + A.y*B.y + A.z*B.z + A.w*B.w; }

/////////////////////////
//SCALAR MULTIPLICATION//
/////////////////////////

Quat operator*(Quat A, f32 s) { return Quat(s*A.x, s*A.y, s*A.z, s*A.w); }

Quat operator*(f32 s, Quat A) { return A*s; }

Quat & operator*=(Quat &A, f32 s) { A = A*s; return A; }

/////////////
//CONJUGATE//
/////////////

inline Quat conjugate(Quat A) { return Quat(-A.x, -A.y, -A.z, A.w); }

////////
//NORM//
////////

inline f32 norm(Quat A) { return sqrtf(dotprod(A, A)); }
inline f32 norm_sq(Quat A) { return dotprod(A, A); }

/////////////
//NORMALIZE//
/////////////

inline Quat normalize(Quat A) { return A * (1.0f / norm(A)); }

///////////
//INVERSE//
///////////

inline Quat inverse(Quat A) { return (conjugate(A) * (1.0f / norm_sq(A))); }



//////////
//ROTATE//
//////////

//Expects Q to be normalized
inline V3 rotate(V3 V, Quat Q)
{
    Quat result = ((Q * Quat(V.x, V.y, V.z, 0)) * inverse(Q)); 
    return V3(result.x, result.y, result.z);
}


#undef SQUAT_DTOR
#undef SQUAT_RTOD



#endif
