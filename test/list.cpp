#include "gtest/gtest.h"
#include "ds/list.h"

TEST(list, pushpop) {
	ds::list<int> l;
	EXPECT_EQ(l.size(), 0);
	EXPECT_EQ(l.empty(), true);
	l.push_back(1);
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l.empty(), false);
	EXPECT_EQ(l.front(), 1);
	EXPECT_EQ(l.back(), 1);
	l.push_front(0);
	EXPECT_EQ(l.size(), 2);
	EXPECT_EQ(l.empty(), false);
	EXPECT_EQ(l.front(), 0);
	EXPECT_EQ(l.back(), 1);
	l.pop_front();
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l.empty(), false);
	EXPECT_EQ(l.front(), 1);
	EXPECT_EQ(l.back(), 1);
	l.push_back(3);
	EXPECT_EQ(l.size(), 2);
	EXPECT_EQ(l.empty(), false);
	EXPECT_EQ(l.front(), 1);
	EXPECT_EQ(l.back(), 3);
	l.pop_back();
	EXPECT_EQ(l.size(), 1);
	EXPECT_EQ(l.empty(), false);
	EXPECT_EQ(l.front(), 1);
	EXPECT_EQ(l.back(), 1);
	l.pop_back();
	EXPECT_EQ(l.size(), 0);
	EXPECT_EQ(l.empty(), true);
}

TEST(list, iter_short_back) {
	ds::list<int> l;
	l.push_back(1);
	int cnt = 1;
	for(auto u : l) {
		EXPECT_EQ(u, cnt++);
	}
}


TEST(list, iter_short_front) {
	ds::list<int> l;
	l.push_front(1);
	int cnt = 1;
	for(auto u : l) {
		EXPECT_EQ(u, cnt++);
	}
}

TEST(list, iter_long) {
	ds::list<int> l;
	l.push_back(2);
	l.push_front(1);
	for(int i=3; i<=1000; i++) {
		l.push_back(i);
		int cnt = 1;
		for(auto u : l) {
			EXPECT_EQ(u, cnt++);
		}
	}
}

TEST(list, splice) {
	ds::list<int> l1;
	l1.push_front(2);
	l1.push_back(3);
	l1.push_front(1);
	ds::list<int> l2;
	l2.push_front(5);
	l2.push_back(6);
	l2.push_front(4);
	l1.splice(l1.end(), l2, l2.begin());
	EXPECT_EQ(l1.size(), 4);
	EXPECT_EQ(l1.empty(), false);
	EXPECT_EQ(l1.front(), 1);
	EXPECT_EQ(l1.back(), 4);
}