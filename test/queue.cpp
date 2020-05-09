#include "gtest/gtest.h"
#include "ds/queue.h"
#include <random>

TEST(queue, 1) {
	ds::queue<int> q;
	EXPECT_EQ(q.empty(), true);
	q.push(1);
	q.push(2);
	q.push(3);
	EXPECT_EQ(q.front(), 1);
	EXPECT_EQ(q.empty(), false);
	q.pop();
	EXPECT_EQ(q.front(), 2);
	EXPECT_EQ(q.empty(), false);
	q.pop();
	EXPECT_EQ(q.front(), 3);
	EXPECT_EQ(q.empty(), false);
	q.pop();
	EXPECT_EQ(q.empty(), true);
}
