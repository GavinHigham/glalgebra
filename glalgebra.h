#ifndef GLALGEBRA_H
#define GLALGEBRA_H

typedef union vector3 {
	float A[3];
	struct {
		float x, y, z;
	};
	struct {
		float r, g, b;
	};
} vec3;

typedef struct matrix3 {
	float A[9];
} mat3;

typedef struct affine_matrix4 {
	union {
		float A[9];
		mat3 a;
	};
	union {
		float T[3];
		struct {
			float x, y, z;
		};
		vec3 t;
	};
} amat4;

#define MAT3_IDENT (mat3){{1, 0, 0,  0, 1, 0,  0, 0, 1}}
#define AMAT4_IDENT {.a = MAT3_IDENT, .t = (vec3){{0.0, 0.0, 0.0}}}

//Produces a new vector. Equivalent to (vec3){{{x, y, z}}}.
vec3 vec3_new(float x, float y, float z);
//Returns a new vector that represents the addition of respective components of a and b.
//(a + b)
vec3 vec3_add(vec3 a, vec3 b);
//Returns a new vector that represents the subtraction of respective components of a and b.
//(a - b)
vec3 vec3_sub(vec3 a, vec3 b);
//Returns a new vector that represents the scaling of a by factor b.
//(a * b)
vec3 vec3_scale(vec3 a, float b);
//Returns a new vector that represents the negation of each component of a.
//(-a)
vec3 vec3_neg(vec3 a);
//Returns a new vector that represents the normalization of a.
//Normalizing a zero-vector is undefined.
vec3 vec3_normalize(vec3 a);
//Returns a new vector that represents the cross product of a and b.
vec3 vec3_cross(vec3 a, vec3 b);
//Returns a new vector that is linearly interpolated between a and by by parameter alpha.
//(a*alpha + b*(1 - alpha)
vec3 vec3_lerp(vec3 a, vec3 b, float alpha);
//Return the dot product of a and b.
float vec3_dot(vec3 a, vec3 b);
//Return the magnitude of a.
float vec3_mag(vec3 a);
//Return the distance between a and b.
float vec3_dist(vec3 a, vec3 b);

//Create a new mat3 from an array of floats. Row-major order.
mat3 mat3_from_array(float *array);
//3x3 Identity matrix.
mat3 mat3_ident();
//Multiply a by b
mat3 mat3_mult(mat3 a, mat3 b);
//Multiply a by the column vector b.
vec3 mat3_multvec(mat3 a, vec3 b);
//Rotate a about <ux, uy, uz> by some angle, provided by s and c.
//s and c should be the sine and cosine of the angle, respectively.
mat3 mat3_rot(mat3 a, float ux, float uy, float uz, float s, float c);
//Produces the matrix for a rotation about <ux, uy, uz> by some angle, provided by s and c.
//s and c should be the sine and cosine of the angle, respectively.
mat3 mat3_rotmat(float ux, float uy, float uz, float s, float c);
//Produces a rotation matrix about the three basis vectors by some angle, provided by s and c.
//s and c should be the sine and cosine of the angle, respectively.
mat3 mat3_rotmatx(float s, float c);
mat3 mat3_rotmaty(float s, float c);
mat3 mat3_rotmatz(float s, float c);
//Scale a by x, y, z.
mat3 mat3_scale(mat3 a, float x, float y, float z);
//Produce a matrix that will scale by x, y, z.
mat3 mat3_scalemat(float x, float y, float z);
//Produce the transpose matrix of a.
mat3 mat3_transp(mat3 a);
//Produce a rotation matrix that will look from p to q, with u up.
mat3 mat3_lookat(vec3 p, vec3 q, vec3 u);
//Takes a mat3 and a vec3, and copies them into a buffer representing a true, row-major 4x4 matrix.
//a becomes the rotation portion, and b becomes the translation.
void mat3_vec3_to_array(mat3 a, vec3 b, float *buf);

//Multiply a by b and return the result as a new affine matrix.
amat4 amat4_mult(amat4 a, amat4 b);
//Multiply a by b and return the result as a new affine matrix.
//This version has branches to try to reduce multiplications. (Faster on ARM?)
amat4 amat4_mult_b(amat4 a, amat4 b);
//Multiply a by b as a column vector and return a new vector.
//b is implied to be a 4-vec with the form <x, y, z, 1>
vec3 amat4_multpoint(amat4 a, vec3 b);
//Multiply a by b as a column vector and return a new vector.
//b is implied to be a 4-vec with the form <x, y, z, 0>
//It's probably faster to do mat3_multvec(a.a, b), since that copies less.
vec3 amat4_multvec(amat4 a, vec3 b);
//Produce a new matrix that is the result of rotating a about the axis <ux, uy, uz> by angle, in radians.
//<ux, uy, uz> should be normalized beforehand.
//s and c should be the sine and cosine of the angle, respectively.
amat4 amat4_rot(amat4 a, float ux, float uy, float uz, float s, float c);
//Copy a into a buffer representing a true 4x4 row-major matrix.
//The buffer should be large enough to store 16 floats.
//The last row will be <0, 0, 0, 1>.
void amat4_to_array(amat4 a, float *buf);
//Produce a rotation matrix which represents a rotation about <ux, uy, uz> by some angle.
//s and c should be the sine and cosine of the angle, respectively.
amat4 amat4_rotmat(float ux, float uy, float uz, float s, float c);
//Produce a rotation matrix which represents a rotation about <ux, uy, uz> by angle, in radians.
//This version tries to reduce multiplications at the cost of more interdependant local variables.
amat4 amat4_rotmat_lomult(float ux, float uy, float uz, float s, float c);
//Produce a lookat matrix that points from point p to point q, with u as "up".
amat4 amat4_lookat(vec3 p, vec3 q, vec3 u);
//Produce the inverse matrix to a, provided that a represents a rotation and a translation.
//This is not a true inverse, which in practice would be quite slow, and should be avoided.
//Thus, this does not work if a represents a scale or skew.
amat4 amat4_inverse(amat4 a);
//Do a true 4x4 matrix multiply between a and b, and put the result into out.
//a, b and out should represent 4x4 row-major matrices, as arrays of floats.
//a, b and out must all be different 16-float buffers, or the behaviour of this function is undefined.
void amat4_buf_mult(float * restrict a, float * restrict b, float * restrict out);
//Do a true 4x4 matrix multiply between a and b, and put the result into out.
//b and out should represent 4x4 row-major matrices, as arrays of floats.
//b and out must all be different 16-float buffers, or the behaviour of this function is undefined.
void amat4_amat_buf_mult(amat4 a, float * restrict b, float * restrict out);
//Do a true 4x4 matrix multiply between a and b, and put the result into out.
//a and out should represent 4x4 row-major matrices, as arrays of floats.
//a and out must all be different 16-float buffers, or the behaviour of this function is undefined.
void amat4_buf_amat_mult(float * restrict a, amat4 b, float * restrict out);

#endif