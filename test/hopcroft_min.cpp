#include "gtest/gtest.h"
#include "powerset.h"
#include "hopcroft.h"
#include "ds/list.h"
#include <string>

void test(std::string expr, int states) {
	Powerset *ps = new Powerset(expr);
	Hopcroft *hc = new Hopcroft(ps);
	EXPECT_EQ(hc->dfa_states, states);
	delete ps;
	delete hc;
}

TEST(hopcroft_min, 1) {
	test("A*B*C", 3);
}

TEST(hopcroft_min, 2) {
	test("A", 2);
}

TEST(hopcroft_min, 3) {
	test("(A|B*)*(C*|D*|A*)*B", 4);
}

TEST(hopcroft_min, 4) {
	test("A*B*C|C*D*A", 8);
}

TEST(hopcroft_min, 5) {
	test("(A*|B*)|(A*C*)", 4);
}

TEST(hopcroft_min, 6) {
	test("ABBA*", 4);
}

TEST(hopcroft_min, 7) {
	test("C(ABA)*", 4);
}

TEST(hopcroft_min, 8) {
	test("A(B|C)*((A|B)|(C|D))E*ABC|F", 8);
}

TEST(hopcroft_min, 9) {
	test("(A|A)B|B*(D|C*)*", 5);
}

TEST(hopcroft_min, 10) {
	test("(A|B)*(C*|D*|A*)*B", 4);
}

TEST(hopcroft_min, 11) {
	test("ABAB*DU", 6);
}

TEST(hopcroft_min, 12) {
	test("A.BAB.*U", 7);
}

TEST(hopcroft_min, 13) {
	test("A.BAB.*U", 7);
}