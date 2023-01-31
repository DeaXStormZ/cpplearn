#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <utility>
#include <functional>
#include <forward_list>

// SFINAE

template<class T> // meta fonction type -> type
using ref_type = std::reference_wrapper<const T>;

template<class C> // meta fonction type -> type
using ref_vector = std::vector<ref_type<typename C::value_type>>;

// does C have a size ?
template <class C, class = void>
struct sizeable : std::false_type {};


template <class C> // le compiler essaie de prendre la spécialization, sinon fallback sur le template initial
struct sizeable<C, std::void_t<decltype(std::declval<const C &>().size())>> : std::true_type {}; // decltype associe a une expression son type
// on utilise void pour que ce soit générique. en l'occurence ça compilerait avec size_t car on s'attend que les méthodes size renvoient un size_t

// concept C++20


template<class C>
inline constexpr bool sizeable_v = sizeable<C>::value;

static_assert(sizeable_v<std::vector<int>>);
static_assert(sizeable_v<std::list<int>>);
static_assert(not sizeable_v<std::forward_list<int>>);

// inline evite les declarations multiples si plusieurs TU

template<class C>
ref_vector<C> make_reference_vector(const C &elements) {
    // create vector of references
    ref_vector<C> mv;
    if constexpr (sizeable_v<C>)
        mv.reserve(elements.size());
    for (const auto &elem: elements)
        mv.emplace_back(elem); // calls cref due to const Meetings<T>
    return mv;
}


template<class C>
ref_vector<C> omni_sort(const C &c) {
    auto rv = make_reference_vector(c);
    std::sort(rv.begin(), rv.end());
    return rv;
}

using X = std::vector<int>::value_type; // X = int
using Y = std::list<float>::value_type;


template<class C>
void print_container(const C &vec) {
    std::cout << "container = {";
    for (const auto &n: vec)
        std::cout << n << ",\n";
    std::cout << "};\n";
}

int main() {
    std::vector<int> vec{1, 5, 4, 2, 23};
    print_container(omni_sort(vec));
    // besoin d'un random access iterator pour sort

    std::list<int> l{1, 5, 4, 2, 23};
    print_container(omni_sort(l));

    std::forward_list<int> fl{1, 5, 4, 2, 23};
    print_container(omni_sort(fl));

    return 0;
}