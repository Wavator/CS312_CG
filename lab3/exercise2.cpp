/*
Author: 11612908 Yu Zhao
*/
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

int main()
{
	auto u = glm::vec3(9.0f, 8.0f, 5.0f);
	auto v = glm::vec3(6.0f, 6.0f, 3.0f);
	auto result1 = u - v;
	printf("u - v = (%.0f, %.0f, %.0f)\n", result1.x, result1.y, result1.z);
	auto result2 = u + (v *= 5);
	printf("u + 5v = (%.0f, %.0f, %.0f)\n", result2.x, result2.y, result2.z);
	return 0;
}
/*
u - v = (3, 2, 2)
u + 5v = (39, 38, 20)
*/
