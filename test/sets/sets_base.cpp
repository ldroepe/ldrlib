#include "sets.h"
#include <gtest/gtest.h>

class SetTestsFixture: public ::testing::Test
{
protected:
    const std::unordered_set<int> nonempty_one = {1, 2, 3, 4, 5};
    const std::unordered_set<int> nonempty_two = {7, 8, 9};
    const std::unordered_set<int> nonempty_three = {1, 2, 3};
    const std::unordered_set<int> nonempty_four = {7, 8, 1};
    const std::unordered_set<int> empty_one;

    template <typename T>
    std::string to_string(const std::unordered_set<T>& s)
    {
        std::ostringstream oss;
        oss << '{';
        for(const auto& x: s)
            oss << x << ',';
        oss << '}';
        return oss.str();
    }
};

TEST_F(SetTestsFixture, test_union_identity)
// Test ldr::set_union respects identity operations
{

    EXPECT_EQ(ldr::set_union(nonempty_one, empty_one), nonempty_one);
    EXPECT_EQ(ldr::set_union(empty_one, nonempty_one), nonempty_one);
    EXPECT_EQ(ldr::set_union(empty_one, empty_one), empty_one);
}

TEST_F(SetTestsFixture, test_union_symmetric)
// Test ldr::set_union is symmetric
{
    
    const auto ab = ldr::set_union(nonempty_one, nonempty_two);
    const auto ba = ldr::set_union(nonempty_two, nonempty_one);
    EXPECT_EQ(ab, ba);

    const auto bc = ldr::set_union(nonempty_two, nonempty_three);
    const auto cb = ldr::set_union(nonempty_three, nonempty_two);
    EXPECT_EQ(bc, cb);
}

TEST_F(SetTestsFixture, test_intersection_identity)
// Test ldr::set_intersection respects identity operations
{

    EXPECT_EQ(ldr::set_intersection(nonempty_one, nonempty_one), nonempty_one);
    EXPECT_EQ(ldr::set_intersection(empty_one, empty_one), empty_one);
}

TEST_F(SetTestsFixture, test_intersection_symmetry)
// Test ldr::set_intersection is symmetric
{
    
    EXPECT_EQ(ldr::set_intersection(nonempty_one, empty_one), empty_one);
    EXPECT_EQ(ldr::set_intersection(empty_one, nonempty_one), empty_one);
    EXPECT_EQ(ldr::set_intersection(nonempty_one, nonempty_three), nonempty_three);
    EXPECT_EQ(ldr::set_intersection(nonempty_three, nonempty_one), nonempty_three);
}

TEST_F(SetTestsFixture, test_intersection_misc)
// Misc ldr::set_intersection tests
{

    EXPECT_EQ(ldr::set_intersection(nonempty_one, nonempty_three), nonempty_three);
}

TEST_F(SetTestsFixture, test_difference_identity)
// Test ldr::set_difference respects identity operations
{
    
    EXPECT_EQ(ldr::set_difference(nonempty_one, nonempty_two), nonempty_one);
    EXPECT_EQ(ldr::set_difference(nonempty_two, nonempty_one), nonempty_two);
    EXPECT_EQ(ldr::set_difference(nonempty_one, empty_one), nonempty_one);
    EXPECT_EQ(ldr::set_difference(empty_one, nonempty_one), empty_one);
}

TEST_F(SetTestsFixture, test_difference_subsets)
{

    // strict subset
    EXPECT_EQ(ldr::set_difference(nonempty_one, nonempty_three), std::unordered_set({4, 5}));
    EXPECT_EQ(ldr::set_difference(nonempty_three, nonempty_one), empty_one);

    //partial subset
    EXPECT_EQ(ldr::set_difference(nonempty_one, nonempty_four), std::unordered_set({2, 3, 4, 5}));
    EXPECT_EQ(ldr::set_difference(nonempty_four, nonempty_one), std::unordered_set({7, 8}));

    // completely empty
    EXPECT_EQ(ldr::set_difference(empty_one, empty_one), empty_one);
}

TEST_F(SetTestsFixture, test_symmetric_diff_identity)
{

    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_one, empty_one), nonempty_one);
    EXPECT_EQ(ldr::set_symmetric_difference(empty_one, nonempty_one), nonempty_one);

    // empty results
    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_one, nonempty_one), empty_one);
    EXPECT_EQ(ldr::set_symmetric_difference(empty_one, empty_one), empty_one);
}

TEST_F(SetTestsFixture, test_symmetric_diff_symmetric)
{
    
    const std::unordered_set res1 = {1, 2, 3, 4, 5, 7, 8, 9};
    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_one, nonempty_two), res1);
    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_two, nonempty_one), res1);

    const std::unordered_set res2 = {2, 3, 4, 5, 7, 8};
    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_one, nonempty_four), res2);
    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_four, nonempty_one), res2);

    const std::unordered_set res3 = {4, 5};
    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_one, nonempty_three), res3);
    EXPECT_EQ(ldr::set_symmetric_difference(nonempty_three, nonempty_one), res3);
}
