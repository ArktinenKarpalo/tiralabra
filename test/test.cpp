#include <string>
#include <utility>
#include "powerset.h"
#include "gtest/gtest.h"
#include "thompson.h"
#include "ds/node_nfa.h"
#include "ds/matcher.h"

// Test if addtrans adds some element to vector with transitions
TEST(NodeTest, AddTransSize) {
	ds::Node_nfa *nodeA = new ds::Node_nfa(1);
	ds::Node_nfa *nodeB = new ds::Node_nfa(2);
	nodeA->addTrans('A', nodeB);
	EXPECT_EQ(nodeA->next('A').size(), 1);
	EXPECT_EQ(nodeA->next('B').size(), 0);
	delete nodeA;
	delete nodeB;
}

// Test some basic operations
void test_inputs(std::pair<std::string, bool> inputs[], int n, Matcher *m) {
	for(int i=0; i<n; i++) {
		if(inputs[i].second) {
			EXPECT_TRUE(m->match(inputs[i].first)) << "Input string: " << inputs[i].first;
		} else {
			EXPECT_FALSE(m->match(inputs[i].first)) << "Input string: " << inputs[i].first;
		}
	}
}

TEST(MatcherTest_NFA_one_symbol, 1) {
	Thompson *t = new Thompson("A");
	std::pair<std::string, bool> inputs[] = {
		std::make_pair("A", true),
		std::make_pair("B", false),
		std::make_pair("AA", false),
		std::make_pair("ABA", false)
		};
	test_inputs(inputs, sizeof(inputs)/sizeof(inputs[0]), t);
	delete t;
}

TEST(MatcherTest_NFA_concat, 2) {
	Thompson *t = new Thompson("ABC");
	std::pair<std::string, bool> inputs[] = {
		std::make_pair("ABC", true),
		std::make_pair("AB", false),
		std::make_pair("ABCC", false),
		std::make_pair("BC", false)
		};
	test_inputs(inputs, sizeof(inputs)/sizeof(inputs[0]), t);
	delete t;
}

TEST(MatcherTest_NFA_star, 3) {
	Thompson *t = new Thompson("A*");
	std::pair<std::string, bool> inputs[] = {
		std::make_pair("A", true),
		std::make_pair("AA", true),
		std::make_pair("AAAAAA", true),
		std::make_pair("AAB", false),
		std::make_pair("BAA", false),
		std::make_pair("ABA", false),
		std::make_pair("BAB", false)
		};
	test_inputs(inputs, sizeof(inputs)/sizeof(inputs[0]), t);
	delete t;
}

TEST(MatcherTest_NFA_or, 4) {
	Thompson *t = new Thompson("A|BC");
	std::pair<std::string, bool> inputs[] = {
		std::make_pair("A", true),
		std::make_pair("BC", true),
		std::make_pair("ABC", false),
		std::make_pair("BCA", false),
		std::make_pair("C", false)
		};
	test_inputs(inputs, sizeof(inputs)/sizeof(inputs[0]), t);
	delete t;
}