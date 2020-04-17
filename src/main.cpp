#include <string>
#include <iostream>
#include <memory>

#include "thompson.h"
#include "powerset.h"


int main() {
	std::string expr, st;
	std::cin >> expr;
	std::cin >> st;
	std::unique_ptr<Thompson> t(new Thompson(expr));
	std::cout << t->match(st);
}
