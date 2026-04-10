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
		std::size_t size;
		std::size_t capacity;
		numc::Shape shape;

		Vector(size_t capacity) : size(0), capacity(capacity), shape({ .rows = 1, .cols = 0}),
			elements(std::make_unique<T[]>(capacity)) {}
		
		Vector(Vector&& other) noexcept
			: size(other.size),
			  capacity(other.capacity),
			  shape(other.shape),
			  elements(std::move(other.elements)) {
			other.size = 0;
			other.capacity = 0;
		}

		~Vector() = default;

		void push(T value) {
			if (size >= capacity) return;
			elements[size++] = value;
			shape.cols = size;
		}

		T get(std::size_t index) const {
			if (index >= size) throw std::out_of_range("index of of range!");
			return elements[index];
		}

		void set(std::size_t index, T value) {
			if (index >= size) return;
			elements[index] = value;
		}

		friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec) {
			if (vec.size == 0) { os << "[ ]"; return os; }

			os << "[ ";

			for (std::size_t i = 0; i < vec.size - 1; ++i) {
				os << vec.elements[i] << ", ";
			}

			os << vec.elements[vec.size - 1] << " ]";

			return os;
		}
	};

	template <typename T>
	void scalarX(Vector<T>& vec, int x) {
		for (size_t i = 0; i < vec.size; ++i) {
			vec.elements[i] *= x;
		}
	}

	template <typename T>
	Vector<T> vecAdd(const Vector<T>& vec1, const Vector<T>& vec2) {
		// add length check later
		Vector<T> vec3(vec1.size);

		for (size_t i = 0; i < vec1.size; ++i) {
			vec3.elements[i] = vec1.elements[i] + vec2.elements[i];
		}

		vec3.size = vec1.size;
		vec3.shape.cols = vec1.shape.cols;

		return vec3;
	}
	
	template <typename T>
	Vector<T> vecSub(const Vector<T>& a, const Vector<T>& b) {
		Vector<T> c(a.size);

		for (size_t i = 0; i < a.size; ++i) {
			c.elements[i] = a.elements[i] - b.elements[i];
		}

		c.size = a.size;
		c.shape.cols = a.shape.cols;

		return c;
	}

	template <typename T>
	T dot(const Vector<T>& vec1, const Vector<T>& vec2) {
		if (vec1.size != vec2.size) return -1; // invalid
		
		int dot = 0;

		for (size_t i = 0; i < vec1.size; ++i) {
			dot += vec1.elements[i] * vec2.elements[i];
		}
		return dot;
	}
	
	template <typename T>
	double magnitude(const Vector<T>& vec) {
		uint32_t sum = 0;

		for (size_t i = 0; i < vec.size; ++i) {
			sum += (vec.elements[i] * vec.elements[i]);
		}

		return std::sqrt(sum);
	}

	template <typename T>
	double cosine_similarity(const Vector<T>& a, const Vector<T>& b) {
		double sumAB = 0;
		double sumAA = 0;
		double sumBB = 0;

		for (size_t i = 0; i < a.size; ++i) {
			sumAB += a.elements[i] * b.elements[i];
			sumAA += a.elements[i] * a.elements[i];
			sumBB += b.elements[i] * b.elements[i];
		}

		return (sumAB / (std::sqrt(sumAA) * std::sqrt(sumBB)));
	}

	// template <typename T>
	// Vector<T> cross(const Vector<T>& vecA, const Vector<T>& vecB) {
	//
	// }
	
	template <typename T>
	Vector<T> hadamard(const Vector<T>& a, const Vector<T>& b) {
		if (a.shape != b.shape) { throw std::out_of_range("index of of range!"); } 
		
		Vector<T> c(a.capacity);

		for (size_t i = 0; i < a.capacity; ++i) {
			c.elements[i] = a.elements[i] * b.elements[i];
			++c.size;
		}
		c.shape.cols = c.size;

		return c;
	}
	
	template<typename T>
	Vector<double> normalize(const Vector<T>& a) {
		double magnitude = numc::magnitude(a);

		Vector<double> c(a.capacity);

		for (size_t i = 0; i < a.size; ++i) {
			c.elements[i] = (double) a.elements[i] / magnitude;
			++c.size;
		}
		c.shape.cols = c.size;

		return c;
	}

	template <typename T>
	T argmax(const Vector<T>& vec) {
		T max = vec.elements[0];

		for (size_t i = 1; i < vec.size; ++i) {
			if (vec.elements[i] > max)
				max = vec.elements[i];
		}

		return max;
	}
}
