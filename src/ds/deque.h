#pragma once

namespace ds {

	// Similar to vector
	// All operations amortized O(1), growth factor 2
	// All functions behave similar to std::deque

	template<class T>
	class deque {
		private:
		int front_elem, back_elem;
		int arr_capacity, arr_size;
		T *arr;

		// Resize to the given capacity
		void set_capacity(int new_capacity) {
			T *new_arr = new T[new_capacity];
			for(int i=0; i<arr_size; i++) {
				if(front_elem == arr_capacity)
					front_elem = 0;
				new_arr[i] = arr[front_elem++];
			}
			delete[] arr;
			arr = new_arr;
			arr_capacity = new_capacity;
			front_elem = 0;
			back_elem = arr_size-1;
		}

		public:
		deque() {
			arr_size = 0;
			arr_capacity = 1;
			arr = new T[arr_capacity];
		}

		void push_back(T elem) {
			if(arr_size == arr_capacity) {
				set_capacity(arr_capacity*2);
			}
			if(arr_size == 0) {
				front_elem = 0;
				back_elem = -1;
			}
			back_elem++;
			if(back_elem == arr_capacity)
				back_elem = 0;
			arr[back_elem] = elem;
			arr_size++;
		}

		void push_front(T elem) {
			if(arr_size == arr_capacity) {
				set_capacity(arr_capacity*2);
			}
			if(arr_size == 0) {
				front_elem = 1;
				back_elem = 0;
			}
			if(front_elem == 0) {
				front_elem = arr_capacity;
			}
			front_elem--;
			arr[front_elem] = elem;
			arr_size++;
		}

		void pop_back() {
			back_elem--;
			if(back_elem == -1)
				back_elem = arr_capacity-1;
			arr_size--;
			if(arr_capacity > 1 && arr_size < arr_capacity/4) {
				set_capacity(arr_capacity/2);
			}
		}

		void pop_front() {
			front_elem++;
			if(front_elem == arr_capacity)
				front_elem = 0;
			arr_size--;
			if(arr_capacity > 1 && arr_size < arr_capacity/4) {
				set_capacity(arr_capacity/2);
			}
		}

		bool empty() {
			return (arr_size == 0);
		}

		int capacity() {
			return arr_capacity;
		}

		int size() {
			return arr_size;
		}

		T front() {
			return arr[front_elem];
		}

		T back() {
			return arr[back_elem];
		}

		~deque() {
			delete[] arr;
		}
	};
}