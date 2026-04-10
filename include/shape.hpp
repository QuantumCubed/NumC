#pragma once

#include <cstdint>
#include <ostream>

namespace numc {
	
	struct Shape {
		uint32_t rows;
		uint32_t cols;

		friend bool operator==(const Shape shapeA, const Shape shapeB) {
			return shapeA.rows == shapeB.rows && shapeA.cols == shapeB.cols;
		}

		friend bool operator!=(const Shape shapeA, const Shape shapeB) {
			return shapeA.rows != shapeB.rows || shapeA.cols != shapeB.cols;
		}

		friend std::ostream& operator<<(std::ostream& os, const Shape& shape) {	
			os << "(" << shape.rows << ", " << shape.cols << ")";
			return os;
	
		}
	};
}
