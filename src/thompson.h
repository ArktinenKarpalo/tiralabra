#pragma once
#include <string>
#include <set>

#include "ds/node_nfa.h"
#include "ds/matcher.h"

class Thompson : public Matcher {
	public:
		ds::Node_nfa *initial, *accept;
		Thompson(std::string);
		~Thompson();
		bool match(std::string);
	private:
		void thompson_nfa(std::string);
		bool matches(std::string, int, ds::Node_nfa*);
		void delete_nodes_rec(ds::Node_nfa*);
		std::set<ds::Node_nfa*> deleted_nodes;
};