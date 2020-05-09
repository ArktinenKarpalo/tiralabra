#include <string>

#include "thompson.h"
#include "ds/node_nfa.h"
#include "ds/sub_expr.h"
#include "ds/pair.h"
#include "ds/stack.h"
#include "ds/deque.h"
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
	ds::stack<ds::Sub_expr*> stk;
	bool ignore_next = false;
	for(char cha : expr) {
		if(cha == '\\') {
			ignore_next = true;
		} else if(!ignore_next && cha == '*') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Node_nfa *node1 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node1);
			ds::Node_nfa *node2 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node2);
			ds::Sub_expr *subex = new ds::Sub_expr(node1, node2);
			subex->q->addTrans(EPSILON, subex1->q);
			subex1->f->addTrans(EPSILON, subex1->q);
			subex1->f->addTrans(EPSILON, subex->f);
			subex->q->addTrans(EPSILON, subex->f);
			stk.push(subex);
			delete subex1;
		} else if(!ignore_next && cha == '#') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex2 = stk.top();
			stk.pop();
			for(ds::pair<char, ds::Node_nfa*> u : subex1->q->transitions_input())
				subex2->f->addTrans(u.first, u.second);
			nodes[subex1->q->id2] = nullptr;
			delete subex1->q;
			subex1->q = subex2->f;
			ds::Sub_expr *subex = new ds::Sub_expr(subex2->q, subex1->f);
			stk.push(subex);
			delete subex1;
			delete subex2;
		} else if(!ignore_next && cha == '|') {
			ds::Sub_expr *subex1 = stk.top();
			stk.pop();
			ds::Sub_expr *subex2 = stk.top();
			stk.pop();
			ds::Node_nfa *node1 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node1);
			ds::Node_nfa *node2 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node2);
			ds::Sub_expr *subex = new ds::Sub_expr(node1, node2);
			subex->q->addTrans(EPSILON, subex1->q);
			subex->q->addTrans(EPSILON, subex2->q);
			subex1->f->addTrans(EPSILON, subex->f);
			subex2->f->addTrans(EPSILON, subex->f);
			stk.push(subex);
			delete subex1;
			delete subex2;
		} else if(!ignore_next && cha == '.') {
			ds::Node_nfa *node1 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node1);
			ds::Node_nfa *node2 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node2);
			ds::Sub_expr *subex = new ds::Sub_expr(node1, node2);
			for(int chaa=33; chaa<127; chaa++) {
				subex->q->addTrans(chaa, subex->f);
			}
			stk.push(subex);
		} else {
			ds::Node_nfa *node1 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node1);
			ds::Node_nfa *node2 = new ds::Node_nfa(nodes.size());
			nodes.push_back(node2);
			ds::Sub_expr *subex = new ds::Sub_expr(node1, node2);
			subex->q->addTrans(cha, subex->f);
			stk.push(subex);
			ignore_next = false;
		}
	}
	ds::Sub_expr *nfa = stk.top();
	stk.pop();
	initial = nfa->q;
	accept = nfa->f;
	visited = new int[nodes.size()];
	delete nfa;
}

bool Thompson::match(std::string s) {
	for(int i=0; i<nodes.size(); i++)
		visited[i] = -1;
	ds::deque<ds::pair<ds::Node_nfa*, int>> dq;
	dq.push_back(ds::make_pair(initial, 0));
	while(!dq.empty()) {
		ds::Node_nfa *cur_node = dq.front().first;
		int cur_ind = dq.front().second;
		dq.pop_front();
		if(visited[cur_node->id2] == cur_ind)
			continue;
		visited[cur_node->id2] = cur_ind;
		if(cur_ind == s.size() && cur_node == accept)
			return true;
		for(ds::pair<char, ds::Node_nfa*> pa : cur_node->next(s[cur_ind])) {
			if(pa.first == EPSILON) {
				dq.push_front(ds::make_pair(pa.second, cur_ind));
			} else if(cur_ind != s.size()) {
				dq.push_back(ds::make_pair(pa.second, cur_ind+1));
			}
		}
	}
	return false;
}

Thompson::~Thompson() {
	for(auto node : nodes) {
		if(node != nullptr)
			delete node;
	}
	delete[] visited;
}