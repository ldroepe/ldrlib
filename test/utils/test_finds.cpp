#include "finds.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <gtest/gtest.h>

class FindsFixture : public ::testing::Test
{

protected:
    
    std::vector<int> v;

    constexpr static int modulus = 5;
    constexpr static auto is_even = [](int x) { return !(x&1); };
    constexpr static auto is_multiple_of = [](int modulus) { 
        return [&](int x) { return (x % modulus == 0); };
    };

    template <typename T>
    std::string to_string(std::vector<T> v)
    {
        return to_string(std::cbegin(v), std::cend(v));
    }

    template <typename I>
    std::string to_string(I first, I last)
    {
        std::ostringstream oss;
        oss << '[';
        while(first != last) oss << *first++ << ',';
        oss << ']';
        return oss.str();
    }

    FindsFixture(): v(20) { std::iota(std::begin(v), std::end(v), 1); }
};

TEST_F(FindsFixture, test_find_first_before)
{

    const auto first_even =
        ldr::find_first_before(std::cbegin(v), std::cend(v), is_multiple_of(modulus), is_even);
    EXPECT_EQ(*first_even, 2) << "v is: "  << to_string(v);
}

TEST_F(FindsFixture, test_find_last_before)
{

    const auto last_even = 
        ldr::find_last_before(std::cbegin(v), std::cend(v), is_multiple_of(modulus), is_even);
    EXPECT_EQ(*last_even, 20);
}
