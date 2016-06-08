#include "glalgebra.h"
#include <math.h> //sqrt, sin, cos
#include <string.h> //memcpy

vec3 vec3_zero = {{0.0, 0.0, 0.0}};

vec3 vec3_new(float x, float y, float z)
{
	return (vec3){{x, y, z}};
}

vec3 vec3_add(vec3 a, vec3 b)
{
	return (vec3){{a.x + b.x, a.y + b.y, a.z + b.z}};
}

vec3 vec3_sub(vec3 a, vec3 b)
{
	return (vec3){{a.x - b.x, a.y - b.y, a.z - b.z}};
}

vec3 vec3_scale(vec3 a, float b)
{
	return (vec3){{a.x*b, a.y*b, a.z*b}};
}

vec3 vec3_neg(vec3 a)
{
	return (vec3){{-a.x, -a.y, -a.z}};
}

vec3 vec3_normalize(vec3 a)
{
	float m = sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
	return (vec3){{a.x/m, a.y/m, a.z/m}};
}

vec3 vec3_cross(vec3 u, vec3 v)
{
	return (vec3){{u.y*v.z-u.z*v.y, u.z*v.x-u.x*v.z, u.x*v.y-u.y*v.x}};
}

vec3 vec3_lerp(vec3 a, vec3 b, float alpha)
{
	float beta = 1 - alpha;
	return (vec3){{a.x * alpha + b.x * beta, a.y * alpha + b.y * beta, a.z * alpha + b.z * beta, }};
}

float vec3_dot(vec3 u, vec3 v)
{
	return (u.x * v.x + u.y * v.y + u.z * v.z);
}

float vec3_mag(vec3 a)
{
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}
float vec3_dist(vec3 a, vec3 b)
{
	return vec3_mag(vec3_sub(a, b));
}

mat3 mat3_mult(mat3 a, mat3 b)
{
	return (mat3){
		{
			//First row
			a.A[0] * b.A[0] + a.A[1] * b.A[3] + a.A[2] * b.A[6],
			a.A[0] * b.A[1] + a.A[1] * b.A[4] + a.A[2] * b.A[7],
			a.A[0] * b.A[2] + a.A[1] * b.A[5] + a.A[2] * b.A[8],
			//Second row
			a.A[3] * b.A[0] + a.A[4] * b.A[3] + a.A[5] * b.A[6],
			a.A[3] * b.A[1] + a.A[4] * b.A[4] + a.A[5] * b.A[7],
			a.A[3] * b.A[2] + a.A[4] * b.A[5] + a.A[5] * b.A[8],
			//Third row
			a.A[6] * b.A[0] + a.A[7] * b.A[3] + a.A[8] * b.A[6],
			a.A[6] * b.A[1] + a.A[7] * b.A[4] + a.A[8] * b.A[7],
			a.A[6] * b.A[2] + a.A[7] * b.A[5] + a.A[8] * b.A[8]
		}
	};
}

vec3 mat3_multvec(mat3 a, vec3 b)
{
	return (vec3){
		.A = {
			a.A[0]*b.x + a.A[1]*b.y + a.A[2]*b.z,
			a.A[3]*b.x + a.A[4]*b.y + a.A[5]*b.z,
			a.A[6]*b.x + a.A[7]*b.y + a.A[8]*b.z
		}
	};
}

mat3 mat3_rot(mat3 a, float ux, float uy, float uz, float s, float c)
{
	return mat3_mult(a, mat3_rotmat(ux, uy, uz, s, c));
}

mat3 mat3_rotmat(float ux, float uy, float uz, float s, float c)
{
	float c1 = 1-c;
	return (mat3){
		{
			c + ux*ux*c1, ux*uy*c1 - uz*s, ux*uz*c1 + uy*s, 
			uy*ux*c1 + uz*s, c + uy*uy*c1, uy*uz*c1 - ux*s,
			ux*uz*c1 - uy*s, uy*uz*c1 + ux*s, c + uz*uz*c1
		}
	};
}

mat3 mat3_rotmatx(float s, float c)
{
	return (mat3){
		{
			1, 0, 0,
			0, c, -s,
			0, s, c
		}
	};
}
mat3 mat3_rotmaty(float s, float c)
{
	return (mat3){
		{
			c, 0, s,
			0, 1, 0,
			-s, 0, c
		}
	};
}
mat3 mat3_rotmatz(float s, float c)
{
	return (mat3){
		{
			c, -s, 0,
			s, c, 0,
			0, 0, 1
		}
	};
}

