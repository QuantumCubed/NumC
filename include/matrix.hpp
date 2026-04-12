#pragma once

#include "shape.hpp"
#include <memory>
#include <cstddef>
#include <ostream>

namespace numc {

	template <typename T>

	struct Matrix {
		std::unique_ptr<T[]> elements;
		std::size_t capacity;
		std::size_t size;
		numc::Shape shape;

		Matrix(std::size_t rows, std::size_t cols) :
			shape({
				static_cast<uint32_t>(rows), 
				static_cast<uint32_t>(cols),
			}),
			size(0),
			capacity(rows * cols),
			elements(std::make_unique<T[]>(rows * cols)) {}
		
		Matrix(Matrix&& other) noexcept
			: size(other.size),
			  capacity(other.capacity),
			  shape(other.shape),
			  elements(std::move(other.elements)) {
			other.size = 0;
			other.capacity = 0;
		}

		~Matrix() = default;

		T get(std::uint32_t row_index, std::uint32_t col_index) const {	
			if (row_index >= shape.rows || col_index >= shape.cols) { throw std::out_of_range("index of of range!"); } 
			return elements[row_index * shape.cols + col_index];
		}

		void push(T value) {
			if (size >= capacity) return;
			elements[size++] = value;
		}

		void set(std::size_t index_row, std::size_t index_col, T value) {
			if (index_row >= shape.rows || index_col >= shape.cols) return;
			elements[index_row * shape.cols + index_col] = value;
		}
		
		friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat) {
			if (mat.size == 0) { os << "[[ ]]"; return os; }

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
		for (size_t i = 0; i < mat.size; ++i) {
			mat.elements[i] *= x;
		}
	}

	template <typename T>
	Matrix<T> matAdd(const Matrix<T>& matA, const Matrix<T>& matB) {
		// add length & shape check later
		Matrix<T> matC(matA.size);

		for (size_t i = 0; i < matA.size; ++i) {
			matC.elements[i] = matA.elements[i] + matB.elements[i];
		}

		matC.size = matA.size;
		matC.shape = matA.shape;

		return matC;
	}
	
	template <typename T>
	Matrix<T> matSub(const Matrix<T>& matA, const Matrix<T>& matB) {
		// add length & shape check later
		Matrix<T> matC(matA.size);

		for (size_t i = 0; i < matA.size; ++i) {
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
	Matrix<T> hadamard(const Matrix<T>& A, const Matrix<T>& B) {
		if (A.shape != B.shape) 
			throw std::invalid_argument("Incompatible Matrix Dimensions");
		
		Matrix<T> C(A.shape.rows, B.shape.cols);

		for (size_t i = 0; i < A.size; ++i) {
			C.elements[i] = A.elements[i] * B.elements[i];
			++C.size;
		}

		return C;
	}
  
	// ADD TILING FOR BIGGER MATRICIES e.g. 8x8
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
