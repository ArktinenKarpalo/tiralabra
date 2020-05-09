#pragma once

#include <string>

class Matcher {
	public:
		virtual bool match(std::string){};
		virtual ~Matcher(){};
};