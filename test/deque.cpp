#include "gtest/gtest.h"
#include "ds/vector.h"
#include "ds/deque.h"
#include <random>

TEST(deque_push_back, 1) {
	ds::deque<int> dq;
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_back(1);
	EXPECT_EQ(dq.back(), 1);
	EXPECT_EQ(dq.size(), 1);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_back(5);
	EXPECT_EQ(dq.back(), 5);
	EXPECT_EQ(dq.size(), 2);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 2);
}

TEST(deque_push_front, 1) {
	ds::deque<int> dq;
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_front(1);
	EXPECT_EQ(dq.front(), 1);
	EXPECT_EQ(dq.size(), 1);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_front(5);
	EXPECT_EQ(dq.front(), 5);
	EXPECT_EQ(dq.size(), 2);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 2);
}

TEST(deque_push_front_and_back, 1) {
	ds::deque<int> dq;
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_front(1);
	EXPECT_EQ(dq.front(), 1);
	EXPECT_EQ(dq.back(), 1);
	EXPECT_EQ(dq.size(), 1);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_back(2);
	EXPECT_EQ(dq.front(), 1);
	EXPECT_EQ(dq.back(), 2);
	EXPECT_EQ(dq.size(), 2);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 2);
	dq.push_front(3);
	EXPECT_EQ(dq.front(), 3);
	EXPECT_EQ(dq.back(), 2);
	EXPECT_EQ(dq.size(), 3);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 4);
	dq.push_front(4);
	EXPECT_EQ(dq.front(), 4);
	EXPECT_EQ(dq.back(), 2);
	EXPECT_EQ(dq.size(), 4);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 4);
	dq.push_back(5);
	EXPECT_EQ(dq.front(), 4);
	EXPECT_EQ(dq.back(), 5);
	EXPECT_EQ(dq.size(), 5);
	EXPECT_EQ(dq.empty(), false);
	EXPECT_EQ(dq.capacity(), 8);
}

TEST(deque_push_and_pop, 1) {
	ds::deque<int> dq;
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_back(1);
	EXPECT_EQ(dq.back(), 1);
	EXPECT_EQ(dq.front(), 1);
	dq.pop_back();
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_front(2);
	EXPECT_EQ(dq.back(), 2);
	EXPECT_EQ(dq.front(), 2);
	dq.pop_back();
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_back(3);
	EXPECT_EQ(dq.back(), 3);
	EXPECT_EQ(dq.front(), 3);
	dq.pop_front();
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
	dq.push_front(4);
	EXPECT_EQ(dq.back(), 4);
	EXPECT_EQ(dq.front(), 4);
	dq.pop_front();
	EXPECT_EQ(dq.size(), 0);
	EXPECT_EQ(dq.empty(), true);
	EXPECT_EQ(dq.capacity(), 1);
}