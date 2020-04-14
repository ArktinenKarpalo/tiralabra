#include "gtest/gtest.h"
#include "ds/node_nfa.h"
#include "matcher.h"

// Test if addtrans adds some element to vector with transitions
TEST(NodeTest, AddTransSize) {
	ds::Node_nfa *nodeA = new ds::Node_nfa();
	ds::Node_nfa *nodeB = new ds::Node_nfa();
	nodeA->addTrans('A', nodeB);
	EXPECT_EQ(nodeA->next('A').size(), 1);
	EXPECT_EQ(nodeA->next('B').size(), 0);
	delete nodeA;
	delete nodeB;
}

// Test some basic operations TODO: test with generated inputs from a file

TEST(MatcherTest, 1) {
	EXPECT_TRUE(matcher::match("A", "A"));
	EXPECT_FALSE(matcher::match("A", "B"));
	EXPECT_FALSE(matcher::match("A", "AA"));
}

TEST(MatcherTest, 2) {
	EXPECT_TRUE(matcher::match("ABC", "ABC"));
	EXPECT_FALSE(matcher::match("ABC", "AB"));
	EXPECT_FALSE(matcher::match("ABC", "ABCC"));
	EXPECT_FALSE(matcher::match("ABC", "BC"));
}

TEST(MatcherTest, 3) {
	EXPECT_TRUE(matcher::match("A*", "A"));
	EXPECT_TRUE(matcher::match("A*", "AAAAAA"));
	EXPECT_FALSE(matcher::match("A*", "AAB"));
	EXPECT_FALSE(matcher::match("A*", "BAA"));
	EXPECT_FALSE(matcher::match("A*", "ABA"));
}

TEST(MatcherTest, 4) {
	EXPECT_TRUE(matcher::match("A|BC", "A"));
	EXPECT_TRUE(matcher::match("A|BC", "BC"));
	EXPECT_FALSE(matcher::match("A|BC", "ABC"));
	EXPECT_FALSE(matcher::match("A|BC", "BCA"));
	EXPECT_FALSE(matcher::match("A|BC", "C"));
}

TEST(MatcherTest, 5) {
	EXPECT_TRUE(matcher::match("(A|B)C", "AC"));
	EXPECT_TRUE(matcher::match("(A|B)C", "AC"));
	EXPECT_FALSE(matcher::match("(A|B)C", "AB"));
	EXPECT_FALSE(matcher::match("(A|B)C", "ABC"));
	EXPECT_FALSE(matcher::match("(A|B)C", "C"));
}

TEST(MatcherTest, 6) {
	EXPECT_TRUE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "F"));
	EXPECT_TRUE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "ACBBCABC"));
	EXPECT_TRUE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "ABBCCABC"));
	EXPECT_TRUE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "ACABC"));
	EXPECT_TRUE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "ACBBCDEEEEABC"));
	EXPECT_FALSE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "FF"));
	EXPECT_FALSE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "ABCBEEAABC"));
	EXPECT_FALSE(matcher::match("A(B|C)*((A|B)|(C|D))E*ABC|F", "ABCCDBDEEEABC"));
}
