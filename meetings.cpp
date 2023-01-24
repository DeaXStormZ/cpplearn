#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

struct Meeting
{
    int start;
    int end;
};

bool compareMeeting(Meeting m1, Meeting m2){
    return m1.start < m2.start;
}

void printMeetingVector(std::vector<Meeting> meetings){
    std::cout << "meetings = {";
    for (Meeting n : meetings)
        std::cout << "{\n\tstart: " << n.start << ", \n\tend: " << n.end << "\n},\n";
    std::cout << "};\n";
}

bool has_overlaps(const std::vector<Meeting> &meetings2)
{
    std::vector<Meeting> meetings = meetings2;
    sort(meetings.begin(), meetings.end(), compareMeeting);
    // printMeetingVector(meetings);
    int end = 0;
    for (const Meeting m: meetings){
        if (end > m.start) {
            return true;
        }
        end = m.end;
    }
    return false;
}

int main()
{
    std::vector<Meeting> meetingsOverlapping {
        {.start = 0, .end = 60},
        {.start = 60, .end = 90},
        {.start = 30, .end = 60},
    };
    std::vector<Meeting> meetingsNotOverlapping {
        {.start {0}, .end = 60},
        {.start = 60, .end = 90},
    };
    // std::vector<Meeting> m = &meetings;
    std::cout << "\n" << "meetingsOverlapping : " << has_overlaps(meetingsOverlapping) << "\n";
    std::cout << "\n" << "meetingsNotOverlapping : " << has_overlaps(meetingsNotOverlapping) << "\n";
    return 0;
}