#pragma once

#include <string>
#include <iostream>

class Matcher {
	public:
		virtual bool match(std::string){};
		virtual ~Matcher(){};
};