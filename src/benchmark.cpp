#include <benchmark/benchmark.h>
#include <thread>

#include <optional>
#include <string>
#include <functional>
#include <limits>
#include <vector>
#include <algorithm>
#include <boost/optional.hpp>
//#include <ranges>

template<class C, class Comparator>
boost::optional<C> get_max_element(Comparator comp,
                                   const std::vector<C> &vector) {
    auto best_route_iterator = // todo check type w/ Jordi
            std::max_element(vector.begin(), vector.end(), comp);
    // best_route_iterator cannot be nullptr since vector isn't empty
    if (best_route_iterator == vector.end()) {
        return {};
    }
    return *best_route_iterator;
}

template<class C>
boost::optional<C> get_max_element_old(const std::function<bool(const C &, const C &)> &comp,
                                       const std::vector<C> &vector) {
    if (vector.empty()) {
        return {};
    }
    auto best_route_iterator = // todo check type w/ Jordi
            std::max_element(vector.begin(), vector.end(), comp);
    // best_route_iterator cannot be nullptr since vector isn't empty
    if (best_route_iterator == vector.end()) {
        return {};
    }
    return *best_route_iterator;
}

struct scheduled_route {
    double departure{};
};

double get_min_departure_date_old(const std::vector<scheduled_route> &route_vector) {
    using C =scheduled_route;
    const std::function<bool(const C &, const C &)> cmp = [](const scheduled_route &a, const scheduled_route &b) {
        return a.departure < b.departure;
    };
    if (boost::optional<scheduled_route> elem = get_max_element_old(
            cmp,
            route_vector)) {
        const scheduled_route &best_route = *elem;
        return best_route.departure;
    }
    return std::numeric_limits<double>::infinity();
}

double get_min_departure_date(const std::vector<scheduled_route> &route_vector) {
    if (boost::optional<scheduled_route> elem = get_max_element(
            [](const scheduled_route &a, const scheduled_route &b) {
                return a.departure < b.departure;
            },
            route_vector)) {
        const scheduled_route &best_route = *elem;
        return best_route.departure;
    }
    return std::numeric_limits<double>::infinity();
}



//double get_min_departure_date_cpp20(const std::vector<scheduled_route>& route_vector) {
//    return std::ranges::max_element(route_vector, {}, &scheduled_route::departure)->departure;
//}

// todo disable cpu scaling
using namespace std::chrono_literals;

auto get_vector() {
    std::vector<scheduled_route> routes{};
    for (int i = 0; i < 2e4; ++i)
        routes.push_back({double(i)});

    return routes;
}

void max_templated(benchmark::State &state) {
    auto v = get_vector();
    for (auto _: state)
        benchmark::DoNotOptimize(get_min_departure_date(v));

}

void max_function(benchmark::State &state) {
    auto v = get_vector();
    for (auto _: state)
        benchmark::DoNotOptimize(get_min_departure_date_old(v));

}

BENCHMARK(max_templated);
BENCHMARK(max_function);

BENCHMARK_MAIN();