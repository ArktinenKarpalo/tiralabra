#pragma once

#include "vector.h"

namespace ds {

	// All functions behave similar to std::stack

	template<class T>
	class stack {
		private:
		ds::vector<T> *v;
		public:

		stack() {
			v = new ds::vector<T>();
		}

		T top() {
			return (*v)[v->size()-1];
		}

		void push(T elem) {
			v->push_back(elem);
		}

		void pop() {
			v->pop_back();
		}

		unsigned int size() {
			return v->size();
		}

		bool empty() {
			return (v->size() == 0);
		}

		~stack() {
			delete v;
		}
	};
}