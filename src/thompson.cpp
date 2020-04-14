#include <utility>
#include <string>
#include <stack>
#include "thompson.h"
#include "ds/node_nfa.h"
#include "ds/sub_expr.h"

// Convert postfix notation regex to NFA with Thompson's construction
// Returns start state and accepting state
std::pair<ds::Node_nfa*, ds::Node_nfa*> Thompson::thompson_nfa(std::string expr) {
	// Thompson nfa from postfix
	std::stack<ds::Sub_expr*> stk;
	for(char cha : expr) {
		if(cha == '*') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex = new ds::Sub_expr();
			subex->q->addTrans('?', subex1->q);
			subex1->f->addTrans('?', subex1->q);
			subex1->f->addTrans('?', subex->f);
			subex->q->addTrans('?', subex->f);
			stk.push(subex);
			delete subex1;
		} else if(cha == '#') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex2 = stk.top();
			stk.pop();
			ds::Sub_expr *subex = new ds::Sub_expr(subex2->q, subex1->f);
			subex2->f->addTrans('?', subex1->q);
			stk.push(subex);
			delete subex1;
			delete subex2;
		} else if(cha == '|') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex2 = stk.top();
			stk.pop();
			ds::Sub_expr *subex = new ds::Sub_expr();
			subex->q->addTrans('?', subex1->q);
			subex->q->addTrans('?', subex2->q);
			subex1->f->addTrans('?', subex->f);
			subex2->f->addTrans('?', subex->f);
			stk.push(subex);
			delete subex1;
			delete subex2;
		} else {
			ds::Sub_expr *subex = new ds::Sub_expr();
			subex->q->addTrans(cha, subex->f);
			stk.push(subex);
		}
	}
	ds::Sub_expr *nfa = stk.top();
	stk.pop();
	return std::make_pair(nfa->q, nfa->f);
}

bool Thompson::matches(std::string input, int cur_ind, ds::Node_nfa *cur_node, ds::Node_nfa *accept_node) {
	if(cur_ind == input.size()) {
		if(cur_node == accept_node)
			return true;
	}
	for(std::pair<char, ds::Node_nfa*> pa : cur_node->next(input[cur_ind])) {
		if(pa.first == '?') {
			if(matches(input, cur_ind, pa.second, accept_node))
				return true;
		} else if(cur_ind != input.size()) {
			if(matches(input, cur_ind+1, pa.second, accept_node))
				return true;
		}
	}
	return false;
}
