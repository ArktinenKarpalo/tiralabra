#pragma once
#include <utility>
#include <vector>
#include <iostream>

namespace ds {
	struct Node_nfa {
		private:
			// With Thompson's construction, we can only get at most 2 transitions out of the node
			std::pair<char, Node_nfa*> *d = new std::pair<char, Node_nfa*>[2];
			int transitions = 0;
		public:
			void addTrans(char cha, Node_nfa* nod) {
				if(transitions++)
					d[1] = std::make_pair(cha, nod);
				else
					d[0] = std::make_pair(cha, nod);
			}

			// ? = epsilon for now
			std::vector<std::pair<char, Node_nfa*>> next(char cha) {
				std::vector<std::pair<char, Node_nfa*>> v;
				if(transitions) {
					for(int i=0; i<2; i++) {
						if(d[i].first == '?' || d[i].first == cha)
							v.push_back(d[i]);
					}
				} else {
					if(d[0].first == '?' || d[0].first == cha)
						v.push_back(d[0]);
				}
				return v;
			}

			~Node_nfa() {
				delete d;
			}
	};
}
