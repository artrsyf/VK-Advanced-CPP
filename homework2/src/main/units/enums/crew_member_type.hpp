#include <string>
#include <iostream>

const std::string PILOT = "PILOT";
const std::string FLIGHT_ATTENDANT = "FLIGHT_ATTENDANT";

enum class CrewMemberType
{
    PILOT,
    FLIGHT_ATTENDANT,
};

std::string mapCrewToString(CrewMemberType type)
{
    switch (type)
    {
    case CrewMemberType::PILOT:
        return "Pilot";

    case CrewMemberType::FLIGHT_ATTENDANT:
        return "Flight attendant";
    
    default:
        return "Unknown";
    }
}

CrewMemberType mapStringToCrew(std::string typeString) {
    if (typeString == PILOT) {
        return CrewMemberType::PILOT;
    } else if (typeString == FLIGHT_ATTENDANT ) {
        return CrewMemberType::FLIGHT_ATTENDANT;
    } else {
        std::cout << "Unrecognized crew member type" << std::endl;
        return CrewMemberType::FLIGHT_ATTENDANT;
    }
}