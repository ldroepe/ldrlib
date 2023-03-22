#include <cassert>
#include <iostream>
#include "../sets.h"

// Well I mean, assert is a macro too ... right ? :|
#define assertm(exp, msg) assert(((void)(msg), (exp)))

template <typename T>
bool equal_sets(const std::unordered_set<T>& first, const std::unordered_set<T>& second)
{
    return first == second;
}

template <typename T>
void show_set(const std::unordered_set<T>& s)
{
    std::cout << '{';
    for(const T& x: s)
        std::cout << x << ',';
    std::cout << "}\n";
}

void test_equal_sets()
{
    const std::unordered_set<int> one = {1,2,3,4,5};
    const std::unordered_set<int> two = {1,2,3,4,5};
    const std::unordered_set<int> three = {1,2,3};
    const std::unordered_set<int> four;

    assertm(equal_sets(one, one), "TES: one == one");
    assertm(equal_sets(one, two), "TES: one == two");
    assertm(equal_sets(two, one), "TES: two == one");
    assertm(!equal_sets(three, one), "TES: three =/= one");
    assertm(!equal_sets(four, three), "TES: four =/= three");
    assertm(equal_sets(four, four), "TES: four == four");
}

void test_set_union()
{
    const std::unordered_set<int> nonempty_one = {1, 2, 3, 4, 5};
    const std::unordered_set<int> nonempty_two = {7, 8, 9};
    const std::unordered_set<int> nonempty_three = {1, 2, 3};
    const std::unordered_set<int> nonempty_four = {7, 8, 1};
    const std::unordered_set<int> empty_one;

    // identity
    const auto returned_one = ldr::set_union(nonempty_one, empty_one);
    assertm(equal_sets(returned_one, nonempty_one), "TU: {1,2,3,4,5} U {} == {1,2,3,4,5}");
    const auto returned_two = ldr::set_union(empty_one, nonempty_one);
    assertm(equal_sets(returned_two, nonempty_one), "TU: {} U {1,2,3,4,5} == {1,2,3,4,5}");
    const auto returned_three = ldr::set_union(empty_one, empty_one);
    assertm(equal_sets(returned_three, empty_one), "TU: {} U {} == {}");

    // associativity
    const auto returned_four = ldr::set_union(nonempty_one, nonempty_two);
    assertm(equal_sets(returned_four, {1, 2, 3, 4, 5, 7, 8, 9}),
            "TU: {1,2,3,4,5} U {7,8,9} == {1,2,3,4,5,7,8,9");
    const auto returned_five = ldr::set_union(nonempty_two, nonempty_one);
    assertm(equal_sets(returned_five, {1,2,3,4,5,7,8,9}),
            "TU: {7,8,9}U{1,2,3,4,5} == {1,2,3,4,5,7,8,9}");

    // uniqueness of elements
    const auto returned_six = ldr::set_union(nonempty_one, nonempty_three);
    assertm(equal_sets(returned_six, nonempty_one), "TU: {1,2,3,4,5} U {1,2,3} == {1,2,3,4,5}");
    const auto returned_seven = ldr::set_union(nonempty_four, nonempty_one);
    assertm(equal_sets(returned_seven, {1,2,3,4,5,7,8}),
            "TU: {7,8,1} U {1,2,3,4,5} == {1,2,3,4,5,7,8}");
}

void test_set_intersection()
{

    const std::unordered_set<int> nonempty_one = {1,2,3,4,5};
    const std::unordered_set<int> nonempty_two = {1,2,3};
    const std::unordered_set<int> nonempty_three = {1,7,8};
    const std::unordered_set<int> empty_one;

    // identity
    const std::unordered_set<int> returned_one = ldr::set_intersection(nonempty_one, nonempty_one);
    assertm(equal_sets(returned_one, nonempty_one), "TSI: {1,2,3,4,5}n{1,2,3,4,5} == {1,2,3,4,5}");

    // symmetry
    const auto returned_two = ldr::set_intersection(nonempty_one, empty_one);
    assertm(equal_sets(returned_two, empty_one), "TSI: {1,2,3,4,5}n{} == {}");
    const auto returned_three = ldr::set_intersection(empty_one, nonempty_one);
    assertm(equal_sets(returned_three, empty_one), "TSI: {}n{1,2,3,4,5} == {}");
    const auto returned_four = ldr::set_intersection(nonempty_one, nonempty_two);
    assertm(equal_sets(returned_four, nonempty_two), "TSI: {1,2,3,4,5}n{1,2,3} == {1,2,3}");
    const auto returned_five = ldr::set_intersection(nonempty_two, nonempty_one);
    assertm(equal_sets(returned_five, nonempty_two), "TSI: {1,2,3}n{1,2,3,4,5} == {1,2,3}");

    // misc
    const auto returned_six = ldr::set_intersection(nonempty_one, nonempty_three);
    assertm(equal_sets(returned_six, {1}), "TSI: {1,2,3,4,5}n{1,7,8} == {1}");
    const auto returned_seven = ldr::set_intersection(empty_one, empty_one);
    assertm(equal_sets(returned_seven, empty_one), "TSI: {}n{} == {}");
}

