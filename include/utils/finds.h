#ifndef _LDRLIB_FINDS_H_
#define _LDRLIB_FINDS_H_

#include <optional>

namespace ldr
{

template <typename InputIt, typename UnaryPredicate1, typename UnaryPredicate2>
InputIt find_first_before(InputIt first, InputIt last,
                          UnaryPredicate1 upper_bound_fn, UnaryPredicate2 selection_fn)
{
    std::optional<InputIt> first_before;

    for( ; first != last; ++first)
    {
        if(!first_before.has_value() && selection_fn(*first))
            first_before.emplace(first);

        if(upper_bound_fn(*first))
            return first_before.value_or(first);
    }

    return last;
}

template <typename InputIt, typename UnaryPredicate1, typename UnaryPredicate2>
InputIt find_last_before(InputIt first, InputIt last, 
                          UnaryPredicate1 upper_bound_fn, UnaryPredicate2 selection_fn)
{
    std::optional<InputIt> last_before;

    for( ; first != last; ++first)
    {
        if(selection_fn(*first))
            last_before.emplace(first);

        if(upper_bound_fn(*first))
            return last_before.value_or(first);
    }

    return last;
}

} // namespace ldr
#endif
