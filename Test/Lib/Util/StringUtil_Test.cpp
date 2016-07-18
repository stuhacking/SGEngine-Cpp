//
//
//
#include <gtest/gtest.h>
#include "Lib.h"

using namespace sge::str;

TEST (StringUtil_Test, StartsWith) {
    EXPECT_TRUE(StartsWith("String", "S"));
    EXPECT_TRUE(StartsWith("String", "Str"));
    EXPECT_TRUE(StartsWith("String", ""));
    EXPECT_FALSE(StartsWith("String", "tri"));
}

TEST (StringUtil_Test, EndsWith) {
    EXPECT_TRUE(EndsWith("String", "g"));
    EXPECT_TRUE(EndsWith("String", "ing"));
    EXPECT_TRUE(EndsWith("String", ""));
    EXPECT_FALSE(EndsWith("String", "str"));
}

TEST (StringUtil_Test, TrimLeft) {
    EXPECT_EQ("Test", TrimLeft("Test"));
    EXPECT_EQ("Test   ", TrimLeft("Test   "));
    EXPECT_EQ("Test", TrimLeft("   Test"));
    EXPECT_EQ("Test", TrimLeft(" 	 Test"));
    EXPECT_EQ("", TrimLeft(""));
    EXPECT_EQ("", TrimLeft("  "));
    EXPECT_EQ("", TrimLeft("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", TrimLeft("Hello 	World!"));
}

TEST (StringUtil_Test, TrimRight) {
    EXPECT_EQ("Test", TrimRight("Test"));
    EXPECT_EQ("Test", TrimRight("Test   "));
    EXPECT_EQ("   Test", TrimRight("   Test"));
    EXPECT_EQ(" 	 Test", TrimRight(" 	 Test"));
    EXPECT_EQ("Test", TrimRight("Test 	 "));
    EXPECT_EQ("", TrimRight(""));
    EXPECT_EQ("", TrimRight("  "));
    EXPECT_EQ("", TrimRight("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", TrimRight("Hello 	World!"));
}

TEST (StringUtil_Test, Trim) {
    EXPECT_EQ("Test", Trim("Test"));
    EXPECT_EQ("Test", Trim("Test   "));
    EXPECT_EQ("Test", Trim("   Test"));
    EXPECT_EQ("Test", Trim(" 	 Test"));
    EXPECT_EQ("Test", Trim("Test 	 "));
    EXPECT_EQ("", Trim(""));
    EXPECT_EQ("", Trim("  "));
    EXPECT_EQ("", Trim("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", Trim("Hello 	World!"));
}

TEST (StringUtil_Test, PadLeft) {
    EXPECT_EQ("Test    ", PadLeft("Test", 8));
    EXPECT_EQ(8, PadLeft("Test", 8).length());
    EXPECT_EQ("Test", PadLeft("Test", 3));

    EXPECT_EQ("Hello World---", PadLeft("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", PadLeft("Hello World", 7, '-'));
}

TEST (StringUtil_Test, PadRight) {
    EXPECT_EQ("    Test", PadRight("Test", 8));
    EXPECT_EQ(8, PadRight("Test", 8).length());
    EXPECT_EQ("Test", PadRight("Test", 3));

    EXPECT_EQ("---Hello World", PadRight("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", PadRight("Hello World", 7, '-'));
}

TEST (StringUtil_Test, PadCenter) {
    EXPECT_EQ("  Test  ", PadCenter("Test", 8));
    EXPECT_EQ(8, PadCenter("Test", 8).length());
    EXPECT_EQ("Test", PadCenter("Test", 3));

    EXPECT_EQ("--Hello World-", PadCenter("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", PadCenter("Hello World", 7, '-'));
}

TEST (StringUtil_Test, TruncateEllipsis) {
    EXPECT_EQ("", TruncateEllipsis("Hello", 0));
    EXPECT_EQ("~", TruncateEllipsis("Hello", 1));
    EXPECT_EQ("H~", TruncateEllipsis("Hello", 2));
    EXPECT_EQ("Hello", TruncateEllipsis("Hello", 10));
    EXPECT_EQ("Hello", TruncateEllipsis("Hello", 5));
    EXPECT_EQ("Hel~", TruncateEllipsis("Hello, World!", 4));
}

TEST (StringUtil_Test, Truncate) {
    EXPECT_EQ("", Truncate("Hello", 0));
    EXPECT_EQ("H", Truncate("Hello", 1));
    EXPECT_EQ("He", Truncate("Hello", 2));
    EXPECT_EQ("Hello", Truncate("Hello", 10));
    EXPECT_EQ("Hello", Truncate("Hello", 5));
    EXPECT_EQ("Hel", Truncate("Hello, World!", 3));
}

TEST (StringUtil_Test, SetWidth) {
    EXPECT_EQ("Hello", SetWidth("Hello", 5));
    EXPECT_EQ("Hello, Wo~", SetWidth("Hello, World", 10));
    EXPECT_EQ("Hello    ", SetWidth("Hello", 9));
}

TEST (StringUtil_Test, FileExtension) {
    EXPECT_EQ("", FileExtension("Test"));
    EXPECT_EQ("", FileExtension("Test."));
    EXPECT_EQ("png", FileExtension(".png"));
    EXPECT_EQ("txt", FileExtension("foo.txt"));
    EXPECT_EQ("gz", FileExtension("foo.tar.gz"));
}

TEST (StringUtil_Test, FileName) {
    EXPECT_EQ("Test", FileName("Test"));
    EXPECT_EQ("Test.txt", FileName("Test.txt"));
    EXPECT_EQ("Text", FileName("/res/data/Text"));
    EXPECT_EQ("img.png", FileName("/res/art/img.png"));
    EXPECT_EQ("", FileName("/res/art/"));
}

TEST (StringUtil_Test, BasePath) {
    EXPECT_EQ("", BasePath("Test"));
    EXPECT_EQ("", BasePath("Test.txt"));
    EXPECT_EQ("/res/data/", BasePath("/res/data/Text"));
    EXPECT_EQ("/res/art/", BasePath("/res/art/img.png"));
    EXPECT_EQ("/res/art/", BasePath("/res/art/"));
}
