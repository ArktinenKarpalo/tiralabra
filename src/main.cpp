#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>

#include "thompson.h"
#include "powerset.h"
#include "ds/matcher.h"

void printHelp() {
	std::cout << "Usage:\n"
		<< "./tiralabra_run i - Interactive mode\n"
		<< "./tiralabra_run expr <nfa/dfa> <filename> - Print words from the file that match the given expression, using nfa or dfa" << std::endl;
}

void interactive() {
	Matcher *m = nullptr;
	std::cout << "expr <expr> <dfa/nfa> - set expression\n"
		<< "<string> - check if the string matches the given expression\n"
		<< "quit - quit" << std::endl;
	while(true) {
		std::string cmd;
		std::cin >> cmd;
		if(cmd == "expr") {
			std::string expr;
			std::cin >> expr;
			std::string type;
			std::cin >> type;
			std::cout << "generating, please wait..." << std::endl;
			if(m != nullptr)
				delete m;
			if(type == "nfa") {
				m = new Thompson(expr);
			} else if(type == "dfa") {
				m = new Powerset(expr);
			}
			std::cout << "done" << std::endl;
		} else if(cmd == "quit") {
			break;
		} else {
			std::cout << "matching, please wait..." << std::endl;
			if(m->match(cmd)) {
				std::cout << "match" << std::endl;
			} else {
				std::cout << "no match" << std::endl;
			}
		}
	}
	if(m != nullptr)
		delete m;
}

void solveFile(std::string filename, Matcher *m) {
	std::ios::sync_with_stdio(false);
	std::ifstream fs(filename);
	auto size = std::filesystem::file_size(filename);
	std::string content(size, 0);
	fs.read(content.data(), size);
	std::string input = "";
	for(auto u:content) {
		if(u == ' ' || u == '\n') {
			if(m->match(input)) {
				std::cout << input << "\n";
			}
			input = "";
		} else {
			input.push_back(u);
		}
	}
}

int main(int argc, char **argv) {
	if(argc == 2) {
		if(std::string(argv[1]) == "i") {
			interactive();
		} else {
			printHelp();
		}
	} else if(argc == 4) {
		std::string expr = argv[1];
		std::string filename = argv[3];
		Matcher *m;
		if(std::string(argv[2]) == "nfa") {
			m = new Thompson(expr);
			solveFile(filename, m);
			delete m;
		} else if(std::string(argv[2]) == "dfa") {
			m = new Powerset(expr);
			solveFile(filename, m);
			delete m;
		} else {
			printHelp();
		}
	} else {
		printHelp();
	}
}