mat3 mat3_scale(mat3 a, float x, float y, float z)
{
	return (mat3){
		{
			x*a.A[0], x*a.A[1], x*a.A[2],
			y*a.A[3], y*a.A[4], y*a.A[5],
			z*a.A[6], z*a.A[7], z*a.A[8]
		}
	};
};

mat3 mat3_scalemat(float x, float y, float z)
{
	return (mat3){
		{
			x, 0, 0,
			0, y, 0,
			0, 0, z
		}
	};
}

mat3 mat3_transp(mat3 a)
{
	return (mat3){
		{
			a.A[0], a.A[3], a.A[6],
			a.A[1], a.A[4], a.A[7],
			a.A[2], a.A[5], a.A[8]
		}
	};
}

mat3 mat3_lookat(vec3 p, vec3 q, vec3 u)
{
	vec3 z = vec3_normalize(vec3_sub(p, q));
	vec3 x = vec3_normalize(vec3_cross(u, z));
	vec3 y = vec3_cross(z, x);
	return (mat3){{
		x.x, y.x, z.x,
		x.y, y.y, z.y,
		x.z, y.z, z.z
	}};
}

void mat3_vec3_to_array(mat3 a, vec3 b, float *buf)
{
	float tmp[] = {
		a.A[0], a.A[1], a.A[2], b.x,
		a.A[3], a.A[4], a.A[5], b.y,
		a.A[6], a.A[7], a.A[8], b.z,
		     0,      0,      0,    1
	};
	memcpy(buf, tmp, sizeof(tmp));
}

amat4 amat4_mult(amat4 a, amat4 b)
{
	return (amat4){
		.A = {
			//Top row
			a.A[0] * b.A[0] + a.A[1] * b.A[3] + a.A[2] * b.A[6],
			a.A[0] * b.A[1] + a.A[1] * b.A[4] + a.A[2] * b.A[7],
			a.A[0] * b.A[2] + a.A[1] * b.A[5] + a.A[2] * b.A[8],
			//Second row
			a.A[3] * b.A[0] + a.A[4] * b.A[3] + a.A[5] * b.A[6],
			a.A[3] * b.A[1] + a.A[4] * b.A[4] + a.A[5] * b.A[7],
			a.A[3] * b.A[2] + a.A[4] * b.A[5] + a.A[5] * b.A[8],
			//Third row
			a.A[6] * b.A[0] + a.A[7] * b.A[3] + a.A[8] * b.A[6],
			a.A[6] * b.A[1] + a.A[7] * b.A[4] + a.A[8] * b.A[7],
			a.A[6] * b.A[2] + a.A[7] * b.A[5] + a.A[8] * b.A[8]
		},
		.T = {
			a.A[0] * b.x + a.A[1] * b.y + a.A[2] * b.z + a.x,
			a.A[3] * b.x + a.A[4] * b.y + a.A[5] * b.z + a.y,
			a.A[6] * b.x + a.A[7] * b.y + a.A[8] * b.z + a.z
		}
	};
}

vec3 amat4_multpoint(amat4 a, vec3 b)
{
	return (vec3){{
		a.A[0]*b.x + a.A[1]*b.y + a.A[2]*b.z + a.x,
		a.A[3]*b.x + a.A[4]*b.y + a.A[5]*b.z + a.y,
		a.A[6]*b.x + a.A[7]*b.y + a.A[8]*b.z + a.z
	}};
}

vec3 amat4_multvec(amat4 a, vec3 b)
{
	return (vec3){{
		a.A[0]*b.x + a.A[1]*b.y + a.A[2]*b.z,
		a.A[3]*b.x + a.A[4]*b.y + a.A[5]*b.z,
		a.A[6]*b.x + a.A[7]*b.y + a.A[8]*b.z
	}};
}

