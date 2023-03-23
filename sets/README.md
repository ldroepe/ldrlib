# Set Algorithms on ... Sets !

Reading through the STL algorithms, one will quickly discover that there are a 
host of algorithms for set operations -- difference, intersection, symmetric 
difference, &c. However, these algorithms work on "sets" ... which according to
C++ are ... *sorted collections*. Huh.

As someone with a background in mathematics, when I think of a set, I think of
a collection of unique unordered elements (with posisbly infinite cardinality, 
but that's another project for another time); in other words, I think of 
`std::unordered_set`. `std::unordered_set` is very useful & I use it quite often, but
the problem that I have with it is that it doesn't have access to those very
useful algorithms that the STL provides on sets!

So, here's a naive implementation of the algorithms that the STL supports on sets,
but specialized for the case of `std::unordered_set`. Note that many of the 
set algorithms provided in the STL have time complexities that arise due to the 
sorted nature of their input. As I am working with unsorted data, the 
complexity of these same algorithms may change!

## Supported Algorithms

- [`set_union`](#set_union)
- [`set_intersection`](#set_intersection)
- [`set_difference`](#set_difference)
- [`set_symmetric_difference`](#set_symmetric_difference)

### `set_union`

The union of two sets, `A` and `B`, is defined as a third set, `C`, which contains all elements of `A` *and* `B`. Note that if an element is present in *both* `A` and `B`, it will still only appear once in `C`, since elements of sets are unique.

In mathematical terms: 
$A \cup B = \{x \mid x \in A \lor x \in B \}$

<table>
    <tr>
        <td colspan="3" style="text-align:center">Complexity</td>
    </tr>
    <tr>
    <td></td>
    <td>Average</td>
    <td>Worst</td>
    </tr>
    <tr>
        <td>Space</td>
        <td></td>
        <td><i>O(n+m)</i></td>
    </tr>
    <tr>
        <td>Time</td>
        <td><i>O(n+m)</i></td>
        <td><i>O(nm<sup>2</sup>+nm)</i></td>
    </tr>
</table>

#### Calculation of Worst Case Time Complexity

The worst case time complexity of `std::unordered_set::insert` is $O(n)$. At the time of calling `std::unordered_set::insert`, the current size of the set which is returned is $n$. Thus, we have:

$$
n + (n+1) + (n+2) + ... + (n+m) \\
= n * \left( \sum_{i=1}^m i \right) \\
= n * \left( \frac{m*(m+1)}{2} \right) \\ 
= n * \left( \frac{m^2}{2} + \frac{m}{2} \right) \\
= \frac{nm^2}{2} + \frac{nm}{2} \\
\implies O(nm^2 + nm)
$$

### `set_intersection`

The intersection of two sets, `A` and `B`, is defined as a third set, `C`, which contains only those elements which are elements of `A` *and* `B`.

In mathematical terms:
$A \cap B = \{x \mid x \in A \land x \in B \}$

<table>
    <tr>
        <td colspan="3" style="text-align:center">Complexity</td>
    </tr>
    <tr>
    <td></td>
    <td>Average</td>
    <td>Worst</td>
    </tr>
    <tr>
        <td>Space</td>
        <td></td>
        <td><i>O(n+m)</i></td>
    </tr>
    <tr>
        <td>Time</td>
        <td><i>O(n+m)</i></td>
        <td><i>O(n<sup>2</sup> + m<sup>2</sup> + nm + n + m)</i></td>
    </tr>
</table>

#### Calculation of Worst Case Time Complexity

The worst case time complexities of `std::unordered_set::insert` and `std::unordered_set::find` are $O(n)$. This means that we call `std::unordered_set::insert` and `std::unordered_set::find` $n$ times with their worst case complexity and are therefore left with:

$$ \left( \sum_{i=1}^n i \right) + \left( \sum_{j=1}^m j \right) + 2nm \\
= \frac{n^2 + m^2}{2} + \frac{n + m}{2} + 2nm \\
\implies O(n^2 + m^2 + nm + n + m)
$$

### `set_difference`

The difference of two sets, `A` and `B`, is defined as a third set, `C`, which contains all elements in `A` which are *not* also contained in `B`.

In mathematical terms:
$A \setminus B = \{ x \mid x \in A \land x \notin B\}$

<table>
    <tr>
        <td colspan="3" style="text-align:center">Complexity</td>
    </tr>
    <tr>
    <td></td>
    <td>Average</td>
    <td>Worst</td>
    </tr>
    <tr>
        <td>Space</td>
        <td></td>
        <td><i>O(n)</i></td>
    </tr>
    <tr>
        <td>Time</td>
        <td><i>O(n)</td>
        <td><i>O(n<sup>2</sup>+nm+n)</i></td>
    </tr>
</table>

#### Calculation of Worst Case Time Complexity

`set_difference` is implemented as (essentially) one half of `set_intersection`, so we have only one summation ($1$ to $n$) and a single product term.

#### `set_symmetric_difference`

The symmetric difference of two sets, `A` and `B`, is defined as a third set, `C`, which contains those elements which are in `A` or `B`, but not *both* `A` and `B`.

In mathematical terms:
$A \ominus B = \{ x \mid (x \in A \lor x \in B) \land (x \notin A \cap B) \}$

<table>
    <tr>
        <td colspan="3" style="text-align:center">Complexity</td>
    </tr>
    <tr>
    <td></td>
    <td>Average</td>
    <td>Worst</td>
    </tr>
    <tr>
        <td>Space</td>
        <td></td>
        <td><i>O(n+m)</i></td>
    </tr>
    <tr>
        <td>Time</td>
        <td><i>O(n+m)</td>
        <td><i>O(n<sup>2</sup> + m<sup>2</sup> + nm + n + m)</i></td>
    </tr>
</table>

#### Calculation of Worst Case Time Complexity

`set_symmetric_difference` is implemented in the exact same way as `set_intersection`, just with a negated predicate. Thus, their runtimes are going to be the same.

## Todo

- Better Testing Code
    - Move away from assert
    - Include tests using different types
- Generalize this code to work with other unordered data structures
