#include "../stypes.h"
#include "../svector.h"
#include "../squat.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


inline void
print(Quat q) { printf("[%8.03f, %8.03f, %8.03f, %8.03f]", q.x, q.y, q.z, q.w); }

inline void
print(V3 v) { printf("(%8.03f, %8.03f, %8.03f)", v.x, v.y, v.z); }

inline void
print(Quat q, V3 v) { print(q); printf("    "); print(v); }

inline float
get_random(f32 max)
{
    return ((float) (rand())) / ((float) (RAND_MAX/max));
}

inline float
angle_between(V3 a, V3 b)
{
    a = normalize(a);
    b = normalize(b);

    if(length(a) == 0.0f || length(b) == 0.0f)
    {
        return 0.0f;
    }
    
    return acosf(dotprod(a,b) / (length(a) * length(b)));
}

#define TEST_DTOR(deg) (deg)*PI32/180.0f
#define TEST_RTOD(rad) (rad)*180.0f/PI32

int
main()
{
    printf("\n");

    
    srand(0);
    //srand(time(NULL));

    V3 v, axis, target;
    f32 angle;
    Quat q;

    f32 e = 0.0001;

    u32 n_success = 0;
    u32 n_failure = 0;

    for(int i=0; i<1000; i++)
    {
        angle  = get_random(1440.0f) - 720.0f;
        axis   = V3(get_random(1.0f), get_random(1.0f), get_random(1.0f));
        target = V3(get_random(1.0f), get_random(1.0f), get_random(1.0f));

        f32 test_angle = angle < 0 ? -angle : angle;
        while(test_angle >= 360.0f) test_angle -= 360.0f;
        if(test_angle > 180.0f)     test_angle = 360.0f - test_angle;
        
        axis   = normalize(axis); 
        target = normalize(target);

        q = Quat(axis, angle);

        printf("Angle: %f, Axis: ", angle);
        print(axis);

        printf("\n");

        f32 tangle;
        V3 taxis;
        get_angle_axis(q, &tangle, &taxis);
        printf("Angle: %f, Axis: ", tangle);
        print(taxis);

        printf("\n");

        // q = normalize(q);
        v = rotate(target, q);

        f32 ldiff = length(v) - length(target);
        f32 final_angle1 = TEST_RTOD(angle_between(v, axis));
        f32 final_angle2 = TEST_RTOD(angle_between(target, axis));
        f32 adiff = final_angle1 - final_angle2;

        print(conjugate(q));
        printf("\n");
        print(inverse(q));
        printf("\n");
        printf("\n");

        if((ldiff < e && ldiff > -e) &&
           (adiff < e && adiff > -e))
        {
            n_success++;
        }
        else
        {
            n_failure++;

            printf("Rotate  ");
            print(target);
            printf("  %8.03f degrees", angle);
            printf("  %8.03f effective", test_angle);
            printf("\naround  ");
            print(axis);
            printf("\nwith    ");
            print(q);
            printf("\nis      ");
            print(v);
            printf("\n");
            printf("Angle1:  %10.05f\nAngle2:  %10.05f\n", final_angle1, final_angle2);
            printf("Error: %f,    %f%%\n", final_angle1 - final_angle2, (final_angle1 - final_angle2)/final_angle2);
            printf("----------------FAILURE----------------\n");
            printf("\n");
        }
    }
    
    printf("Passed: %d\nFailed: %d,    %f%%", n_success, n_failure, (float)n_failure/(float)(n_success + n_failure));

    return 0;
}
