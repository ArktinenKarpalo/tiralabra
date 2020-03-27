#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <queue>

#include "ds/node.h"
#include "ds/sub_expr.h"
#include "preprocess.h"
#include "thompson.h"
#include "matcher.h"


int main() {
	std::string expr, st;
	std::cin >> expr;
	std::cin >> st;
	std::cout << matcher::match(expr, st);
}