void test_set_difference()
{
    
    const std::unordered_set<int> nonempty_one = {1,2,3,4,5};
    const std::unordered_set<int> nonempty_two = {1,2,3};
    const std::unordered_set<int> nonempty_three = {7,8,9};
    const std::unordered_set<int> nonempty_four = {1,10,11};
    const std::unordered_set<int> empty_one;

    //identity
    const auto returned_one = ldr::set_difference(nonempty_one, nonempty_three);
    assertm(equal_sets(nonempty_one, returned_one), "TSD: {1,2,3,4,5}\\{7,8,9} == {1,2,3,4,5}");
    const auto returned_two = ldr::set_difference(nonempty_three, nonempty_one);
    assertm(equal_sets(returned_two, nonempty_three), "TSD: {7,8,9}\\{1,2,3,4,5} == {7,8,9}");
    const auto returned_three = ldr::set_difference(nonempty_one, empty_one);
    assertm(equal_sets(returned_three, nonempty_one), "TSD: {1,2,3,4,5}\\{} == {1,2,3,4,5}");
    const auto returned_four = ldr::set_difference(empty_one, nonempty_one);
    assertm(equal_sets(returned_four, empty_one), "TSD: {}\\{1,2,3,4,5} == {}");

    //full subset
    const auto returned_five = ldr::set_difference(nonempty_one, nonempty_two);
    assertm(equal_sets(returned_five, {4,5}), "TSD: {1,2,3,4,5}\\{1,2,3} == {4,5}");
    const auto returned_six = ldr::set_difference(nonempty_two, nonempty_one);
    assertm(equal_sets(returned_six, empty_one), "TSD: {1,2,3}\\{1,2,3,4,5} == {}");

    //partial subset
    const auto returned_seven = ldr::set_difference(nonempty_one, nonempty_four);
    assertm(equal_sets(returned_seven, {2,3,4,5}), "TSD: {1,2,3,4,5}\\{1,10,11} == {2,3,4,5}");
    const auto returned_eight = ldr::set_difference(nonempty_four, nonempty_one);
    assertm(equal_sets(returned_eight, {10,11}), "TSD: {1,10,11}\\{1,2,3,4,5} == {10,11}");

    // completely empty
    const auto returned_nine = ldr::set_difference(empty_one, empty_one);
    assertm(equal_sets(returned_nine, empty_one), "TSD: {}\\{} == {}");
}

void test_set_symmetric_difference()
{

    const std::unordered_set<int> nonempty_one = {1,2,3,4,5};
    const std::unordered_set<int> nonempty_two = {6,7,8,9,10};
    const std::unordered_set<int> nonempty_three = {1,2,7,8,9};
    const std::unordered_set<int> empty_one;

    // identity
    const auto returned_one = ldr::set_symmetric_difference(nonempty_one, empty_one);
    assertm(equal_sets(returned_one, nonempty_one), "TSSD: {1,2,3,4,5}(-){} == {1,2,3,4,5}");
    const auto returned_two = ldr::set_symmetric_difference(empty_one, nonempty_one);
    assertm(equal_sets(returned_two, nonempty_one), "TSSD: {}(-){1,2,3,4,5} == {1,2,3,4,5}");
    assertm(equal_sets(returned_one, returned_two), "TSSD: {1,2,3,4,5}(-){} == {}(-){1,2,3,4,5}");

    // empty results
    const auto returned_three = ldr::set_symmetric_difference(nonempty_one, nonempty_one);
    assertm(equal_sets(returned_three, empty_one), "TSSD: {1,2,3,4,5}(-){1,2,3,4,5} == {}");
    const auto returned_four = ldr::set_symmetric_difference(empty_one, empty_one);
    assertm(equal_sets(returned_four, empty_one), "TSSD: {}(-){} == {}");

    // nonempty results & symmetry
    const auto returned_five = ldr::set_symmetric_difference(nonempty_one, nonempty_two);
    assertm(equal_sets(returned_five, {1,2,3,4,5,6,7,8,9,10}),
            "TSSD: {1,2,3,4,5}(-){6,7,8,9,10} == {1,2,3,4,5,6,7,8,9,10}");
    const auto returned_six = ldr::set_symmetric_difference(nonempty_two, nonempty_one);
    assertm(equal_sets(returned_six, {1,2,3,4,5,6,7,8,9,10}), 
            "TSSD: {6,7,8,9,10}(-){1,2,3,4,5} == {1,2,3,4,5,6,7,8,9,10}");
    assertm(equal_sets(returned_five, returned_six), 
            "TSSD: {1,2,3,4,5}(-){6,7,8,9,10} == {6,7,8,9,10}(-){1,2,3,4,5}");
    const auto returned_seven = ldr::set_symmetric_difference(nonempty_one, nonempty_three);
    assertm(equal_sets(returned_seven, {3,4,5,7,8,9}),
            "TSSD: {1,2,3,4,5}(-){1,2,7,8,9} == {3,4,5,7,8,9}");
    const auto returned_eight = ldr::set_symmetric_difference(nonempty_three, nonempty_one);
    assertm(equal_sets(returned_eight, {3,4,5,7,8,9}),
            "TSSD: {1,2,7,8,9}(-){1,2,3,4,5} == {3,4,5,7,8,9}");
    assertm(equal_sets(returned_seven, returned_eight),
            "TSSD: {1,2,3,4,5}(-){1,2,7,8,9} == {1,2,7,8,9}(-){1,2,3,4,5}");
}

int main()
{
    std::cout << "Testing equal_sets function ...\n";
    test_equal_sets();

    std::cout << "Testing ldr::set_union ...\n";
    test_set_union();

    std::cout << "Testing ldr::set_intersection ... \n";
    test_set_intersection();

    std::cout << "Testing ldr::set_difference ... \n";
    test_set_difference();

    std::cout << "Testing ldr::set_symmetric_difference ... \n";
    test_set_symmetric_difference();

    std::cout << "All done!!\n";
}
