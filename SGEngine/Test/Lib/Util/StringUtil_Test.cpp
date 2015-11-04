//
//
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::String;

TEST (StringUtil_Test, StartsWith) {
    EXPECT_TRUE(String::StartsWith("String", "S"));
    EXPECT_TRUE(String::StartsWith("String", "Str"));
    EXPECT_TRUE(String::StartsWith("String", ""));
    EXPECT_FALSE(String::StartsWith("String", "tri"));
}

TEST (StringUtil_Test, EndsWith) {
    EXPECT_TRUE(String::EndsWith("String", "g"));
    EXPECT_TRUE(String::EndsWith("String", "ing"));
    EXPECT_TRUE(String::EndsWith("String", ""));
    EXPECT_FALSE(String::EndsWith("String", "str"));
}

TEST (StringUtil_Test, TrimLeft) {
    EXPECT_EQ("Test", String::TrimLeft("Test"));
    EXPECT_EQ("Test   ", String::TrimLeft("Test   "));
    EXPECT_EQ("Test", String::TrimLeft("   Test"));
    EXPECT_EQ("Test", String::TrimLeft(" 	 Test"));
    EXPECT_EQ("", String::TrimLeft(""));
    EXPECT_EQ("", String::TrimLeft("  "));
    EXPECT_EQ("", String::TrimLeft("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", String::TrimLeft("Hello 	World!"));
}

TEST (StringUtil_Test, TrimRight) {
    EXPECT_EQ("Test", String::TrimRight("Test"));
    EXPECT_EQ("Test", String::TrimRight("Test   "));
    EXPECT_EQ("   Test", String::TrimRight("   Test"));
    EXPECT_EQ(" 	 Test", String::TrimRight(" 	 Test"));
    EXPECT_EQ("Test", String::TrimRight("Test 	 "));
    EXPECT_EQ("", String::TrimRight(""));
    EXPECT_EQ("", String::TrimRight("  "));
    EXPECT_EQ("", String::TrimRight("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", String::TrimRight("Hello 	World!"));
}

TEST (StringUtil_Test, Trim) {
    EXPECT_EQ("Test", String::Trim("Test"));
    EXPECT_EQ("Test", String::Trim("Test   "));
    EXPECT_EQ("Test", String::Trim("   Test"));
    EXPECT_EQ("Test", String::Trim(" 	 Test"));
    EXPECT_EQ("Test", String::Trim("Test 	 "));
    EXPECT_EQ("", String::Trim(""));
    EXPECT_EQ("", String::Trim("  "));
    EXPECT_EQ("", String::Trim("	 "));
    
    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", String::Trim("Hello 	World!"));
}

TEST (StringUtil_Test, PadLeft) {
    EXPECT_EQ("Test    ", String::PadLeft("Test", 8));
    EXPECT_EQ(8, String::PadLeft("Test", 8).length());
    EXPECT_EQ("Test", String::PadLeft("Test", 3));

    EXPECT_EQ("Hello World---", String::PadLeft("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", String::PadLeft("Hello World", 7, '-'));
}

TEST (StringUtil_Test, PadRight) {
    EXPECT_EQ("    Test", String::PadRight("Test", 8));
    EXPECT_EQ(8, String::PadRight("Test", 8).length());
    EXPECT_EQ("Test", String::PadRight("Test", 3));

    EXPECT_EQ("---Hello World", String::PadRight("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", String::PadRight("Hello World", 7, '-'));
}

TEST (StringUtil_Test, PadCenter) {
    EXPECT_EQ("  Test  ", String::PadCenter("Test", 8));
    EXPECT_EQ(8, String::PadCenter("Test", 8).length());
    EXPECT_EQ("Test", String::PadCenter("Test", 3));

    EXPECT_EQ("--Hello World-", String::PadCenter("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", String::PadCenter("Hello World", 7, '-'));
}

TEST (StringUtil_Test, TruncateEllipsis) {
    EXPECT_EQ("", String::TruncateEllipsis("Hello", 0));
    EXPECT_EQ(">", String::TruncateEllipsis("Hello", 1));
    EXPECT_EQ("H>", String::TruncateEllipsis("Hello", 2));
    EXPECT_EQ("Hello", String::TruncateEllipsis("Hello", 10));
    EXPECT_EQ("Hello", String::TruncateEllipsis("Hello", 5));
    EXPECT_EQ("Hel>", String::TruncateEllipsis("Hello, World!", 4));
}

TEST (StringUtil_Test, Truncate) {
    EXPECT_EQ("", String::Truncate("Hello", 0));
    EXPECT_EQ("H", String::Truncate("Hello", 1));
    EXPECT_EQ("He", String::Truncate("Hello", 2));
    EXPECT_EQ("Hello", String::Truncate("Hello", 10));
    EXPECT_EQ("Hello", String::Truncate("Hello", 5));
    EXPECT_EQ("Hel", String::Truncate("Hello, World!", 3));
}

TEST (StringUtil_Test, SetWidth) {
    EXPECT_EQ("Hello", String::SetWidth("Hello", 5));
    EXPECT_EQ("Hello, Wo>", String::SetWidth("Hello, World", 10));
    EXPECT_EQ("Hello    ", String::SetWidth("Hello", 9));
}

TEST (StringUtil_Test, FileExtension) {
    EXPECT_EQ("", String::FileExtension("Test"));
    EXPECT_EQ("", String::FileExtension("Test."));
    EXPECT_EQ("png", String::FileExtension(".png"));
    EXPECT_EQ("txt", String::FileExtension("foo.txt"));
    EXPECT_EQ("gz", String::FileExtension("foo.tar.gz"));    
}

TEST (StringUtil_Test, FileName) {
    EXPECT_EQ("Test", String::FileName("Test"));
    EXPECT_EQ("Test.txt", String::FileName("Test.txt"));
    EXPECT_EQ("Text", String::FileName("/res/data/Text"));
    EXPECT_EQ("img.png", String::FileName("/res/art/img.png"));
    EXPECT_EQ("", String::FileName("/res/art/"));
}

TEST (StringUtil_Test, BasePath) {
    EXPECT_EQ("", String::BasePath("Test"));
    EXPECT_EQ("", String::BasePath("Test.txt"));
    EXPECT_EQ("/res/data/", String::BasePath("/res/data/Text"));
    EXPECT_EQ("/res/art/", String::BasePath("/res/art/img.png"));
    EXPECT_EQ("/res/art/", String::BasePath("/res/art/"));
}