amat4 amat4_rot(amat4 a, float ux, float uy, float uz, float s, float c)
{
	amat4 b = amat4_rotmat(ux, uy, uz, s, c);
	return (amat4){
		.A = {
			//Top row
			a.A[0] * b.A[0] + a.A[1] * b.A[3] + a.A[2] * b.A[6],
			a.A[0] * b.A[1] + a.A[1] * b.A[4] + a.A[2] * b.A[7],
			a.A[0] * b.A[2] + a.A[1] * b.A[5] + a.A[2] * b.A[8],
			//Second row
			a.A[3] * b.A[0] + a.A[4] * b.A[3] + a.A[5] * b.A[6],
			a.A[3] * b.A[1] + a.A[4] * b.A[4] + a.A[5] * b.A[7],
			a.A[3] * b.A[2] + a.A[4] * b.A[5] + a.A[5] * b.A[8],
			//Third row
			a.A[6] * b.A[0] + a.A[7] * b.A[3] + a.A[8] * b.A[6],
			a.A[6] * b.A[1] + a.A[7] * b.A[4] + a.A[8] * b.A[7],
			a.A[6] * b.A[2] + a.A[7] * b.A[5] + a.A[8] * b.A[8]
		},
		.T = {a.x, a.y, a.z}
	};
}

void amat4_to_array(amat4 a, float *buf)
{
	float tmp[] = {
		a.A[0], a.A[1], a.A[2], a.x,
		a.A[3], a.A[4], a.A[5], a.y,
		a.A[6], a.A[7], a.A[8], a.z,
		     0,      0,      0,      1
	};
	memcpy(buf, tmp, sizeof(tmp));
};

amat4 amat4_rotmat(float ux, float uy, float uz, float s, float c)
{
	float c1 = 1-c;
	return (amat4){
		.A = {
			c + ux*ux*c1, ux*uy*c1 - uz*s, ux*uz*c1 + uy*s, 
			uy*ux*c1 + uz*s, c + uy*uy*c1, uy*uz*c1 - ux*s,
			ux*uz*c1 - uy*s, uy*uz*c1 + ux*s, c + uz*uz*c1
		},
		.T = {0}
	};
}

amat4 amat4_rotmat_lomult(float ux, float uy, float uz, float s, float c)
{
	float c1 = 1-c;
	//This strategy may exhibit poorer instruction-level parallelism.
	float uxc1 = ux*c1;    //Costs one multiply, saves five
	float uyc1 = uy*c1;    //Costs one multiply, saves three
	float uyzc1 = uz*uyc1; //Costs one multiply, saves two
	float uxs = ux * s;    //Costs one multiply, saves two
	float uys = uy * s;    //Costs one multiply, saves two
	float uzs = uz * s;    //Costs one multiply, saves two
	return (amat4){
		.A = {
			c + ux*uxc1, uy*uxc1 - uzs, uz*uxc1 + uys, 
			uy*uxc1 + uzs, c + uy*uyc1, uyzc1 - uxs,
			uz*uxc1 - uys, uyzc1 + uxs, c + uz*uz*c1
		},
		.T = {0}
	};
}

amat4 amat4_inverse(amat4 a)
{
	return (amat4){
		.A = {
			a.A[0], a.A[3], a.A[6],
			a.A[1], a.A[4], a.A[7],
			a.A[2], a.A[5], a.A[8]
		},
		.T = {
			(-a.A[0] * a.x) - (a.A[3] * a.y) - (a.A[6] * a.z),
			(-a.A[1] * a.x) - (a.A[4] * a.y) - (a.A[7] * a.z),
			(-a.A[2] * a.x) - (a.A[5] * a.y) - (a.A[8] * a.z)
		}
	};
}

void amat4_buf_mult(float * restrict a, float * restrict b, float * restrict out)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			out[i * 4 + j] =
			a[i * 4 + 0] * b[ 0 + j]+
			a[i * 4 + 1] * b[ 4 + j]+
			a[i * 4 + 2] * b[ 8 + j]+
			a[i * 4 + 3] * b[12 + j];
		}
	}
}

void amat4_mat_buf_mult(amat4 a, float * restrict b, float * restrict out)
{
	float tmp[16];
	amat4_to_array(a, tmp);
	amat4_buf_mult(tmp, b, out);
}

void amat4_buf_mat_mult(float * restrict a, amat4 b, float * restrict out)
{
	float tmp[16];
	amat4_to_array(b, tmp);
	amat4_buf_mult(a, tmp, out);
}
