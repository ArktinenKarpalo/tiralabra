#pragma once
#include <string>
#include <utility>

#include "ds/node_nfa.h"

namespace Thompson {
	std::pair<ds::Node_nfa*, ds::Node_nfa*> thompson_nfa(std::string);
	bool matches(std::string, int, ds::Node_nfa*, ds::Node_nfa*);
}
