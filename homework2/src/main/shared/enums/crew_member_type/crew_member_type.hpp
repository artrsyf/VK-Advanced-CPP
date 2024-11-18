#pragma once

#include <iostream>
#include <string>

const std::string PILOT = "PILOT";
const std::string FLIGHT_ATTENDANT = "FLIGHT_ATTENDANT";

enum class CrewMemberType {
    PILOT,
    FLIGHT_ATTENDANT,
};

std::string mapCrewToString(CrewMemberType type);

CrewMemberType mapStringToCrew(std::string typeString);