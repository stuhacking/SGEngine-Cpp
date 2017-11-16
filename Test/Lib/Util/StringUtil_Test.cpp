//
//
//
#include <gtest/gtest.h>
#include "lib.h"

using namespace sge::str;

TEST (StringUtil_Test, StartsWith) {
    EXPECT_TRUE(startsWith("String", "S"));
    EXPECT_TRUE(startsWith("String", "Str"));
    EXPECT_TRUE(startsWith("String", ""));
    EXPECT_FALSE(startsWith("String", "tri"));
}

TEST (StringUtil_Test, EndsWith) {
    EXPECT_TRUE(endsWith("String", "g"));
    EXPECT_TRUE(endsWith("String", "ing"));
    EXPECT_TRUE(endsWith("String", ""));
    EXPECT_FALSE(endsWith("String", "str"));
}

TEST (StringUtil_Test, trimLeft) {
    EXPECT_EQ("Test", trimLeft("Test"));
    EXPECT_EQ("Test   ", trimLeft("Test   "));
    EXPECT_EQ("Test", trimLeft("   Test"));
    EXPECT_EQ("Test", trimLeft(" 	 Test"));
    EXPECT_EQ("", trimLeft(""));
    EXPECT_EQ("", trimLeft("  "));
    EXPECT_EQ("", trimLeft("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", trimLeft("Hello 	World!"));
}

TEST (StringUtil_Test, trimRight) {
    EXPECT_EQ("Test", trimRight("Test"));
    EXPECT_EQ("Test", trimRight("Test   "));
    EXPECT_EQ("   Test", trimRight("   Test"));
    EXPECT_EQ(" 	 Test", trimRight(" 	 Test"));
    EXPECT_EQ("Test", trimRight("Test 	 "));
    EXPECT_EQ("", trimRight(""));
    EXPECT_EQ("", trimRight("  "));
    EXPECT_EQ("", trimRight("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", trimRight("Hello 	World!"));
}

TEST (StringUtil_Test, trim) {
    EXPECT_EQ("Test", trim("Test"));
    EXPECT_EQ("Test", trim("Test   "));
    EXPECT_EQ("Test", trim("   Test"));
    EXPECT_EQ("Test", trim(" 	 Test"));
    EXPECT_EQ("Test", trim("Test 	 "));
    EXPECT_EQ("", trim(""));
    EXPECT_EQ("", trim("  "));
    EXPECT_EQ("", trim("	 "));

    // Preserves inner whitespace
    EXPECT_EQ("Hello 	World!", trim("Hello 	World!"));
}

TEST (StringUtil_Test, padLeft) {
    EXPECT_EQ("Test    ", padLeft("Test", 8));
    EXPECT_EQ(8, padLeft("Test", 8).length());
    EXPECT_EQ("Test", padLeft("Test", 3));

    EXPECT_EQ("Hello World---", padLeft("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", padLeft("Hello World", 7, '-'));
}

TEST (StringUtil_Test, padRight) {
    EXPECT_EQ("    Test", padRight("Test", 8));
    EXPECT_EQ(8, padRight("Test", 8).length());
    EXPECT_EQ("Test", padRight("Test", 3));

    EXPECT_EQ("---Hello World", padRight("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", padRight("Hello World", 7, '-'));
}

TEST (StringUtil_Test, padCenter) {
    EXPECT_EQ("  Test  ", padCenter("Test", 8));
    EXPECT_EQ(8, padCenter("Test", 8).length());
    EXPECT_EQ("Test", padCenter("Test", 3));

    EXPECT_EQ("--Hello World-", padCenter("Hello World", 14, '-'));
    EXPECT_EQ("Hello World", padCenter("Hello World", 7, '-'));
}

TEST (StringUtil_Test, truncateEllipsis) {
    EXPECT_EQ("", truncateEllipsis("Hello", 0));
    EXPECT_EQ("\u2026", truncateEllipsis("Hello", 1));
    EXPECT_EQ("H\u2026", truncateEllipsis("Hello", 2));
    EXPECT_EQ("Hello", truncateEllipsis("Hello", 10));
    EXPECT_EQ("Hello", truncateEllipsis("Hello", 5));
    EXPECT_EQ("Hel\u2026", truncateEllipsis("Hello, World!", 4));
}

TEST (StringUtil_Test, truncate) {
    EXPECT_EQ("", sge::str::truncate("Hello", 0));
    EXPECT_EQ("H", sge::str::truncate("Hello", 1));
    EXPECT_EQ("He", sge::str::truncate("Hello", 2));
    EXPECT_EQ("Hello", sge::str::truncate("Hello", 10));
    EXPECT_EQ("Hello", sge::str::truncate("Hello", 5));
    EXPECT_EQ("Hel", sge::str::truncate("Hello, World!", 3));
}

TEST (StringUtil_Test, SetWidth) {
    EXPECT_EQ("Hello", setWidth("Hello", 5));
    EXPECT_EQ("Hello, Wo\u2026", setWidth("Hello, World", 10));
    EXPECT_EQ("Hello    ", setWidth("Hello", 9));
}

TEST (StringUtil_Test, FileExtension) {
    EXPECT_EQ("", fileExt("Test"));
    EXPECT_EQ("", fileExt("Test."));
    EXPECT_EQ("png", fileExt(".png"));
    EXPECT_EQ("txt", fileExt("foo.txt"));
    EXPECT_EQ("gz", fileExt("foo.tar.gz"));
}

TEST (StringUtil_Test, FileName) {
    EXPECT_EQ("Test", fileName("Test"));
    EXPECT_EQ("Test.txt", fileName("Test.txt"));
    EXPECT_EQ("Text", fileName("/res/data/Text"));
    EXPECT_EQ("img.png", fileName("/res/art/img.png"));
    EXPECT_EQ("", fileName("/res/art/"));
}

TEST (StringUtil_Test, BasePath) {
    EXPECT_EQ("", basePath("Test"));
    EXPECT_EQ("", basePath("Test.txt"));
    EXPECT_EQ("/res/data/", basePath("/res/data/Text"));
    EXPECT_EQ("/res/art/", basePath("/res/art/img.png"));
    EXPECT_EQ("/res/art/", basePath("/res/art/"));
}
