#pragma once

#include "shape.hpp"
#include <cstddef>
#include <memory>
#include <ostream>

namespace numc {

	template <typename T>

	struct Vector {
		std::unique_ptr<T[]> elements;
		std::size_t size;
		std::size_t capacity;
		numc::Shape shape;

		Vector(size_t capacity) : size(0), capacity(capacity), shape({ .rows = 1, .cols = 0}),
			elements(std::make_unique<T[]>(capacity)) {}

		~Vector() = default;

		void push(T value) {
			if (size >= capacity) return;
			elements[size++] = value;
			shape.cols = size;
		}

		T get(std::size_t index) {
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

			os << vec.elements[vec.size - 1] << " ]\n";

			return os;
		}
	};
}
