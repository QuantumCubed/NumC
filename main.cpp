#include "include/numc.hpp"
#include "include/vector.hpp"
#include <iostream>
#include <memory>

int main(void) {
		
	// auto vec1 = numc::Vector<int>(3);
	// auto vec2 = numc::Vector<int>(3);
	//
	// for (int i = 0; i < 3; ++i) {
	// 	vec1.push(i);
	// 	vec2.push(i + 1);
	// }
	//
	// std::cout << vec1;
	// std::cout << vec2;	
	//
	// double similarity = numc::cosine_similarity(vec1, vec2);
	//
	// std::cout << similarity << "\n";
	
	// MATRIX TEST STARTS HERE:
	
	auto matrixA = numc::Matrix<int>(3, 3);
	auto matrixB = numc::Matrix<int>(3, 3);

	for (int i = 0; i < 9; ++i) {
		matrixA.push(i + 1);
	}
	
	for (int i = 9; i >= 0; --i) {
		matrixB.push(i);
	}

	std::cout << matrixA << "\n";
	std::cout << matrixB << "\n";
	
	numc::Matrix<int> matrixC = numc::matMult(matrixA, matrixB);

	std::cout << matrixC << "\n";

	return 0;
}
