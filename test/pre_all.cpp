#include <string>
#include <utility>
#include <fstream>
#include "powerset.h"
#include "gtest/gtest.h"
#include "ds/node_nfa.h"
#include "ds/matcher.h"
#include "thompson.h"
#include "hopcroft.h"

// Test all combinations of letters ABCD between length 0 and len, reading the expected result (true or false) from the file
void testall(std::ifstream *fs, Matcher *matcher, std::string *s, int len) {
	if(s->size() == len)
		return;
	for(int i='A'; i<='D'; i++) {
		s->push_back(i);
		char match;
		*fs >> match;
		if(match == '1')
			ASSERT_TRUE(matcher->match(*s)) << " with string: " <<  *s;	
		else
			ASSERT_FALSE(matcher->match(*s)) << " with string: " << *s;
		testall(fs, matcher, s, len);
		s->pop_back();
	}
}

// The test ifstream should contain len for testall() function, and then, list of 0 or 1 on whether the ith string tested by testall() should match, separated by spaces
void testmany(std::ifstream *fs, Matcher *matcher) {
	int len;

	*fs >> len;
	std::string s = "";
	testall(fs, matcher, &s, len);
}

class TestBrute : public testing::TestWithParam<int> {};

TEST_P(TestBrute, NFA) {
	std::ifstream fs("data/test" + std::to_string(GetParam()));
	std::string expr;
	fs >> expr;

	Thompson *t = new Thompson(expr);
	testmany(&fs, t);

	delete t;
}

TEST_P(TestBrute, DFA) {
	std::ifstream fs("data/test" + std::to_string(GetParam()));
	std::string expr;
	fs >> expr;

	Powerset *ps = new Powerset(expr);
	testmany(&fs, ps);

	delete ps;
}

TEST_P(TestBrute, DFA_min) {
	std::ifstream fs("data/test" + std::to_string(GetParam()));
	std::string expr;
	fs >> expr;

	Powerset *ps = new Powerset(expr);
	Hopcroft *hc = new Hopcroft(ps);
	testmany(&fs, hc);

	delete hc;
	delete ps;
}

INSTANTIATE_TEST_SUITE_P(Precalc_brute_all, TestBrute, testing::Range(1, 11));