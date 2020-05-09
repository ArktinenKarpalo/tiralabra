#include "gtest/gtest.h"
#include "ds/vector.h"

TEST(vector_Push, 1) {
	ds::vector<int> v;
	v.push_back(1);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v.size(), 1);
	EXPECT_EQ(v.capacity(), 1);
}

TEST(vector_Push, 2) {
	ds::vector<int> v;
	v.push_back(1);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v.size(), 1);
	EXPECT_EQ(v.capacity(), 1);
	v.push_back(2);
	EXPECT_EQ(v[0], 1);
	EXPECT_EQ(v[1], 2);
	EXPECT_EQ(v.size(), 2);
	EXPECT_EQ(v.capacity(), 2);
}

TEST(vector_Push, 3) {
	ds::vector<int> v;
	for(int i=0; i<100; i++) {
		v.push_back(i);
		ASSERT_EQ(v.size(), i+1);
		for(int j=0; j<=i; j++) {
			ASSERT_EQ(v[j], j);
		}
	}
	ASSERT_EQ(v.capacity(), 128);
	ASSERT_EQ(v.size(), 100);
}

TEST(vector_Pop, 1) {
	ds::vector<int> v;
	v.push_back(1);
	v.pop_back();
	ASSERT_EQ(v.size(), 0);
	ASSERT_EQ(v.capacity(), 1);
}

TEST(vector_Pop, 2) {
	ds::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.pop_back();
	ASSERT_EQ(v.size(), 1);
	ASSERT_EQ(v.capacity(), 2);
	v.pop_back();
	ASSERT_EQ(v.size(), 0);
	ASSERT_EQ(v.capacity(), 1);
}

TEST(vector_PopPush, 1) {
	ds::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.pop_back();
	v.pop_back();
	ASSERT_EQ(v.size(), 0);
	ASSERT_EQ(v.capacity(), 1);
	v.push_back(2);
	v.push_back(1);
	v.push_back(3);
	ASSERT_EQ(v.size(), 3);
	ASSERT_EQ(v.capacity(), 4);
	ASSERT_EQ(v[0], 2);
	ASSERT_EQ(v[1], 1);
	ASSERT_EQ(v[2], 3);
}

TEST(vector_iter, 1) {
	ds::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	int cnt = 1;
	for(auto u : v) {
		ASSERT_EQ(u, cnt++);
	}
	cnt = 1;
	v.pop_back();
	for(auto u : v) {
		ASSERT_EQ(u, cnt++);
	}
}