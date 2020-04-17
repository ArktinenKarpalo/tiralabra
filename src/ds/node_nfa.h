#pragma once
#include <utility>
#include <vector>

#define EPSILON 0x01

namespace ds {
	struct Node_nfa {
		private:
			// With Thompson's construction, we can only get at most 2 transitions for each state
			std::pair<char, Node_nfa*> *d = new std::pair<char, Node_nfa*>[2];
			int transitions = 0;
		public:
			char in_eps = 1; // 1 = no transitions, 2 = Only epsilon transitions coming in
			char out_eps = 1; // 1 = no transitions, 2 = Only epsilon transitions coming out
			int visited1 = 0; // Temporarily used for powerset construction
			bool visited2 = false; // Temporarily used for powerset construction 

			int id = -1; // Temporarily used for powerset construction 

			void addTrans(char cha, Node_nfa* nod) {
				if(cha != EPSILON) {
					out_eps = 3;
					nod->in_eps = 3;
				} else {
					if(out_eps == 1)
						out_eps = 2;
					if(nod->in_eps == 1)
						nod->in_eps = 2;
				}
				d[transitions++] = std::make_pair(cha, nod);
			}

			std::vector<std::pair<char, Node_nfa*>> next(char cha) {
				std::vector<std::pair<char, Node_nfa*>> v;
				for(int i=0; i<transitions; i++) {
					if(d[i].first == EPSILON || d[i].first == cha)
							v.push_back(d[i]);
				}
				return v;
			}

			// Returns list of transitions
			std::vector<std::pair<char, Node_nfa*>> transitions_input() {
				std::vector<std::pair<char, Node_nfa*>> v;
				for(int i=0; i<transitions; i++)
					v.push_back(d[i]);
				return v;
			}

			~Node_nfa() {
				delete[] d;
			}
	};
}
