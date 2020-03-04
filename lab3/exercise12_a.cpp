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
	auto e = glm::vec2(sqrtf(2) / 2, sqrtf(2) / 2);
	auto u = glm::vec2(9, 4);
	auto res = e * u;
	//cout << res.t << endl;
	cout << res.x + res.y << endl;
	cout << sqrtf(2) * 13 / 2 << endl;
	return 0;
}
/*
9.19239
9.19239
*/
