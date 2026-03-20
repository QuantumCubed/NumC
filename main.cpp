#include "include/numc.hpp"
#include "include/vector.hpp"
#include <iostream>
#include <memory>

int main(void) {
		
	auto vec1 = numc::Vector<int>(3);
	auto vec2 = numc::Vector<int>(3);
	
	for (int i = 0; i < 3; ++i) {
		vec1.push(i);
		vec2.push(i + 1);
	}
	
	std::cout << vec1;
	
	// auto vec3 = numc::vecAdd(vec1, vec2);
	numc::scalarX(vec1, 3);	
	// auto mat = numc::Matrix<int>(3, 3);
	
	std::cout << vec1;
	// std::cout << vec2;
	// std::cout << vec3;
	// std::cout << vec3.shape.cols;

	// std::cout << mat;
	
	return 0;
}
