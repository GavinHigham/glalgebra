## GL Algebra


GL Algebra is a small C11 static library that provides types and functions for a 3-vector, a 3x3-matrix, and a 4x4 affine matrix. It is written to be exceedingly clear in both implementation and usage.

#### vec3
This type has some of the usual vector-3 functions, plus some union abuse to allow you to access its members creatively.

Access as an array of 3 floats with .A

Access as direct components with .x/.y/.z and .r/.g/.b

#### mat3
This type has some of the usual 3 by 3 matrix functions, and it's pretty much just a struct wrapper around an array of 9 floats.

Access as an array of 9 floats with .A

#### amat4
This type has some of the usual 4 by 4 matrix functions, plus some union abuse to allow you to access its members creatively. It's pretty much just a struct wrapper around an array of 12 floats. The first 9 floats represent the inner top-left 3 by 3 matrix in row-major order, then the last 3 floats represent the first three components of the rightmost column, top-to-bottom. Since it is meant to represent an affine matrix, the last row is not explicitly stored, but is implied through all operations to be <0, 0, 0, 1>.

Access the upper-left inner matrix3 with .a

Access the upper-left inner matrix3 as an array of 9 floats with .A, or .a.A (but why would you?)

Access the first three elements of the final column as an array of 3 floats with .T

Access the first three elements of the final column as a vector3 with .t

Access the first three elements of the last column with .x/.y/.z

### Example Usage

By defining the vector as a union of an array and an anonymous struct of sequential named floats, components can be accessed similar to GLSL:

	vec3 v1 = {{1.0, 2.0, 3.0}};
	vec3 v2 = {{v1.x * 4, v1.y, v1.z}};

GL Algebra does not use any operator overloading. Algebra is performed by calling functions on the defined types, passed by value. Functions return by value as well.

	vec3 v3 = vec3_scale(v1, 5.0);
	vec3 normal = vec3_cross(vec3_sub(v3, v1), vec3_sub(v2, v1)));
	normal = vec3_normalize(normal);
    
For computer graphics, you can quickly and efficiently compose affine frames by assigning to the rotation and translation components independantly.

	vec3 eye_target = {{0.0, 0.0, 0.0}};
	amat4 eye_frame = {
		.t = (vec3){{0.0, 1.0, 5.0}
	}
	eye_frame.a = mat3_lookat(eye_frame.t, eye_target, (vec3){{0, 1, 0}});
	
### Compiling and Installing
The library is just one header file and one source file. You can simply copy it into your project if you like. Alternatively, you can use the provided Makefile to compile and install the library into your /usr/local/lib/ and /usr/local/include/ folders with this command:

	make install
	
Then you can use it in any future project by prepending this to your C source files:

	#include <glalgebra.h>
	
and compiling with the flags:

	-L/usr/local/lib/ -lglalgebra
	
### Motivation

I wrote this library in the course of making a 3D game engine in C (still a work in progress). I did not like the syntax used for other linear algebra libraries, so I made my own, making use of new C11 features. GL Algebra stands for "Gavin Linear Algebra" and ""Graphics Library Algebra".
