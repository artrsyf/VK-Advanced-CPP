#include <iostream>
#include <sstream>
#include <string>
#include <limits>
#include <chrono>

#include "application/units/plane/plane.hpp"

std::string generateUniqueID()
{
    auto now = std::chrono::system_clock::now();
    auto duration = now.time_since_epoch();

    return std::to_string(duration.count());
}

std::shared_ptr<Passenger> createPassengerFromInput(const std::string &input)
{
    std::istringstream ss(input);
    std::string segmentTypeString;
    ss >> segmentTypeString;

    PassengerSegmentType segment = mapPassengerStringToSegmentType(segmentTypeString);
    std::shared_ptr<Passenger> passenger = std::make_shared<Passenger>(generateUniqueID(), segment);

    if (segment == PassengerSegmentType::ECONOMY)
    {
        int luggage = 0, baggage = 0;
        ss >> luggage >> baggage;
        
        if (luggage > 0) passenger->addLuggageItem(luggage);
        if (baggage > 0) passenger->addBaggageItem(baggage);
    }
    else
    {
        int luggage1 = 0, luggage2 = 0, baggage1 = 0, baggage2 = 0;
        ss >> luggage1 >> luggage2 >> baggage1 >> baggage2;

        if (luggage1 > 0) passenger->addLuggageItem(luggage1);
        if (luggage2 > 0) passenger->addLuggageItem(luggage2);

        if (baggage1 > 0) passenger->addBaggageItem(baggage1);
        if (baggage2 > 0) passenger->addBaggageItem(baggage2);
    }

    return passenger;
}

void run(std::istream & input, std::ostream & output)
{
    Plane plane = Plane();

    std::string segmentTypeString = "";
    int boundWeight = 0;

    for (size_t i = 0; i < SEGEMNT_COUNT; ++i)
    {
        input >> segmentTypeString >> boundWeight;
        PassengerSegmentType segmentTypeEnum = mapStringToSegmentType(segmentTypeString);
        int maxNum = segmentCapacityBind.at(segmentTypeEnum);
        plane.add(std::make_shared<PassengerSegment>(PassengerSegment(boundWeight, segmentTypeEnum, maxNum)));
    }

    plane.add(std::make_shared<CrewSegment>(CrewSegment(0, CrewMemberType::PILOT)));
    plane.add(std::make_shared<CrewSegment>(CrewSegment(0, CrewMemberType::FLIGHT_ATTENDANT)));

    std::string typeString = "";
    int boundBaggageMock1 = 0, boundBaggageMock2 = 0;

    for (size_t i = 0; i < CREW_MEMBER_COUNT; ++i)
    {
        input >> typeString >> boundBaggageMock1 >> boundBaggageMock2;
        CrewMemberType typeEnum = mapStringToCrew(typeString);
        std::shared_ptr<CrewMember> crewMember = std::make_shared<CrewMember>(generateUniqueID(), typeEnum);

        // crewMember->showInfo();
        plane.addPassenger(crewMember);
    }

    input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::string inputString = "";

    while (std::getline(input, inputString) && !inputString.empty())
    {
        std::shared_ptr<Passenger> passenger = createPassengerFromInput(inputString);
        plane.addPassenger(passenger);
    }

    plane.showInfo();
}

int main()
{
    run(std::cin, std::cout);

    return 0;
}