# Slibs

 Slibs is a collection of **S**imple **Lib**rarie**s** similar in style to Sean Barret's [STB libraries](https://github.com/nothings/stb). They are created for personal use as I find them necessary, and as such are written in a style I personally find most comfortable.  
 
 Some Things to Note:
 - Slibs are all single file header libraries. Simply include the header (and ensure the dependancies are present) to use.
 - Slibs do not make use of c++ classes.
 - Slibs do not make use of c++ templates.
 - Slibs do not make use of member functions with the exception of struct constructors.
 - Slibs do not make use of namespaces and are not meant to be compliant with C projects. (You may run into name conflicts)
 - Slibs declare all functions inline and may lead to larger compiled executables.
 - Slibs do not use a #define to create the implementation (the way STB libs do).

---
#### stypes.h
 A collection of concise typedefs for the basic types and some helpful macros. Used as a base for other Slibs.
 
---
#### svector.h
 ***Requires:*** `stypes.h`
 
 2, 3, and 4 dimensional vectors for geometric operations xy/xyz/xyzw also aliased for accessing as colour channels rgb/rgba.
 
---
#### squat.h
 ***Requires:*** `stypes.h`, `svector.h`

 Quaternions for representing 3 dimensional rotations.
 
---
#### stwister.h
 ***Requires:*** `stypes.h`

 Implementation of the Mersenne Twister PRNG.
 
---
