#include "hopcroft.h"
#include "ds/hopcroft_block.h"
#include "ds/hopcroft_state.h"
#include "ds/node_dfa.h"
#include "ds/vector.h"
#include "ds/pair.h"
#include "ds/stack.h"
#include "ds/queue.h"
#include "powerset.h"

Hopcroft::Hopcroft(Powerset* ps) {
	auto p = preprocess_ps(ps);
	process(p.first, p.second);
}

// Split the given state from inital block to the new block
void Hopcroft::split_state(ds::Hopcroft_block *block_old, ds::Hopcroft_state *state, ds::Hopcroft_block *block_new, int input_symbol, ds::stack<ds::Hopcroft_block*> *blocks_empty) {
	block_old->transitions -= state->transition_sum;
	block_new->transitions += state->transition_sum;

	block_new->states.splice(block_new->states.end(), block_old->states, state->iter);
	state->block = block_new;
}

void Hopcroft::process(ds::vector<ds::Hopcroft_block*> *blocks, ds::Hopcroft_state *initial) {
	ds::stack<ds::Hopcroft_block*> blocks_empty; // We re-use empty blocks to save memory
	int split_iteration = 1;
	ds::queue<ds::pair<ds::Hopcroft_block*, char>> blocks_process;
	for(ds::Hopcroft_block* block : *blocks) {
		block->transitions = 0;
		for(int i=0; i<128; i++) {
			block->process[i] = true;
			blocks_process.push(ds::make_pair(block, (char)i));
		}
		for(auto state : block->states) {
			state->transition_sum = 0;
			for(int i=0; i<128; i++) {
				state->transition_sum += state->transitions[i].size();
			}
			block->transitions += state->transition_sum;
		}
	}
	while(!blocks_process.empty()) {
		ds::Hopcroft_block *cur_block = blocks_process.front().first;
		char cur_symbol = blocks_process.front().second;
		blocks_process.pop();
		if(!cur_block->process[cur_symbol])
			continue;
		cur_block->process[cur_symbol] = false;
		ds::stack<ds::Hopcroft_state*> cur_block_split;
		ds::stack<ds::pair<ds::Hopcroft_block*, ds::Hopcroft_block*>> splits;
		for(ds::Hopcroft_state *block_state : cur_block->states) {
			for(ds::Hopcroft_state *transition_state : block_state->transitions[cur_symbol]) {
				if(transition_state->block->block_split.first != split_iteration) {
					ds::Hopcroft_block *split_block;
					if(!blocks_empty.empty()) {
						split_block = blocks_empty.top();
						blocks_empty.pop();
					} else {
						split_block = new ds::Hopcroft_block(blocks->size());
						blocks->push_back(split_block);
					}
					transition_state->block->block_split = ds::make_pair(split_iteration, split_block);

					split_block->accept = transition_state->block->accept;

					for(int i=0; i<128; i++)
						split_block->process[i] = false;
					splits.push(ds::make_pair(transition_state->block, split_block));
				}
				if(transition_state->block == cur_block) {
					// We split this state later from the block, because we may iterate over this block later on
					cur_block_split.push(transition_state);
				} else {
					split_state(transition_state->block, transition_state, transition_state->block->block_split.second, cur_symbol, &blocks_empty);
				}
			}
		}
		while(!cur_block_split.empty()) {
			ds::Hopcroft_state *transition_state = cur_block_split.top();
			split_state(transition_state->block, transition_state, transition_state->block->block_split.second, cur_symbol, &blocks_empty);
			cur_block_split.pop();
		}
		// We iterate all the block splits that we performed, and mark the block with smaller amount of transitions to be processed to achieve n log n for each input symbol
		while(!splits.empty()) {
			ds::Hopcroft_block* block1 = splits.top().first;
			ds::Hopcroft_block* block2 = splits.top().second;
			splits.pop();
			if(block1->transitions < block2->transitions) {
				for(int j=0; j<128; j++) {
					if(block1->process[j]) {
						block2->process[j] = true;
						blocks_process.push(ds::make_pair(block2, (char)j));
					}
					if(block1->transitions != 0) {
						block1->process[j] = true;
						blocks_process.push(ds::make_pair(block1, (char)j));
					}
				}
				if(block1->states.size() == 0) {
					blocks_empty.push(block1);
				}
			} else {
				if(block2->states.size() == 0) {
					blocks_empty.push(block2);
					continue;
				}
				for(int j=0; j<128; j++) {
					block2->process[j] = true;
					blocks_process.push(ds::make_pair(block2, (char)j));
				}
			}
		}
		split_iteration++;
	}
	// Now all DFA equivalent states should be in the same block
	nodes = blocks->size()+1;
	node = new ds::Node_dfa*[nodes]{nullptr};
	for(ds::Hopcroft_block *block : *blocks) {
		if(block->states.empty()) { // We may have empty blocks
			continue;
		}
		if(node[block->id+1] == nullptr) 
			node[block->id+1] = new ds::Node_dfa(block->id+1);
		if(block->accept)
			node[block->id+1]->accept = true;
		for(ds::Hopcroft_state *state : block->states) {
			for(int i=0; i<128; i++ ) {
				for(ds::Hopcroft_state *reversed_transition : state->transitions[i]) {
					if(node[reversed_transition->block->id+1] == nullptr) 
						node[reversed_transition->block->id+1] = new ds::Node_dfa(reversed_transition->block->id+1);
					node[reversed_transition->block->id+1]->transition[i] = block->id+1;
				}
			}
			if(state == initial) {
				start = node[block->id+1];
			}
		}
	}

	// Count nodes of minimized dfa for testing purposes
	bool *visited = new bool[nodes]{0};
	ds::queue<ds::Node_dfa*> q;
	q.push(start);
	dfa_states = 0;
	while(!q.empty()) {
		ds::Node_dfa *cur = q.front();
		q.pop();
		if(visited[cur->id]) {
			continue;
		}
		visited[cur->id] = true;
		for(int i=0; i<128; i++) {
			if(cur->transition[i]) {
				q.push(node[cur->transition[i]]);
			}
		}
		dfa_states++;
	}
	delete[] visited;

	for(int i=0; i<blocks->size(); i++) {
		delete (*blocks)[i];
	}
	for(int i=0; i<states_len; i++) {
		delete states[i];
	}
	delete[] states;
	delete blocks;
}

