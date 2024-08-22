//
// Created by dd on 2024/8/16.
//

#include "gtest/gtest.h"
TEST(FindACGTest, TrueIsTrue) {
    EXPECT_TRUE(true);
}

int gtest_main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}