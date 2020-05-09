#pragma once

#include "ds/list.h"
#include "ds/pair.h"

namespace ds {
	class Hopcroft_state;
	class Hopcroft_block {
		public:
			int id;
			bool accept = false;
			ds::pair<int, Hopcroft_block*> block_split = {0, nullptr}; // Which block to split from this block during the current split iteration
			int transitions = 0; // How many transitions with the current input symbol
			ds::list<Hopcroft_state*> &states = *new ds::list<Hopcroft_state*>;
			bool process[128];
			Hopcroft_block(int id): id(id){};
			~Hopcroft_block() {
				delete &states;
			}
		private:
	};
}