#include "../stypes.h"
#include "../svector.h"
#include "../squat.h"

#include <stdio.h>


inline void
print(Quat q) { printf("[%8.03f, %8.03f, %8.03f, %8.03f]", q.x, q.y, q.z, q.w); }

inline void
print(V3 v) { printf("(%8.03f, %8.03f, %8.03f)", v.x, v.y, v.z); }

inline void
print(Quat q, V3 v) { print(q); printf("    "); print(v); }


int
main()
{
    printf("\n");

    V3 v;
    Quat q;

    q = Quat(V3(1, 1, 1), 120.0f);
    print(V3(2.0f, 0.0f, 0.0f));
    printf("\n");
    print(q);

    printf("\n");

    q = normalize(q);
    print(q);

    printf("\n");
    printf("\n");
    
    v = rotate(V3(1.0f, 0.0f, 0.0f), q);
    print(v);
    printf("\n");
    q *= q;
    v = rotate(V3(1.0f, 0.0f, 0.0f), q);
    print(v);
    printf("\n");
    q *= q;
    v = rotate(V3(1.0f, 0.0f, 0.0f), q);
    print(v);
    printf("\n");

    return 0;
}
