#include <iostream>
#include <memory>
#include <cassert>

#include "../../../../main/shared/enums/crew_member_type/crew_member_type.hpp"

class CrewMemberTypeTestSuite{
public:
    static void testMapCrewToString_Pilot() {
        assert(mapCrewToString(CrewMemberType::PILOT) == "Pilot");
    }

    static void testMapCrewToString_FlightAttendant() {
        assert(mapCrewToString(CrewMemberType::FLIGHT_ATTENDANT) == "Flight attendant");
    }

    static void testMapCrewToString_Unknown() {
        assert(mapCrewToString(static_cast<CrewMemberType>(999)) == "Unknown");
    }

    static void testMapStringToCrew_Pilot() {
        assert(mapStringToCrew(PILOT) == CrewMemberType::PILOT);
    }

    static void testMapStringToCrew_FlightAttendant() {
        assert(mapStringToCrew(FLIGHT_ATTENDANT) == CrewMemberType::FLIGHT_ATTENDANT);
    }

    static void testMapStringToCrew_Invalid() {
        assert(mapStringToCrew("UNKNOWN_TYPE") == CrewMemberType::FLIGHT_ATTENDANT);  // Должен вернуть FLIGHT_ATTENDANT по умолчанию
    }

    // Функция для запуска всех тестов
    static void runTests() {
        testMapCrewToString_Pilot();
        testMapCrewToString_FlightAttendant();
        testMapCrewToString_Unknown();
        testMapStringToCrew_Pilot();
        testMapStringToCrew_FlightAttendant();
        testMapStringToCrew_Invalid();

        std::cout << "\nSUCCESS: Crew Member Type tests passed successfully.\n\n";
    }
};