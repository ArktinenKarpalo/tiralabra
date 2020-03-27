#pragma once
#include <utility>
#include <vector>

namespace ds {
	struct Node {
		std::vector<std::pair<char, Node*>> d;

		void addTrans(char cha, Node* nod) {
			d.push_back(std::make_pair(cha, nod));
		}

		// ? = epsilon for now
		std::vector<std::pair<char, Node*>> next(char cha) {
			std::vector<std::pair<char, Node*>> v;
			for(int i=0; i<d.size(); i++) {
				if(d[i].first == '?' || d[i].first == cha) {
					v.push_back(d[i]);
				}
			}
			return v;
		}

	};
}
