#include <functional>
#include <boost/optional.hpp>

template<class Element, class Input>
struct get_reference {
    std::reference_wrapper<const Element> operator()(const Input &input) const { return std::cref(input); }
};

template<class Element>
struct get_reference<Element, class std::reference_wrapper<const Element> > {
    std::reference_wrapper<const Element>
    operator()(const std::reference_wrapper<const Element> &input) const {
        return input;
    }
};

//! utility function to get reference_wrapper of the min element of container according to comp function
//! (directly returns the element if it is already a reference_wrapper)
// comp function should establish strict weak ordering (cf.
// https://en.cppreference.com/w/cpp/named_req/Compare)
template<class C, class Container, class Comparator>
boost::optional <std::reference_wrapper<const C>> min_element(Comparator comp,
                                                              const Container &container) {
    auto best_route_iterator = std::min_element(container.begin(), container.end(), comp);
    if (best_route_iterator == container.end()) {
        return {};
    }
    return {get_reference<C, typename Container::value_type>()(*best_route_iterator)};
}
