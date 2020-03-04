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
	auto A = glm::mat2x2(9., 8., -8., 9.);
	auto rev_A = glm::inverse(A);
	//debug(rev_A);
	auto right = glm::mat2x2(4, 0, 3, 0);
	auto result = right * rev_A;
	//debug(result);
	printf("x = %.3f\ny = %.3f\n", result[0][0], result[1][0]);
	printf("x = %.3f\ny = %.3f\n", 12./145, 59./145);
	return 0;
}
/*
x = 0.083
y = 0.407
x = 0.083
y = 0.407
*/
