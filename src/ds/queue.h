#pragma once
#include <iostream>
#include "deque.h"

// Functions behave similar to std::queue

namespace ds {
	template<class T>
	class queue {
		private:
		ds::deque<T> *dq;

		public:
		queue() {
			dq = new ds::deque<T>();
		}

		T front() {
			return dq->front();
		}

		void push(T elem) {
			dq->push_back(elem);
		}

		void pop() {
			dq->pop_front();
		}

		bool empty() {
			return dq->empty();
		}

		~queue() {
			delete dq;
		}

	};
}