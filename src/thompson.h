#pragma once
#include <string>
#include <utility>

#include "ds/node.h"

namespace Thompson {
	std::pair<ds::Node*, ds::Node*> thompson_nfa(std::string);
	bool matches(std::string, int, ds::Node*, ds::Node*);
}
