# Set Algorithms on ... Sets !

Reading through the STL algorithms, one will quickly discover that there are a 
host of algorithms for set operations -- difference, intersection, symmetric 
difference, &c. However, these algorithms work on "sets" ... which according to
C++ are ... *sorted collections*. Huh.

As someone with a background in mathematics, when I think of a set, I think of
a collection of unique unordered elements (with posisbly infinite cardinality, 
but that's another project for another time); in other words, I think of 
`std::unordered_set`. `std::unordered_set` is very useful & I use it often, but
the problem that I have with it is that it doesn't have access to those very
useful algorithms that the STL provides on sets!

So, here's an implementation of the algorithms that the STL supports on sets,
but specialized for the case of `std::unordered_set`. Note that many of the 
set algorithms provided in the STL have complexities that arise due to the 
sorted nature of their input. As I am working with unsorted data, the 
complexity of these same algorithms may change!

## Supported Algorithms

- (set\_union)[https://cplusplus.com/reference/algorithm/set\_union/]
- (set\_intersection)[https://cplusplus.com/reference/algorithm/set\_intersection/]
- (set\_difference)[https://cplusplus.com/reference/algorithm/set\_difference/]
- (set\_symmetric\_difference)[https://cplusplus.com/reference/algorithm/set\_symmetric\_difference/]

## Todo

- Better Testing Code
    - Move away from assert
    - Include tests using different types
- Generalize this code to work with other unordered data structures
