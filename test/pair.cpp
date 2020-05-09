#include "gtest/gtest.h"
#include "ds/pair.h"

TEST(Pair, create_one) {
	ds::pair<int, char> p = {1, 5};
	EXPECT_EQ(p.first, 1);
	EXPECT_EQ(p.second, 5);
}

TEST(Pair, make_pair) {
	ds::pair<int, char> p = ds::make_pair(1, (char)5);
	EXPECT_EQ(p.first, 1);
	EXPECT_EQ(p.second, 5);
}