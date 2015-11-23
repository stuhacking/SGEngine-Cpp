//
// Random Tests
//
#include <gtest/gtest.h>
#include "Lib.h"

using sge::Random;

TEST (Random_Test, same_seed_same_sequence) {
    Random r1 = Random(1);
    Random r2 = Random(1);

    for (int k = 0; k < 100; ++k) {
        EXPECT_EQ(r1.NextInt(), r2.NextInt());
        EXPECT_EQ(r1.NextInt(10), r2.NextInt(10));
        EXPECT_EQ(r1.NextInt(20, 50), r2.NextInt(20, 50));
        EXPECT_FLOAT_EQ(r1.NextFloat(), r2.NextFloat());
        EXPECT_FLOAT_EQ(r1.NextFloat(2.0f), r2.NextFloat(2.0f));
        EXPECT_FLOAT_EQ(r1.NextFloat(-4.0f, 4.0f), r2.NextFloat(-4.0f, 4.0f));
    }
}

TEST (Random_Test, diff_seed_diff_sequence) {
    Random r1 = Random(1);
    Random r2 = Random(3);

    bool allMatch = true;
    for (int k = 0; k < 100; ++k) {
        allMatch = r1.NextInt() == r2.NextInt();
        allMatch = r1.NextInt(10) == r2.NextInt(10);
        allMatch = r1.NextInt(20, 50) == r2.NextInt(20, 50);
        allMatch = r1.NextFloat() == r2.NextFloat(20, 50);
        allMatch = r1.NextFloat(2.0f) == r2.NextFloat(2.0f);
        allMatch = r1.NextFloat(-4.0f, 4.0f) == r2.NextFloat(-4.0f, 4.0f);
    }

    EXPECT_FALSE(allMatch);
}

TEST (Random_Test, set_seed_same) {
    Random r1 = Random(1);
    Random r2 = Random(3);

    for (int k = 0; k < 30; ++k) {
        r1.NextInt();

        if (k % 3 == 0) r2.NextInt();
    }

    r1.SetSeed(10);
    r2.SetSeed(10);

    for (int k = 0; k < 100; ++k) {
        EXPECT_EQ(r1.NextInt(), r2.NextInt());
        EXPECT_EQ(r1.NextInt(10), r2.NextInt(10));
        EXPECT_EQ(r1.NextInt(20, 50), r2.NextInt(20, 50));
        EXPECT_FLOAT_EQ(r1.NextFloat(), r2.NextFloat());
        EXPECT_FLOAT_EQ(r1.NextFloat(2.0f), r2.NextFloat(2.0f));
        EXPECT_FLOAT_EQ(r1.NextFloat(-4.0f, 4.0f), r2.NextFloat(-4.0f, 4.0f));
    }
}

TEST (Random_Test, set_seed_diff_sequence) {
    Random r1 = Random(3);
    Random r2 = Random(3);

    for (int k = 0; k < 30; ++k) {
        r1.NextInt();
        r2.NextInt();
    }

    r1.SetSeed(12);
    r2.SetSeed(25);

    bool allMatch = true;
    for (int k = 0; k < 100; ++k) {
        allMatch = r1.NextInt() == r2.NextInt();
        allMatch = r1.NextInt(10) == r2.NextInt(10);
        allMatch = r1.NextInt(20, 50) == r2.NextInt(20, 50);
        allMatch = r1.NextFloat() == r2.NextFloat(20, 50);
        allMatch = r1.NextFloat(2.0f) == r2.NextFloat(2.0f);
        allMatch = r1.NextFloat(-4.0f, 4.0f) == r2.NextFloat(-4.0f, 4.0f);
    }

    EXPECT_FALSE(allMatch);
}
