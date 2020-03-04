/*
Author: 11612908 Yu Zhao
*/
#include <cmath>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;

int main()
{
	auto u = glm::vec3(7.0f, 3.0f, 8.0f);
	auto result = sqrt(1.0 * u.x * u.x + u.y * u.y + u.z * u.z);
	printf("|u| = %.5f\n", result);
	return 0;
}
/*
|u| = 11.04536
*/
