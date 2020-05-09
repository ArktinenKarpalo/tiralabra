#include <string>

#include "preprocess.h"
#include "ds/node_nfa.h"
#include "ds/stack.h"

// Preprocess expression to add concatenations
std::string Preprocess::add_concatenations(std::string expr) {
	std::string expr_c = "";

	bool conc = false;
	bool ignore_next = false;
	for(char cha : expr) {
		if(!ignore_next && cha == '\\') {
			if(conc)
				expr_c.push_back('#');
			ignore_next = true;
			expr_c.push_back(cha);
		} else if(!ignore_next && cha == '*') {
			expr_c.push_back(cha);
		} else if(!ignore_next && cha == '(') {
			if(conc)
				expr_c.push_back('#');
			conc = false;
			expr_c.push_back(cha);
		} else if(!ignore_next && cha == ')') {
			expr_c.push_back(cha);
		} else if(!ignore_next && cha == '|') {
			conc = false;
			expr_c.push_back(cha);
		} else {
			if(!ignore_next && conc)
				expr_c.push_back('#');
			expr_c.push_back(cha);
			conc = true;
			ignore_next = false;
		}
	}

	return expr_c;
}

// Uses shunting-yard algorithm to convert the expression into postfix notation for easier processing
std::string Preprocess::postfix(std::string expr) {
	std::string pf = "";
	ds::stack<char> stk2;

	expr = "(" + expr + ")";
	for(int i=0; i<expr.size(); i++) {
		if(expr[i] == '(') {
			stk2.push('(');
		} else if(expr[i] == ')') {
			while(stk2.top() != '(') {
				pf.push_back(stk2.top());
				stk2.pop();
			}
			stk2.pop(); // Pop (
		} else if(expr[i] == '*') {
			pf.push_back('*');
		} else if(expr[i] == '|') {
			while(stk2.size() > 0 && (stk2.top() == '*' || stk2.top() == '#')) {
				pf.push_back(stk2.top());
				stk2.pop();
			}
			stk2.push('|');
		} else if(expr[i] == '#') {
			while(stk2.size() > 0 && (stk2.top() == '*')) {
				pf.push_back(stk2.top());
				stk2.pop();
			}
			stk2.push('#');
		} else {
			pf.push_back(expr[i]);
		}
	}
	return pf;
}
