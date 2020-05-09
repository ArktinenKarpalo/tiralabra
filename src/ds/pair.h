#pragma once

namespace ds {

	// All functions behave similar to std::pair

	template<class T1, class T2>
	struct pair {
		T1 first;
		T2 second;
		pair(T1 first, T2 second) : first(first), second(second) {};
		pair() {};
	};

	template<class T1, class T2>
	ds::pair<T1, T2> make_pair(T1 first, T2 second) {
		return {first, second};
	}
}