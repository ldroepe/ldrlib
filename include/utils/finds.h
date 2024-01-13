#ifndef _LDRLIB_FINDS_H_
#define _LDRLIB_FINDS_H_

#include <optional>
#include <iostream>

namespace ldr
{

template <typename I, typename UnaryPredicate1, typename UnaryPredicate2>
I find_first_before(
    I first, 
    I last,
    UnaryPredicate1 selection_fn, 
    UnaryPredicate2 upper_bound_fn)
{
    I first_before = last;

    while(first != last)
    {
        if(first_before == last && selection_fn(*first))
            first_before = first;
        if(upper_bound_fn(*first))
            return first_before;
        ++first;
    }

    return last;
}

template <typename I, typename UnaryPredicate1, typename UnaryPredicate2>
I find_last_before(
    I first, 
    I last, 
    UnaryPredicate1 selection_fn,
    UnaryPredicate2 upper_bound_fn)
{
    I last_before = last;

    while(first != last)
    {
        if(selection_fn(*first))
            last_before = first;
        if(upper_bound_fn(*first))
            return last_before;
        ++first;
    }

    return last_before;
}

} // namespace ldr
#endif
