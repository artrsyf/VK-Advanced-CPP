#include "application/units/crew_member/crew_member_test.hpp"
#include "application/units/passenger/passenger_test.hpp"
#include "application/units/plane/plane_test.hpp"
#include "shared/enums/crew_member_type/crew_member_type_test.hpp"
#include "shared/enums/passenger_segment_type/passenger_segment_type_test.hpp"

int main()
{
    PassengerTestSuite::runTests();
    CrewMemberTestSuite::runTests();
    PlaneTestSuite::runTests();
    CrewMemberTypeTestSuite::runTests();
    PassengerSegmentTypeTestSuite::runTests();
}