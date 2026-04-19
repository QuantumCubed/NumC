#pragma once

#include "shape.hpp"
#include <cstddef>
#include <memory>
#include <ostream>
#include <cmath>

namespace numc {

	template <typename T>

	struct Vector {
		std::unique_ptr<T[]> elements;
		numc::Shape shape;

		Vector(size_t cols) : shape(1, cols),
			elements(std::make_unique<T[]>(cols)) {}
		
		Vector(Vector&& other) noexcept
			: shape(other.shape),
			  elements(std::move(other.elements)) {
		}

		~Vector() = default;
		
		T& operator[](size_t i) { return elements[i]; }
		const T& operator[](size_t i) const { return elements[i]; }

		friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {

			os << "[ ";

			for (std::size_t i = 0; i < vec.shape.size - 1; ++i) {
				os << vec.elements[i] << ", ";
			}

			os << vec.elements[vec.shape.size - 1] << " ]";

			return os;
		}
	};

	template <typename T>
	void scalarX(Vector<T>& vec, int x) {
		for (size_t i = 0; i < vec.shape.size; ++i) {
			vec.elements[i] *= x;
		}
	}

	template <typename T>
	Vector<T> vecAdd(const Vector<T>& vecA, const Vector<T>& vecB) {
		// add length check later
		Vector<T> vec3(vecA.shape.size);

		for (size_t i = 0; i < vecA.shape.size; ++i) {
			vec3.elements[i] = vecA.elements[i] + vecB.elements[i];
		}

		return vec3;
	}
	
	template <typename T>
	Vector<T> vecSub(const Vector<T>& vecA, const Vector<T>& vecB) {
		Vector<T> c(vecA.shape.size);

		for (size_t i = 0; i < vecA.shape.size; ++i) {
			c.elements[i] = vecA.elements[i] - vecB.elements[i];
		}

		return c;
	}

	template <typename T>
	T dot(const Vector<T>& vecA, const Vector<T>& vecB) {
		if (vecA.shape.size != vecB.shape.cols) return -1; // invalid
		
		int dot = 0;

		for (size_t i = 0; i < vecA.shape.size; ++i) {
			dot += vecA.elements[i] * vecB.elements[i];
		}
		return dot;
	}
	
	template <typename T>
	double magnitude(const Vector<T>& vec) {
		uint32_t sum = 0;

		for (size_t i = 0; i < vec.shape.size; ++i) {
			sum += (vec.elements[i] * vec.elements[i]);
		}

		return std::sqrt(sum);
	}

	template <typename T>
	double cosine_similarity(const Vector<T>& vecA, const Vector<T>& vecB) {
		double sumAB = 0;
		double sumAA = 0;
		double sumBB = 0;

		for (size_t i = 0; i < vecA.shape.size; ++i) {
			sumAB += vecA.elements[i] * vecB.elements[i];
			sumAA += vecA.elements[i] * vecA.elements[i];
			sumBB += vecB.elements[i] * vecB.elements[i];
		}

		return (sumAB / (std::sqrt(sumAA) * std::sqrt(sumBB)));
	}

	// template <typename T>
	// Vector<T> cross(const Vector<T>& vecA, const Vector<T>& vecB) {
	//
	// }
	
	template <typename T>
	Vector<T> hadamard(const Vector<T>& vecA, const Vector<T>& vecB) {
		if (vecA.shape != vecB.shape) { throw std::out_of_range("index of of range!"); } 
		
		Vector<T> c(vecA.shape.size);

		for (size_t i = 0; i < vecA.shape.size; ++i) {
			c.elements[i] = vecA.elements[i] * vecB.elements[i];
			++c.shape.cols;
		}

		return c;
	}
	
	template<typename T>
	Vector<double> normalize(const Vector<T>& vecA) {
		double magnitude = numc::magnitude(vecA);

		Vector<double> c(vecA.shape.size);

		for (size_t i = 0; i < vecA.shape.size; ++i) {
			c.elements[i] = (double) vecA.elements[i] / magnitude;
			++c.shape.cols;
		}

		return c;
	}

	template <typename T>
	T argmax(const Vector<T>& vec) {
		T max = vec.elements[0];

		for (size_t i = 1; i < vec.shape.size; ++i) {
			if (vec.elements[i] > max)
				max = vec.elements[i];
		}

		return max;
	}
}
