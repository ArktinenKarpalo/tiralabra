#include <iostream>
#include "powerset.h"
#include "preprocess.h"
#include "thompson.h"
#include "ds/node_nfa.h"
#include "ds/node_dfa.h"

#define EPSILON 0x01

Powerset::Powerset(std::string expr) {
	Thompson* t = new Thompson(expr);
	this->nfaPowerset(t->initial, t->accept);
	delete t;
}

// Generate initial DFA nodes for powerset construction from the NFA
void Powerset::dfs_epsilon(ds::Node_nfa *cur_node) {
	if(cur_node->visited2)
		return;
	cur_node->visited2 = true;
	if(cur_node->in_eps != 2 && cur_node->in_eps != 2)
		Powerset::dfs_erm(cur_node, Powerset::nfa_dfa(cur_node));
	for(std::pair<char, ds::Node_nfa*> u : cur_node->transitions_input()) {
		dfs_epsilon(u.second);
	}
}

// Return the corresponding DFA node for the given NFA node
ds::Node_dfa* Powerset::nfa_dfa(ds::Node_nfa *node) {
	if(node->id == -1) {
		if(node->in_eps != 2 && node->in_eps != 2) {
			node->id = cur_id;
			this->node[cur_id] = new ds::Node_dfa(cur_id);
			cur_id *= 2;
		} else {
			node->id = cur_id2;
			this->node[cur_id2] = new ds::Node_dfa(cur_id2);
			cur_id2++;
		}
	}
	return this->node[node->id];
}

// Find the epsilon closure of the NFA node and add transitions to DFA node corresponding the NFA node
void Powerset::dfs_erm(ds::Node_nfa *cur_node, ds::Node_dfa *cnode) {
	if(cur_node->visited1 == cnode->id)
		return;
	cur_node->visited1 = cnode->id;
	for(std::pair<char, ds::Node_nfa*> u : cur_node->transitions_input()) {
		if(u.first == EPSILON) {
			if(nfa_dfa(u.second)->accept) {
				cnode->accept = true;
			}
			dfs_erm(u.second, cnode);
		} else {
			cnode->transition[u.first] |= nfa_dfa(u.second)->id;
		}
	}
}

void Powerset::nfaPowerset(ds::Node_nfa *initial, ds::Node_nfa *accept) {
	accept->id = cur_id2;
	node[cur_id2] = new ds::Node_dfa(cur_id2);
	node[cur_id2]->accept = true;
	cur_id2++;
	dfs_epsilon(initial);

	// Remove DFA inaccessible nodes
	for(int i=cur_id2-1; i>=129; i--) {
		delete node[i];
		node[i] = nullptr;
	}

	// For now we generate every combination, even ones that we can't visit
	for(int i=1; i<=cur_id; i++) {
		if(node[i] == nullptr) {
			node[i] = new ds::Node_dfa(i);
			for(int j=1; j<=cur_id; j *= 2) {
				if((i & j)) {
					if(node[j]->accept)
						node[i]->accept = true;
					for(int k=0; k<128; k++) {
						node[i]->transition[k] |= node[j]->transition[k];
					}
				}
			}
		}
	}
	Powerset::start = node[initial->id];
}

bool Powerset::match(std::string input) {
	ds::Node_dfa *cur_node = Powerset::start;
	for(int i=0; i<input.size(); i++) {
		if(cur_node->transition[input[i]] == 0) {
			return false;
		} else {
			cur_node = Powerset::node[cur_node->transition[input[i]]];
		}
	}
	if(cur_node->accept)
		return true;
	else
		return false;
}

Powerset::~Powerset() {
	for(int i=0; i<(1<<24); i++) {
		delete node[i];
	}
	delete[] node;
}