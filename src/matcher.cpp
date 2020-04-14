#include "matcher.h"
#include "preprocess.h"
#include "thompson.h"

// TODO: check if given expression is valid
bool matcher::match(std::string expr, std::string st) {
	expr = Preprocess::add_concatenations(expr);
	expr = Preprocess::postfix(expr);
	std::pair<ds::Node_nfa*, ds::Node_nfa*> nfa = Thompson::thompson_nfa(expr);

	return Thompson::matches(st, 0, nfa.first, nfa.second);
}
