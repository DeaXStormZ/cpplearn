#include <vector>

template<typename T>
struct Meeting
{
    T start;
    T end;
    bool operator <(Meeting<T> m1){    }
};

template<typename T>
bool has_overlaps(const std::vector<Meeting<T>> &meetings2){}

// TODO how to fill this header ? how to compile w/ multiple files ?