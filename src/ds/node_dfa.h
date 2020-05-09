#pragma once
#include "node_nfa.h"

namespace ds {
	class Node_dfa {
		private:
		public:
			int id; // Set of states this node contains, ith bit true = include transitions of ith state
			bool accept = false;
			int transition[128] = {0}; // Id of DFA node with input symbol

			Node_dfa(int id) : id(id) {
			}
			
			~Node_dfa() {
			}
	};
}