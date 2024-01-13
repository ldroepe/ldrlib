#include "finds.h"
#include <vector>
#include <numeric>
#include <algorithm>
#include <gtest/gtest.h>

template <typename I>
std::string to_string(I first, I last)
{
    std::ostringstream oss;
    oss << '[';
    while(first != last) oss << *first++ << ',';
    oss << ']';
    return oss.str();
}

template <typename T>
std::string to_string(std::vector<T> v) { return to_string(std::cbegin(v), std::cend(v)); };

template <typename I, typename T>
std::string found_element_str(I found, const std::vector<T>& v)
{

    std::ostringstream oss;
    oss << "found: " << *found;
    oss << " in ";
    oss << to_string(v);

    return oss.str();
}

namespace fns
{
    const auto is_even = [](int x) { return !(x&1); };
    const auto is_multiple_of = [](int modulus) { 
        return [m=modulus](int x) { return (x % m == 0); };
    };
    const auto is_equal_to = [](int x){
        return [x=x](int y) { return y == x; };
    };
}

class FindsFixture : public ::testing::Test
{

protected:
    
    std::vector<int> vi;

    constexpr static int n = 20;
    constexpr static int modulus = 5;

    FindsFixture(): vi(n) { std::iota(std::begin(vi), std::end(vi), 1); }
};

TEST_F(FindsFixture, test_find_first_before)
{

    auto found = 
        ldr::find_first_before(std::cbegin(vi), std::cend(vi), 
                               fns::is_even, fns::is_multiple_of(modulus));
    //std::cout << std::distance(found, std::cend(vi)) << '\n';
    ASSERT_NE(found, std::cend(vi)) << found_element_str(found, vi);
    EXPECT_EQ(*found, 2) << "vi is: "  << to_string(vi);
}

TEST_F(FindsFixture, test_find_last_before)
{

    const auto last_even = 
        ldr::find_last_before(std::cbegin(vi), std::cend(vi), fns::is_even, fns::is_multiple_of(modulus));

    std::cout << "working with: " << to_string(vi) << '\n';
    ASSERT_NE(last_even, std::cend(vi)) << "dist: " << std::distance(std::cend(vi), last_even);
    const int check_for = []() {
        if(modulus%2 == 0)
            return modulus;
        else
            return modulus-1;
    }();
    EXPECT_EQ(*last_even, check_for);
}

TEST_F(FindsFixture, test_fail_to_find)
{
    
    const auto equal_to = [](int x) { return x == n+1; };
    EXPECT_EQ(std::cend(vi),
              ldr::find_first_before(std::cbegin(vi), std::cend(vi), 
                                     equal_to, fns::is_multiple_of(10)));
}

TEST_F(FindsFixture, test_fail_to_bound)
{
    
    const auto equal_to = [](int x) { return x == n+1; };
    auto found = ldr::find_first_before(std::cbegin(vi), std::cend(vi), fns::is_even, equal_to);
    EXPECT_EQ(std::cend(vi), found) << found_element_str(found, vi);
}
