//
// Color Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vec4f;
using sge::Color;

TEST (Color_Test, FromHexString) {
    EXPECT_EQ(Color(0, 0, 0, 255), Color::FromHex("000"));
    EXPECT_EQ(Color(0, 0, 0, 255), Color::FromHex("#000"));

    EXPECT_EQ(Color(0, 0, 0, 255), Color::FromHex("Hello, World"));

    EXPECT_EQ(Color(255, 255, 255, 255), Color::FromHex("FFF"));
    EXPECT_EQ(Color(255, 255, 255, 255), Color::FromHex("FFFFFF"));
    EXPECT_EQ(Color(255, 255, 255, 255), Color::FromHex("#FFFFFF"));

    EXPECT_EQ(Color(255, 0, 0, 255), Color::FromHex("#F00"));
}

TEST (Color_Test, ToVec4f) {
    EXPECT_EQ(Vec4f(255.0f, 255.0f, 255.0f, 255.0f), Color::FromHex("#FFF").ToVec4f());
    EXPECT_EQ(Vec4f(1.0f, 1.0f, 1.0f, 1.0f), Color::FromHex("#FFF").ToVec4f(true));

    EXPECT_EQ(Vec4f(0.0f, 0.0f, 0.0f, 255.0f), Color::FromHex("#000").ToVec4f());
    EXPECT_EQ(Vec4f(0.0f, 0.0f, 0.0f, 1.0f), Color::FromHex("#000").ToVec4f(true));
}
