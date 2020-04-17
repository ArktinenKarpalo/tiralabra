#pragma once
#include <string>
#include "ds/node_nfa.h"
#include "ds/node_dfa.h"
#include "ds/matcher.h"

class Powerset : public Matcher {
	private:
		ds::Node_dfa **node = new ds::Node_dfa*[1<<24]{nullptr};
		void dfs_epsilon(ds::Node_nfa*);
		void dfs_erm(ds::Node_nfa*, ds::Node_dfa*);
		ds::Node_dfa *start;
		ds::Node_dfa* nfa_dfa(ds::Node_nfa*);
		int cur_id = 1;
		int cur_id2 = 129;
	public:
		Powerset(std::string);
		~Powerset();
		void nfaPowerset(ds::Node_nfa*, ds::Node_nfa*);
		bool match(std::string);
};
