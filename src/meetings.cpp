#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

template <typename T> // TODO static assert, T must be comparable
struct Meeting
{
    T start;
    T end;
    bool operator<(const Meeting<T> &m1)
    {
        return start < m1.start;
    }
};

template <typename T>
void printMeetingVector(std::vector<Meeting<T>> &meetings)
{
    std::cout << "meetings = {";
    for (Meeting<T> n : meetings)
        std::cout << "{\n\tstart: " << n.start << ", \n\tend: " << n.end << "\n},\n";
    std::cout << "};\n";
}

template <typename T>
bool comp(const Meeting<T> &m1, const Meeting<T> &m2)
{
    return m1.start < m2.start;
}; // TODO use the op of struct ? seems not transfering to reference_wrapper

template <typename T>
std::vector<std::reference_wrapper<const Meeting<T>>> get_ref_vector(const std::vector<Meeting<T>> &meetings) {
    // create vector of references
    std::vector<std::reference_wrapper<const Meeting<T>>> mv;
    mv.reserve(meetings.size());
    for (const Meeting<T> &meeting : meetings)
    {
        mv.emplace_back(meeting); // calls cref due to const Meetings<T>
    }
    return mv;
}

template <typename T>
bool has_overlaps(const std::vector<Meeting<T>> &meetings)
{
    // pas besoin de faire un vecteur de référence pour des types triviaux (faut benchmark). reference plus lourde qu'un int.
    auto mv = make_reference_vector(meetings);
    std::sort(mv.begin(), mv.end());
    T end{};
    for (const Meeting<T> &m : mv) // Mettre des const ref tout le temps !
    { // todo utiliser clang tidy
        if (end > m.start)
        {
            return true;
        }
        end = m.end;
    }
    return false;
}

template <typename T>
std::vector<Meeting<T>> resolve_overlaps(const std::vector<Meeting<T>> &meetings)
{
}

int main()
{
    std::vector<Meeting<int>> meetingsOverlapping{
        {.start=0, .end=60},
        {.start=60, .end=90},
        {.start=30, .end=60},
    };
    std::vector<Meeting<float>> meetingsOverlappingFloat{
        {.start=0.0, .end=60.3},
        {.start=60.1, .end=90.6},
        {.start=30.5, .end=60.4},
    };
    std::vector<Meeting<int>> meetingsNotOverlapping{
        {.start=0, .end=60},
        {.start=60, .end=90},
    };

    // std::vector<Meeting> m = &meetings;
    std::cout << "\n"
              << "meetingsOverlapping : " << has_overlaps(meetingsOverlapping) << "\n";
    std::cout << "\n"
              << "meetingsOverlappingFloat : " << has_overlaps(meetingsOverlappingFloat) << "\n";
    std::cout << "\n"
              << "meetingsNotOverlapping : " << has_overlaps(meetingsNotOverlapping) << "\n";
    return 0;
}