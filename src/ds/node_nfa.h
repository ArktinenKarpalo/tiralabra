#pragma once

#include "ds/pair.h"
#include "ds/vector.h"

#define EPSILON 0x01

namespace ds {
	struct Node_nfa {
		private:
			// With Thompson's construction, we can only get at most 2 transitions for each state, but we have modified version with ., which may produce more transitions
			//ds::pair<char, Node_nfa*> *d = new ds::pair<char, Node_nfa*>[2];
			ds::vector<ds::pair<char, Node_nfa*>> *d = new ds::vector<ds::pair<char, Node_nfa*>>();
			int transitions = 0;
		public:
			char in_eps = 1; // 1 = no transitions, 2 = Only epsilon transitions coming in
			char out_eps = 1; // 1 = no transitions, 2 = Only epsilon transitions coming out
			int visited1 = 0; // Temporarily used for powerset construction
			bool visited2 = false; // Temporarily used for powerset construction 

			int id = -1; // Temporarily used for powerset construction 
			int id2; // used for nfa

			Node_nfa(int id1) : id2(id1) {
			}

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
				d->push_back(ds::make_pair(cha, nod));
				transitions++;
				//d[transitions++] = ds::make_pair(cha, nod);
			}

			ds::vector<ds::pair<char, Node_nfa*>> next(char cha) {
				ds::vector<ds::pair<char, Node_nfa*>> v;
				for(int i=0; i<transitions; i++) {
					if((*d)[i].first == EPSILON || (*d)[i].first == cha)
						v.push_back((*d)[i]);
				}
				return v;
			}

			// Returns list of transitions
			ds::vector<ds::pair<char, Node_nfa*>> transitions_input() {
				ds::vector<ds::pair<char, Node_nfa*>> v;
				for(int i=0; i<transitions; i++)
					v.push_back((*d)[i]);
				return v;
			}

			~Node_nfa() {
				delete d;
				//delete[] d;
			}
	};
}
