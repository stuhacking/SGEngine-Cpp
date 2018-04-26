//
// Color Tests
//
#include <gtest/gtest.h>
#include "lib.h"

TEST (Color_Test, fromHexString) {
    EXPECT_EQ(Color(0, 0, 0, 255), Color::fromHex("000"));
    EXPECT_EQ(Color(0, 0, 0, 255), Color::fromHex("#000"));

    EXPECT_EQ(Color(0, 0, 0, 255), Color::fromHex("Hello, World"));
    EXPECT_EQ(Color(0, 0, 0, 255), Color::fromHex(""));
    EXPECT_EQ(Color(0, 0, 0, 255), Color::fromHex("#"));
    EXPECT_EQ(Color(0, 0, 0, 255), Color::fromHex(nullptr));

    EXPECT_EQ(Color(255, 255, 255, 255), Color::fromHex("FFF"));
    EXPECT_EQ(Color(255, 255, 255, 255), Color::fromHex("FFFFFF"));
    EXPECT_EQ(Color(255, 255, 255, 255), Color::fromHex("#FFFFFF"));

    // test lower case
    EXPECT_EQ(Color(255, 255, 0, 255), Color::fromHex("Ff0"));

    EXPECT_EQ(Color(255, 0, 0, 255), Color::fromHex("#F00"));

    // test well-formed garbage (current just accepts strtoul 0 value for error.)
    EXPECT_EQ(Color(0, 0, 0, 0), Color::fromHex("#LLMMNN"));
}

TEST (Color_Test, toVec4f) {
    EXPECT_EQ(Vec4f(255.0f, 255.0f, 255.0f, 255.0f), Color::fromHex("#FFF").toVec4f());
    EXPECT_EQ(Vec4f(1.0f, 1.0f, 1.0f, 1.0f), Color::fromHex("#FFF").toVec4f(true));

    EXPECT_EQ(Vec4f(0.0f, 0.0f, 0.0f, 255.0f), Color::fromHex("#000").toVec4f());
    EXPECT_EQ(Vec4f(0.0f, 0.0f, 0.0f, 1.0f), Color::fromHex("#000").toVec4f(true));
}