ds::pair<ds::vector<ds::Hopcroft_block*>*, ds::Hopcroft_state*> Hopcroft::preprocess_ps(Powerset* ps) {
	states = new ds::Hopcroft_state*[ps->nodes]{nullptr};
	states_len = ps->nodes;
	ds::vector<ds::Hopcroft_block*> *blocks = new ds::vector<ds::Hopcroft_block*>();
	blocks->push_back(new ds::Hopcroft_block(0));
	blocks->push_back(new ds::Hopcroft_block(1));
	
	(*blocks)[1]->accept = true;
	ds::Hopcroft_state *initial;
	for(int i=1; i<ps->nodes; i++) {
		if(ps->node[i] == nullptr)
			continue; 
		
		if(states[ps->node[i]->id] == nullptr) {
			states[ps->node[i]->id] = new ds::Hopcroft_state();
			if(ps->node[i] == ps->start)
				initial = states[ps->node[i]->id]; 
		}

		for(int j=0; j<128; j++) {
			if(ps->node[i]->transition[j]) {
				if(ps->node[ps->node[i]->transition[j]] == nullptr)
					continue;
				if(states[ps->node[i]->transition[j]] == nullptr) {
					states[ps->node[i]->transition[j]] = new ds::Hopcroft_state();
					if(ps->node[ps->node[i]->transition[j]] == ps->start)
						initial = states[ps->node[i]->transition[j]]; 
				}
				states[ps->node[i]->transition[j]]->transitions[j].push_back(states[ps->node[i]->id]);
			}
		}
		if(ps->node[i]->accept) {
			(*blocks)[1]->states.push_front(states[ps->node[i]->id]);
			states[ps->node[i]->id]->iter = (*blocks)[1]->states.begin();
			states[ps->node[i]->id]->block = (*blocks)[1];
		} else {
			(*blocks)[0]->states.push_front(states[ps->node[i]->id]);
			states[ps->node[i]->id]->iter = (*blocks)[0]->states.begin();
			states[ps->node[i]->id]->block = (*blocks)[0];
		}
	}
	
	// We may sometimes have only accepting states, as we don't have ending state, but instead end match search manually when the transition state id is 0
	if((*blocks)[0]->states.size() == 0) {
		(*blocks)[0]->accept = true;
		(*blocks)[0]->states.push_back((*blocks)[1]->states.back());
		(*blocks)[0]->states.back()->iter = (*blocks)[0]->states.begin();
		(*blocks)[0]->states.back()->block = (*blocks)[0];
		(*blocks)[1]->states.pop_back();
	}

	return ds::make_pair(blocks, initial);
}

bool Hopcroft::match(std::string input) {
	ds::Node_dfa *cur_node = start;
	for(int i=0; i<input.size(); i++) {
		if(input[i] < 32 || input[i] > 127)
			return false;
		if(cur_node->transition[input[i]] == 0) {
			return false;
		} else {
			cur_node = node[cur_node->transition[input[i]]];
		}
	}
	return cur_node->accept;
}

Hopcroft::~Hopcroft() {
	for(int i=0; i<nodes; i++)
		if(node[i] != nullptr)
			delete node[i];
	delete[] node;
}