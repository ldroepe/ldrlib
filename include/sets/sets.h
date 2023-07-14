#ifndef LDRLIB_SETS_H_
#define LDRLIB_SETS_H_

#include <algorithm>
#include <unordered_set>

namespace ldr
{

template <typename T>
std::unordered_set<T> set_union(const std::unordered_set<T>& first, 
                                const std::unordered_set<T>& second)
{

    std::unordered_set<T> toReturn(first);

    for(const T& y: second)
        toReturn.insert(y);

    return toReturn;
}

template <typename T>
std::unordered_set<T> set_intersection(const std::unordered_set<T>& first,
                                       const std::unordered_set<T>& second)
{

    std::unordered_set<T> toReturn;

    const auto toReturn_inserter = std::inserter(toReturn, std::begin(toReturn));
    const auto contained_in = [&](const std::unordered_set<T>& db) {
        return [&](const T& x) {
            return db.find(x) != std::cend(db);
        };
    };

    std::copy_if(std::cbegin(first), std::cend(first),
                 toReturn_inserter,
                 contained_in(second));
    std::copy_if(std::cbegin(second), std::cend(second),
                 toReturn_inserter,
                 contained_in(first));

    return toReturn;
}

template <typename T>
std::unordered_set<T> set_difference(const std::unordered_set<T>& first,
                                     const std::unordered_set<T>& second)
{
    
    std::unordered_set<T> toReturn;

    const auto not_contained_in = [&](const std::unordered_set<T>& db) {
        return [&](const T& x) {
            return db.find(x) == std::cend(db);
        };
    };

    std::copy_if(std::cbegin(first), std::cend(first),
                 std::inserter(toReturn, std::begin(toReturn)),
                 not_contained_in(second));

    return toReturn;
}

template <typename T>
std::unordered_set<T> set_symmetric_difference(
    const std::unordered_set<T>& first,
    const std::unordered_set<T>& second)
{
    
    std::unordered_set<T> toReturn;

    const auto toReturn_inserter = std::inserter(toReturn, std::begin(toReturn));
    const auto not_contained_in = [&](const std::unordered_set<T>& db) {
        return [&](const T& x) {
            return db.find(x) == std::cend(db);
        };
    };

    std::copy_if(std::cbegin(first), std::cend(first), 
                 toReturn_inserter,
                 not_contained_in(second));
    std::copy_if(std::cbegin(second), std::cend(second),
                 toReturn_inserter,
                 not_contained_in(first));

    return toReturn;
}

} // namespace ldr

#endif
