#include <stdio.h>
#include <glalgebra.h>

static const char *prog = "glalgebra_test";

int add_test()
{
	vec3 a = {{1, 0, 0.5}};
	vec3 b = {{0, 1, 0.5}};
	vec3 c = vec3_add(a, b);

	int success = (
		c.x == a.x + b.x &&
		c.y == a.x + b.x &&
		c.z == a.z + b.z);

	if (!success)
		fprintf(stderr, "%s: Add test failed.\n", prog);

	return !success;
}

int main()
{
	//Will add more tests later. Return the || of all tests.
	return add_test();
}