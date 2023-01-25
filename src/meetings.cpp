#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

template<typename T>
struct Meeting
{
    T start;
    T end;
    bool operator <(Meeting<T> m1){
        return start < m1.start;
    }
};

template<typename T>
void printMeetingVector(std::vector<Meeting<T>> meetings){
    std::cout << "meetings = {";
    for (Meeting<T> n : meetings)
        std::cout << "{\n\tstart: " << n.start << ", \n\tend: " << n.end << "\n},\n";
    std::cout << "};\n";
}

template<typename T>
bool has_overlaps(const std::vector<Meeting<T>> &meetings2)
{
    std::vector<Meeting<T>> meetings = meetings2; // creates a copy to sort inplace. is there a way to avoid this ?
    std::sort(meetings.begin(), meetings.end()); // makes sort on a vector of values. TODO sort a vector of pointers ?
    int end = 0;
    for (const Meeting<T> m: meetings){
        if (end > m.start) {
            return true;
        }
        end = m.end;
    }
    return false;
}

int main()
{
    std::vector<Meeting<int>> meetingsOverlapping{
        {.start{0}, .end{60}},
        {.start{60}, .end{90}},
        {.start{30}, .end{60}},
    };
    std::vector<Meeting<float>> meetingsOverlappingFloat {
        {.start{0.0}, .end{60.3}},
        {.start{60.1}, .end{90.6}},
        {.start{30.5}, .end{60.4}},
    };
    std::vector<Meeting<int>> meetingsNotOverlapping {
        {.start {0}, .end {60}},
        {.start {60}, .end {90}},
    };
    // std::vector<Meeting> m = &meetings;
    std::cout << "\n" << "meetingsOverlapping : " << has_overlaps(meetingsOverlapping) << "\n";
    std::cout << "\n" << "meetingsOverlappingFloat : " << has_overlaps(meetingsOverlappingFloat) << "\n";
    std::cout << "\n" << "meetingsNotOverlapping : " << has_overlaps(meetingsNotOverlapping) << "\n";
    return 0;
}