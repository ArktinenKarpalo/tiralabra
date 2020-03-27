#pragma once

#include "node.h"

namespace ds {
	class Sub_expr {
	public:
		ds::Node *q, *f;

		Sub_expr() :q(new ds::Node()), f(new ds::Node()) {
		}

		Sub_expr(ds::Node *q, ds::Node *f) : q(q), f(f) {
		}
	};
}
