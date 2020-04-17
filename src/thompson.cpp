#include <utility>
#include <string>
#include <stack>
#include "thompson.h"
#include "ds/node_nfa.h"
#include "ds/sub_expr.h"
#include "preprocess.h"

#define EPSILON 0x01

Thompson::Thompson(std::string expr) {
	expr = Preprocess::add_concatenations(expr);
	expr = Preprocess::postfix(expr);
	thompson_nfa(expr);
}

// Construct a NFA with Thompson's construction from the given expression which is in postfix form and contains concatenations with symbol #
void Thompson::thompson_nfa(std::string expr) {
	// Thompson nfa from postfix
	std::stack<ds::Sub_expr*> stk;
	for(char cha : expr) {
		if(cha == '*') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex = new ds::Sub_expr();
			subex->q->addTrans(EPSILON, subex1->q);
			subex1->f->addTrans(EPSILON, subex1->q);
			subex1->f->addTrans(EPSILON, subex->f);
			subex->q->addTrans(EPSILON, subex->f);
			stk.push(subex);
			delete subex1;
		} else if(cha == '#') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex2 = stk.top();
			stk.pop();
			for(std::pair<char, ds::Node_nfa*> u : subex1->q->transitions_input())
				subex2->f->addTrans(u.first, u.second);
			delete subex1->q;
			subex1->q = subex2->f;
			ds::Sub_expr *subex = new ds::Sub_expr(subex2->q, subex1->f);
			stk.push(subex);
			delete subex1;
			delete subex2;
		} else if(cha == '|') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex2 = stk.top();
			stk.pop();
			ds::Sub_expr *subex = new ds::Sub_expr();
			subex->q->addTrans(EPSILON, subex1->q);
			subex->q->addTrans(EPSILON, subex2->q);
			subex1->f->addTrans(EPSILON, subex->f);
			subex2->f->addTrans(EPSILON, subex->f);
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
	initial = nfa->q;
	accept = nfa->f;
}

bool Thompson::matches(std::string input, int cur_ind, ds::Node_nfa *cur_node) {
	if(cur_ind == input.size()) {
		if(cur_node == accept)
			return true;
	}
	for(std::pair<char, ds::Node_nfa*> pa : cur_node->next(input[cur_ind])) {
		if(pa.first == EPSILON) {
			if(matches(input, cur_ind, pa.second))
				return true;
		} else if(cur_ind != input.size()) {
			if(matches(input, cur_ind+1, pa.second))
				return true;
		}
	}
	return false;
}

bool Thompson::match(std::string s) {
	return matches(s, 0, initial);
}

// Temporarily we use set to keep track
void Thompson::delete_nodes_rec(ds::Node_nfa *cur_node) {
	if(deleted_nodes.find(cur_node) != deleted_nodes.end())
		return;
	deleted_nodes.insert(cur_node);
	for(std::pair<char, ds::Node_nfa*> u : cur_node->transitions_input()) {
		delete_nodes_rec(u.second);
	}
	delete cur_node;
}

Thompson::~Thompson() {
	delete_nodes_rec(initial);
}