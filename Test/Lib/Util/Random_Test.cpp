//
// Random Tests
//
#include <gtest/gtest.h>
#include <iostream>

#include "Lib.h"

using sge::Random;

static constexpr int nrolls = 10000;

TEST (Random_Test, same_seed_same_sequence) {
    Random r1 = Random(1);
    Random r2 = Random(1);

    for (int k = 0; k < nrolls; ++k) {
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
    for (int k = 0; k < nrolls; ++k) {
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

    for (int k = 0; k < nrolls; ++k) {
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
    for (int k = 0; k < nrolls; ++k) {
        allMatch = r1.NextInt() == r2.NextInt();
        allMatch = r1.NextInt(10) == r2.NextInt(10);
        allMatch = r1.NextInt(20, 50) == r2.NextInt(20, 50);
        allMatch = r1.NextFloat() == r2.NextFloat(20, 50);
        allMatch = r1.NextFloat(2.0f) == r2.NextFloat(2.0f);
        allMatch = r1.NextFloat(-4.0f, 4.0f) == r2.NextFloat(-4.0f, 4.0f);
    }

    EXPECT_FALSE(allMatch);
}

TEST (Random_Test, Uniform_Int_Distribution) {
    Random r1 = Random(1);

    int max = 9;
    int results[max + 1] = {};

    for (int k = 0; k < nrolls; ++k) {
        // This is the actual roll
        results[r1.NextInt(max)]++;

        // What if there's something else using the rng...
        // The distribution should be resilient against that.
        r1.NextFloat();
        r1.NextInt(2, 12);
    }

    // Histogram.
    //for (int k = 0; k <= max; ++k) {
    //    std::cout << k << ": " << std::string(results[k] * 200 / nrolls,'*') << "\n";
    //}

    bool allMatch = true;
    for (int k = 1; k <= max; ++k) {
        allMatch = (results[k] * 200 / nrolls) == (results[k - 1] * 200 / nrolls);
    }

    EXPECT_TRUE(allMatch);
}
