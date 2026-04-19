#pragma once

#include "shape.hpp"
#include <memory>
#include <cstddef>
#include <ostream>

namespace numc {

	template <typename T>

	struct Matrix {
		std::unique_ptr<T[]> elements;
		numc::Shape shape;

		Matrix(std::size_t rows, std::size_t cols) :
			shape(rows, cols),
			elements(std::make_unique<T[]>(rows * cols)) {}
	
		Matrix(numc::Shape shape) : shape(shape),
		elements(std::make_unique<T[]>(shape.rows * shape.cols)) {}

		Matrix(Matrix&& other) noexcept
			: shape(other.shape),
			  elements(std::move(other.elements)) {
		}

		~Matrix() = default;

		T* operator[](size_t i) { return elements.get() + i * shape.cols; }
		const T* operator[](size_t i) const { return elements.get() + i * shape.cols; }
		
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
			os << "[";

			for (uint32_t i = 0; i < mat.shape.rows; ++i) {
				if(i == 0) { os << "[ "; } else { os << "\n [ "; }
				for (uint32_t j = 0; j < mat.shape.cols; ++j) {
					auto element = mat.elements[i * mat.shape.cols + j];
					if(j + 1 == mat.shape.cols) {
						os << element << " ]";
						break;
					}
					
					os << element << ", ";
				}
			}
			os << "]" << "\n";
			return os;
		}
	};

	template <typename T>
	void scalarX(Matrix<T>& mat, int x) {
		for (size_t i = 0; i < mat.shape.rows * mat.shape.cols; ++i) {
			mat.elements[i] *= x;
		}
	}

	template <typename T>
	Matrix<T> matAdd(const Matrix<T>& matA, const Matrix<T>& matB) {
		// add length & shape check later
		Matrix<T> matC(matA.shape);

		for (size_t i = 0; i < matA.shape.size; ++i) {
			matC.elements[i] = matA.elements[i] + matB.elements[i];
		}

		matC.shape = matA.shape;

		return matC;
	}
	
	template <typename T>
	Matrix<T> matSub(const Matrix<T>& matA, const Matrix<T>& matB) {
		// add length & shape check later
		Matrix<T> matC(matA.shape);

		for (size_t i = 0; i < matA.shape.size; ++i) {
			matC.elements[i] = matA.elements[i] - matB.elements[i];
		}

		matC.size = matA.size;
		matC.shape = matA.shape;

		return matC;
	}

	template <typename T>
	Matrix<T> matMult(const Matrix<T>& matA, const Matrix<T>& matB) {
		// add shape validity check: (m x n) * (n x p)

		if (matA.shape.cols != matB.shape.rows)
			throw std::invalid_argument("Incompatible Matrix Dimensions");
		
		Matrix<T> matC(matA.shape.rows, matB.shape.cols);
		matC.size = matC.shape.rows * matC.shape.cols;

		for (size_t k = 0; k < matA.shape.cols; ++k) {
			for (size_t i = 0; i < matA.shape.rows; ++i) {
				auto matA_ik = matA.elements[i * matA.shape.cols + k];
				for (size_t j = 0; j < matB.shape.cols; ++j) {
					matC.elements[i * matC.shape.cols + j] +=
						matA_ik * matB.elements[k * matB.shape.cols + j];
				}
			}
		}
		return matC;
	}

	template <typename T>
	Matrix<T> hadamard(const Matrix<T>& matA, const Matrix<T>& matB) {
		if (matA.shape != matB.shape) 
			throw std::invalid_argument("Incompatible Matrix Dimensions");
		
		Matrix<T> matC(matA.shape.rows, matB.shape.cols);

		for (size_t i = 0; i < matA.size; ++i) {
			matC.elements[i] = matA.elements[i] * matB.elements[i];
			++matC.size;
		}

		return matC;
	}
  
	// ADD TILING FOR BIGGER MATRImatC.ES e.g. 8x8
	template <typename T>
	Matrix<T> transpose(const Matrix<T>& mat) {
		Matrix<T> t(mat.shape.cols, mat.shape.rows);

		for (size_t i = 0; i < mat.shape.rows; ++i) {
			for (size_t j = 0; j < mat.shape.cols; j++) {
				t.elements[j * mat.shape.rows + i] = mat.elements[i * mat.shape.cols + j];
				++t.size;
			}
		}
		return t;
	}

}
