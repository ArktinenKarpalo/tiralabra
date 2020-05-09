#pragma once

#include <string>
#include <utility>
#include <filesystem>
#include <fstream>
#include "gtest/gtest.h"
#include <vector>
namespace utils {
	std::vector<std::string> readFile(std::string filename) {
		std::vector<std::string> v;
		std::ios::sync_with_stdio(false);
		std::ifstream fs(filename);
		auto size = std::filesystem::file_size(filename);
		std::string content(size, 0);
		fs.read(content.data(), size);
		std::string input = "";
		for(auto u:content) {
			if(u == ' ' || u == '\n') {
				v.push_back(input);
				input = "";
			} else {
				input.push_back(u);
			}
		}
		return v;
	}
}