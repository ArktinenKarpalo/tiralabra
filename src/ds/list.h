#pragma once
#include <iterator>
#define END nullptr

namespace ds {
	// Similar to std::list with time complexities

	template<class T>
	struct list_node {
		list_node *next, *prev;
		T elem;
		list_node(T elem) : elem(elem) {
			next = nullptr;
			prev = nullptr;
		};
	};

	template<class T>
	class list {
		public:
		private:
		list_node<T> *first, *last;
		int list_size;
		public:
		list() {
			first = nullptr;
			last = nullptr;
			list_size = 0;
		}

		struct iterator {

			typedef T value_type;
			typedef T* pointer;
			typedef T& reference;
			typedef std::forward_iterator_tag iterator_category;

			list_node<T> *node;
			iterator(list_node<T> *node) : node(node) {
			}
			iterator() {};

			iterator& operator++() {
				node = node->next;
				return *this;
			}

			T operator*() {
				return node->elem;
			}

			bool operator==(iterator it) {
				return it.node == node;
			}

			bool operator!=(iterator it) {
				return it.node != node;
			}
		};

		void push_back(T elem) {
			list_node<T> *node = new list_node<T>(elem);
			if(list_size++ == 0) {
				first = node;
			} else {
				last->next = node;
				node->prev = last;
			}
			last = node;
		}

		void push_front(T elem) {
			list_node<T> *node = new list_node<T>(elem);
			if(list_size++ == 0) {
				last = node;
			} else {
				first->prev = node;
				node->next = first;
			}
			first = node;
		}

		void pop_back() {
			list_node<T> *old = last;
			if(list_size-- != 1) {
				last->prev->next = nullptr;
				last = last->prev;
				if(list_size == 1)
					first = last;
			} else {
				last = nullptr;
				first = nullptr;
			}
			delete old;
		}

		void pop_front() {
			list_node<T> *old = first;
			if(list_size-- != 1) {
				first->next->prev = nullptr;
				first = first->next;
				if(list_size == 1)
					last = first;
			} else {
				last = nullptr;
				first = nullptr;
			}
			delete old;
		}

		// Removes the node from the list without deleting the node itself
		void remove(iterator it) {
			if(it.node == first) {
				if(list_size-- != 1) {
					if(first->next != nullptr)
						first->next->prev = nullptr;
					first = first->next;
				} else {
					first = nullptr;
					last = nullptr;
				}
			} else if(it.node == last) {
				if(list_size-- != 1) {
					if(last->prev != nullptr)
						last->prev->next = nullptr;
					last = last->prev;
				} else {
					first = nullptr;
					last = nullptr;
				}
			} else {
				it.node->next->prev = it.node->prev;
				it.node->prev->next = it.node->next;
				list_size--;
			}
			it.node->prev = nullptr;
			it.node->next = nullptr;
		}

		// Move it from list other to this list before pos
		void splice(iterator pos, list &other, iterator it) {
			other.remove(it);
			if(pos == END) {
				if(list_size == 0) {
					first = it.node;
					it.node->prev = nullptr;
				} else {
					last->next = it.node;
					it.node->prev = last;
				}
				it.node->next = nullptr;
				last = it.node;
				list_size++;
			} else if(pos.node == first) {
				first->prev = it.node;
				it.node->next = first;
				it.node->prev = nullptr;
				first = it.node;
				list_size++;
			} else {
				pos.node->prev->next = it.node;
				pos.node->prev = it.node;
				it.node->prev = pos.node->prev;
				it.node->next = pos.node;
				list_size++;
			}
		}

		T front() {
			return first->elem;
		}

		T back() {
			return last->elem;
		}

		iterator begin() {
			return first;
		}

		iterator end() {
			return nullptr;
		}

		int size() {
			return list_size;
		}

		bool empty() {
			return (list_size == 0);
		}

		~list() {
			list_node<T> *node = first;
			while(node != nullptr) {
				list_node<T> *prev = node;
				node = prev->next;
				delete prev;
			}
		}
	};
}