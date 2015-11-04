//
// Created by shacking on 06/08/15.
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Color;

TEST (Color_Test, FromHexString) {
    ASSERT_EQ(Color(0, 0, 0, 255), Color::FromHex("000"));
    ASSERT_EQ(Color(0, 0, 0, 255), Color::FromHex("#000"));

    ASSERT_EQ(Color(0, 0, 0, 255), Color::FromHex("Hello, World"));

    ASSERT_EQ(Color(255, 255, 255, 255), Color::FromHex("FFF"));
    ASSERT_EQ(Color(255, 255, 255, 255), Color::FromHex("FFFFFF"));
    ASSERT_EQ(Color(255, 255, 255, 255), Color::FromHex("#FFFFFF"));

    ASSERT_EQ(Color(255, 0, 0, 255), Color::FromHex("#F00"));
}

