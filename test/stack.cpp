#include "gtest/gtest.h"
#include "ds/stack.h"

TEST(stack_Push, 1) {
	ds::stack<int> stk;
	EXPECT_EQ(stk.size(), 0);
	EXPECT_EQ(stk.empty(), true);
	stk.push(1);
	EXPECT_EQ(stk.top(), 1);
	EXPECT_EQ(stk.size(), 1);
	EXPECT_EQ(stk.empty(), false);

}

TEST(stack_Push, 2) {
	ds::stack<int> stk;
	stk.push(1);
	EXPECT_EQ(stk.top(), 1);
	EXPECT_EQ(stk.size(), 1);
	EXPECT_EQ(stk.empty(), false);
	stk.push(2);
	EXPECT_EQ(stk.top(), 2);
	EXPECT_EQ(stk.size(), 2);
	EXPECT_EQ(stk.empty(), false);
}

TEST(stack_Push, 3) {
	ds::stack<int> stk;
	for(int i=0; i<100; i++) {
		stk.push(i);
		ASSERT_EQ(stk.size(), i+1);
		ASSERT_EQ(stk.top(), i);
	}
}

TEST(stack_Pop, 1) {
	ds::stack<int> stk;
	stk.push(1);
	stk.pop();
	ASSERT_EQ(stk.size(), 0);
	ASSERT_EQ(stk.empty(), true);
}

TEST(stack_Pop, 2) {
	ds::stack<int> stk;
	stk.push(1);
	stk.push(2);
	stk.pop();
	ASSERT_EQ(stk.size(), 1);
	ASSERT_EQ(stk.top(), 1);
	ASSERT_EQ(stk.empty(), false);
	stk.pop();
	ASSERT_EQ(stk.size(), 0);
	ASSERT_EQ(stk.empty(), true);
}

TEST(stack_PopPush, 1) {
	ds::stack<int> stk;
	stk.push(1);
	stk.push(2);
	stk.pop();
	stk.pop();
	ASSERT_EQ(stk.size(), 0);
	ASSERT_EQ(stk.empty(), true);
	stk.push(2);
	stk.push(1);
	stk.push(3);
	ASSERT_EQ(stk.size(), 3);
	ASSERT_EQ(stk.empty(), false);
	ASSERT_EQ(stk.top(), 3);
	stk.pop();
	ASSERT_EQ(stk.top(), 1);
	ASSERT_EQ(stk.size(), 2);
	ASSERT_EQ(stk.empty(), false);
	stk.pop();
	ASSERT_EQ(stk.top(), 2);
	ASSERT_EQ(stk.size(), 1);
	ASSERT_EQ(stk.empty(), false);
	stk.pop();
	ASSERT_EQ(stk.size(), 0);
	ASSERT_EQ(stk.empty(), true);
}