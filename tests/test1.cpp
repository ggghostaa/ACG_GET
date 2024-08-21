//
// Created by dd on 2024/8/16.
//

#include "gtest/gtest.h"

TEST(SampleeTest, TrueIsTrue) {
    std::cout << "aaa" << std::endl;
    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}