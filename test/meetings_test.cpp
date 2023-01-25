#include <boost/test/unit_test.hpp>
#include <meetings.h>

BOOST_AUTO_TEST_CASE(overlapping)
{
    std::vector<Meeting<int>> meetingsOverlapping{
        {.start{0}, .end{60}},
        {.start{60}, .end{90}},
        {.start{30}, .end{60}},
    };  
    BOOST_TEST(has_overlaps(meetingsOverlapping));
}

// TODO how to run this test ? how to compile w/ multiple files ?