#pragma once
#include <string>

#include "ds/node_dfa.h"
#include "ds/hopcroft_block.h"
#include "ds/hopcroft_state.h"
#include "ds/matcher.h"
#include "ds/pair.h"
#include "ds/vector.h"
#include "ds/stack.h"
#include "powerset.h"

class Hopcroft : public Matcher {
	public:
		Hopcroft(Powerset*);
		bool match(std::string);
		~Hopcroft();
		int dfa_states;
	private:
		ds::Node_dfa *start;
		ds::Node_dfa **node;
		int nodes;
		ds::pair<ds::vector<ds::Hopcroft_block*>*, ds::Hopcroft_state*> preprocess_ps(Powerset*);
		void process(ds::vector<ds::Hopcroft_block*>*, ds::Hopcroft_state*);
		void split_state(ds::Hopcroft_block*, ds::Hopcroft_state*, ds::Hopcroft_block*, int, ds::stack<ds::Hopcroft_block*>*);
		ds::Hopcroft_state **states;
		int states_len;
};