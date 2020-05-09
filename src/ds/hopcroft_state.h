#pragma once

#include "ds/list.h"
#include "ds/vector.h"

namespace ds {

	class Hopcroft_block;
	class Hopcroft_state {
		public:
			ds::Hopcroft_block* block; // Block that the state belongs to
			ds::list<ds::Hopcroft_state*>::iterator iter; // Iterator to list of block, containing this state
			ds::vector<Hopcroft_state*> transitions[128]; // DFA's transitions reversed
			int transition_sum = 0; // Pre-calculated amount of transitions from the state
		private:
	};
}