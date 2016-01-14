//
// Color Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Vector4;
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

TEST (Color_Test, ToVector4) {
    EXPECT_EQ(Vector4(255.0f, 255.0f, 255.0f, 255.0f), Color::FromHex("#FFF").ToVector4());
    EXPECT_EQ(Vector4(1.0f, 1.0f, 1.0f, 1.0f), Color::FromHex("#FFF").ToVector4(true));

    EXPECT_EQ(Vector4(0.0f, 0.0f, 0.0f, 255.0f), Color::FromHex("#000").ToVector4());
    EXPECT_EQ(Vector4(0.0f, 0.0f, 0.0f, 1.0f), Color::FromHex("#000").ToVector4(true));
}
