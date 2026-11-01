#include <gtest/gtest.h>
#include <mysqrt.hpp>
#include <cmath>

TEST(MySqrtTest, HandlesPositiveNumbers) {
    EXPECT_NEAR(mysqrt(25.0), 5.0, 1e-5);
    EXPECT_NEAR(mysqrt(9.0), 3.0, 1e-5);
    EXPECT_NEAR(mysqrt(2.0), 1.41421, 1e-4);
}

TEST(MySqrtTest, HandlesZeroAndOne) {
    EXPECT_NEAR(mysqrt(0.0), 0.0, 1e-5);
    EXPECT_NEAR(mysqrt(1.0), 1.0, 1e-5);
}

TEST(MySqrtTest, HandlesNegativeInput) {
    double result = mysqrt(-4.0);
    EXPECT_TRUE(std::isnan(result) || result == 0.0); 
}