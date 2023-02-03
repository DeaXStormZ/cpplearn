# Classic STL

## STL Design

goal of the standard library : reduce the space of things we have to worry about.
abstracting from concrete, efficient algorithms to obtain generic algorithms that can be combined w/ different data representations
comprehensive, extensible, efficient, natural

Container <- Iterators -> Algorithms
Containers and algorithms are entirely independent
Iterators provide a common unit of information exchange between them

## Iterators
- provide access to container elements and ordering
- may provide way to modify container elements
- interface specifies :
  - operation complexity
  - manner to observe
  - whether an element can be read from or written to
- **iterators never own the elements**
- categories arranged in hierarchy of _requirements_ :
  - Output : Write forward, single-pass
  - Input : Read forward, single-pass
  - Forward : Access forward, multi-pass
  - Bidirectional : Access forward and backward, multi-pass
  - Random access : Assess arbitrary position, multi-pass
- iterator range : a pair of iterator `[first, last[`. makes testing for loop termination very simple.
  node base containers can use sentinel nodes
- iterator adaptors
  - reverse iterators : `reverse_iterator`
  - insert iterators (inserters) : `back_insert_iterator, front_insert_iterator, insert_iterator`

## Containers
Rpz **sequence** of elements, owns them
- adding/removing elements
- accessing (read/update) elements via associated iterators
- a container iterator understands (and **abstracts**) that container's internal structure
type of containers :
- sequence containers : observe and modify order.
element position is independent of its value
  `vector, deque, list, array, forward_list`
    - vector
      - stores contiguously (except for bool),
      - amortized O(1) insert/erase at the end
      - O(n) insert/erase in the middle
      - const and mutable random-access iterators
      - const and mutable indexing
      - support changing elements value
    - deque :
      cf vector, amortized O(1) insert/erase at begin or end. 
      elements not stored contiguously
    - array : fixed size. random-access iterators
    - list (doubled linked list)
      - splicing, sorting
    - forward list
- associative containers : observe order
element position is dependent of its value
`map, set, multimap, multiset`
  - set : unique key on which to compare
    - find in log
  - multiset, set w/ non unique keys
  - map : key, value. comparator sorting by key. unique keys
  - multimap, map w/ non unique keys
- unordered associative containers : observe order
unsorted collection, element position is irrelevant. impl w/ hash table
`unordered_map, unordered_set, unordered_multimap, unordered_multiset`
  - unordered_set : O(1) element lookup
    - forward iterator
    - keys stored internally in order determined by key hash
  - unordered_map
- container adaptors
`queue, stack, priority_queue`
  - stack : push/pop/top
  - queue : fifo queue

nested type aliases :
- value type `std::vector<int>::value_type // = int`
- reference
- const_reference
- iterator
- const_iterator
- size_type
- difference_type : distance between 2 iterators
bidirectional
- reverse_iterator
- rbegin, rend
- crbegin, crend
- ...

common set of function
- iterator begin, end
- const iterator begin, end
- const iterator cbegin, cend

## Algorithms
- employ iterators interface
- complexity based on algorithm, guarantees made by the iterators
- require at least one pair of iterators
- categories of algorithms
  - non-modifying eg. `lower_bound`
  - modifying
  - removing eg. `remove_copy_if`
  - mutating
  - sorting eg. `sort`
  - sorted range
  - numeric
