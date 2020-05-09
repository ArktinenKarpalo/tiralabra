#pragma once

namespace ds {

	// Basic dynamic array with growth factor of 2
	// All functions behave similar to std::vector

	template<class T>
	class vector {
		private:
		int arr_capacity, arr_size;
		T *arr;

		void set_capacity(int new_capacity) {
			T *new_arr = new T[new_capacity];
			for(int i=0; i<arr_size; i++)
				new_arr[i] = arr[i];
			delete[] arr;
			arr = new_arr;
			arr_capacity = new_capacity;
		}

		public:

		vector() {
			arr_capacity = 1;
			arr_size = 0;
			arr = new T[arr_capacity];
		}

		void push_back(T elem) {
			if(arr_size == arr_capacity) {
				set_capacity(arr_capacity*2);
			}
			arr[arr_size] = elem;
			arr_size++;
		}

		void pop_back() {
			arr_size--;
			if(arr_capacity > 1 && arr_capacity/4 == arr_size) {
				set_capacity(arr_capacity/2);
			}
		}

		T& operator[](unsigned int pos) {
			return arr[pos];
		}

		T* begin() {
			return &arr[0];
		}

		T* end() {
			return &arr[arr_size];
		}

		unsigned int size() {
			return arr_size;
		}

		unsigned int capacity() {
			return arr_capacity;
		}

		~vector() {
			delete[] arr;
		}
	};
}