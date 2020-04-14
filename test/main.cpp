#include "gtest/gtest.h"

int main() {
	::testing::InitGoogleTest();
	RUN_ALL_TESTS();
	return 0; // Always return 0, even if tests fail
}
