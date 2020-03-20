#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <stack>
#include <queue>

struct sub_expr;
struct node;

struct node {
	std::vector<std::pair<char, node*>> d;

	void addTrans(char cha, node* nod) {
		d.push_back(std::make_pair(cha, nod));
	}

	// ? = epsilon for now
	std::vector<std::pair<char, node*>> next(char cha) {
		std::vector<std::pair<char, node*>> v;
		for(int i=0; i<d.size(); i++) {
			if(d[i].first == '?' || d[i].first == cha) {
				v.push_back(d[i]);
			}
		}
		return v;
	}

};

struct sub_expr {
	node *q, *f;
	sub_expr() :q(new node()), f(new node()) {
	}

	sub_expr(node *q, node *f) : q(q), f(f) {
	}
};

std::queue<char> postfix(std::string expr) {
	std::queue<char> q;
	std::stack<char> stk2;
	
	// TODO: Support empty expressions
	// Concatenation must be given in expr for now as '#'

	expr = "(" + expr + ")";
	// For now, convert to postfix with Shunting-yard
	for(int i=0; i<expr.size(); i++) {
		if(expr[i] == '(') {
			stk2.push('(');
		} else if(expr[i] == ')') {
			while(stk2.top() != '(') {
				q.push(stk2.top());
				stk2.pop();
			}
			stk2.pop(); // Pop (
		} else if(expr[i] == '*') {
			q.push('*');
		} else if(expr[i] == '|') {
			while(stk2.size() > 0 && (stk2.top() == '*' || stk2.top() == '#')) {
				q.push(stk2.top());
				stk2.pop();
			}
			stk2.push('|');
		} else if(expr[i] == '#') {
			while(stk2.size() > 0 && (stk2.top() == '*')) {
				q.push(stk2.top());
				stk2.pop();
			}
			stk2.push('#');
		} else {
			q.push(expr[i]);
		}
		std::cout << expr[i];
	}
	return q;

}

bool matches(std::string input, int cur_ind, node *cur_node, node *accept_node) {
	if(cur_ind == input.size()) {
		if(cur_node == accept_node)
			return true;
		else
			return false;
	}
	for(std::pair<char, node*> pa : cur_node->next(input[cur_ind])) {
		if(pa.first == '?') {
			if(matches(input, cur_ind, pa.second, accept_node))
				return true;
		} else {
			if(matches(input, cur_ind+1, pa.second, accept_node))
				return true;
		}
	}
	return false;
}

int main() {
	std::string expr;
	std::cin >> expr;

	std::queue<char> q = postfix(expr);

	// Thompson nfa from postfix
	std::stack<sub_expr*> stk;
	while(q.size() > 0) {
		if(q.front() == '*') {
			sub_expr *subex1 = stk.top();
			stk.pop();
			sub_expr *subex = new sub_expr();
			subex->q->addTrans('?', subex1->q);
			subex1->f->addTrans('?', subex1->q);
			subex1->f->addTrans('?', subex->f);
			subex->q->addTrans('?', subex->f);
			stk.push(subex);
			delete subex1;
		} else if(q.front() == '#') {
			sub_expr *subex1 = stk.top();
			stk.pop();
			sub_expr *subex2 = stk.top();
			stk.pop();
			sub_expr *subex = new sub_expr(subex2->q, subex1->f);
			subex2->f->addTrans('?', subex1->q);
			stk.push(subex);
			delete subex1;
			delete subex2;
		} else if(q.front() == '|') {
			sub_expr *subex1 = stk.top();
			stk.pop();
			sub_expr *subex2 = stk.top();
			stk.pop();
			sub_expr *subex = new sub_expr();
			subex->q->addTrans('?', subex1->q);
			subex->q->addTrans('?', subex2->q);
			subex1->f->addTrans('?', subex->f);
			subex2->f->addTrans('?', subex->f);
			stk.push(subex);
			delete subex1;
			delete subex2;
		} else {
			sub_expr *subex = new sub_expr();
			subex->q->addTrans(q.front(), subex->f);
			stk.push(subex);
		}
		std::cout << q.front() << std::flush;
		q.pop();
	}

	sub_expr *nfa = stk.top();
	stk.pop();
	std::string st;
	std::cin >> st;
	std::cout << matches(st, 0, nfa->q, nfa->f);
}
