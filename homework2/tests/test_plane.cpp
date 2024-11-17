#include <cassert>
#include <iostream>
#include <memory>

#include "../units/plane.hpp"

class PlaneTestSuite {
public:
    static void testInvariant()
    {
        Plane plane = Plane();
        auto segment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::ECONOMY, 200));

        plane.add(segment);
        assert(plane.invariant() == true);
    }

    static void testGetLuggageWeight()
    {
        Plane plane = Plane();
        auto segment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::ECONOMY, 200));
        Passenger passenger("some_id", PassengerSegmentType::ECONOMY);

        passenger.addLuggageItem(4);
        segment->add(std::make_shared<Passenger>(passenger));
        plane.add(segment);
        assert(plane.getLuggageWeight() == 4);
    }

    static void testGetBaggageWeight()
    {
        Plane plane = Plane();
        auto segment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::ECONOMY, 200));
        Passenger passenger("some_id", PassengerSegmentType::ECONOMY);

        passenger.addBaggageItem(7);
        segment->add(std::make_shared<Passenger>(passenger));
        plane.add(segment);
        assert(plane.getBaggageWeight() == 7);
    }

    static void testAddPassenger()
    {
        Plane plane = Plane();
        auto segment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::ECONOMY, 200));
        Passenger passenger("some_id", PassengerSegmentType::ECONOMY);
        passenger.addBaggageItem(7);
        passenger.addLuggageItem(4);

        plane.add(segment);
        plane.addPassenger(std::make_shared<Passenger>(passenger));
        assert(plane.getBaggageWeight() == 7 && plane.getLuggageWeight() == 4);
    }

    static void testTransferPassenger()
    {
        Plane plane = Plane();
        auto economySegment = std::make_shared<PassengerSegment>(PassengerSegment(50, PassengerSegmentType::ECONOMY, 200));
        auto businessSegment = std::make_shared<PassengerSegment>(PassengerSegment(10, PassengerSegmentType::BUSINESS, 10));

        Passenger passenger1("some_id1", PassengerSegmentType::ECONOMY);
        passenger1.addLuggageItem(7);
        passenger1.addBaggageItem(8);

        Passenger passenger2("some_id2", PassengerSegmentType::BUSINESS);
        passenger2.addLuggageItem(10);
        passenger2.addBaggageItem(23);

        plane.add(economySegment);
        plane.add(businessSegment);
        plane.addPassenger(std::make_shared<Passenger>(passenger1));
        plane.addPassenger(std::make_shared<Passenger>(passenger2));
        assert(plane.getLuggageWeight() == 17 && plane.getBaggageWeight() == 31);
    }

    static void testShowInfo()
    {
        Plane plane = Plane();
        auto segment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::ECONOMY, 200));
        Passenger passenger("some_id", PassengerSegmentType::ECONOMY);
        passenger.addBaggageItem(7);
        passenger.addLuggageItem(4);

        segment->add(std::make_shared<Passenger>(passenger));
        plane.add(segment);
        plane.addPassenger(std::make_shared<Passenger>(passenger));
        plane.showInfo();
        assert(true);
    }

    static void testSegmentByTypeGetter()
    {
        Plane plane = Plane();

        auto economySegment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::ECONOMY, 200));
        Passenger economyPassenger("some_id1", PassengerSegmentType::ECONOMY);
        economyPassenger.addBaggageItem(5);
        economySegment->add(std::make_shared<Passenger>(economyPassenger));
        plane.add(economySegment);

        auto businessSegment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::BUSINESS, 10));
        Passenger businessPassenger("some_id2", PassengerSegmentType::BUSINESS);
        businessPassenger.addBaggageItem(13);
        businessSegment->add(std::make_shared<Passenger>(businessPassenger));
        plane.add(businessSegment);

        auto firstClassSegment = std::make_shared<PassengerSegment>(PassengerSegment(1000, PassengerSegmentType::FIRST_CLASS, 10));
        Passenger firstClassPassenger("some_id2", PassengerSegmentType::FIRST_CLASS);
        firstClassPassenger.addBaggageItem(13);
        firstClassSegment->add(std::make_shared<Passenger>(firstClassPassenger));
        plane.add(firstClassSegment);

        plane.add(std::make_shared<CrewSegment>(CrewSegment(0, CrewMemberType::PILOT)));
        plane.add(std::make_shared<CrewSegment>(CrewSegment(0, CrewMemberType::FLIGHT_ATTENDANT)));

        EnumVariant economyVariant = PassengerSegmentType::ECONOMY;
        auto checkEconomySegment = plane.getSegmentByType(economyVariant);
        assert(checkEconomySegment->getBaggageWeight() == 5);

        EnumVariant businessVariant = PassengerSegmentType::BUSINESS;
        auto checkBusinessSegment = plane.getSegmentByType(businessVariant);
        assert(checkBusinessSegment->getBaggageWeight() == 13);

        EnumVariant crewVariant = CrewMemberType::PILOT;
        auto checkCrewSegment = plane.getSegmentByType(crewVariant);
        assert(checkCrewSegment->getBaggageWeight() == 0);

        EnumVariant crewVariant2 = CrewMemberType::FLIGHT_ATTENDANT;
        auto checkCrewSegment2 = plane.getSegmentByType(crewVariant2);
        assert(checkCrewSegment->getBaggageWeight() == 0);

        EnumVariant firstClassVariant = PassengerSegmentType::FIRST_CLASS;
        auto checkFirstClassSegment = plane.getSegmentByType(firstClassVariant);
        assert(checkFirstClassSegment->getBaggageWeight() == 13);
    }

    static void runTests()
    {
        testInvariant();
        testGetLuggageWeight();
        testGetBaggageWeight();
        testAddPassenger();
        testTransferPassenger();
        testShowInfo();
        testSegmentByTypeGetter();

        std::cout << "\nSUCCESS: Plane tests passed successfully.\n\n";
    }
};

int main()
{
    PlaneTestSuite::runTests();

    return 0;
}