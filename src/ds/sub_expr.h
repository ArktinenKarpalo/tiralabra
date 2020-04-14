#pragma once

#include "node_nfa.h"

namespace ds {
	class Sub_expr {
	public:
		ds::Node_nfa *q, *f;

		Sub_expr() : q(new ds::Node_nfa()), f(new ds::Node_nfa()) {
		}

		Sub_expr(ds::Node_nfa *q, ds::Node_nfa *f) : q(q), f(f) {
		}
	};
}
