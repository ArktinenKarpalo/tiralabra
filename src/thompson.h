#pragma once
#include <string>

#include "ds/node_nfa.h"
#include "ds/matcher.h"
#include "ds/vector.h"

class Thompson : public Matcher {
	public:
		ds::Node_nfa *initial, *accept;
		Thompson(std::string);
		~Thompson();
		bool match(std::string);
	private:
		ds::vector<ds::Node_nfa*> nodes;
		void thompson_nfa(std::string);
		bool matches(std::string, int, ds::Node_nfa*, bool*);
		void delete_nodes_rec(ds::Node_nfa*);
		int *visited;
};