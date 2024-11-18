#include <cassert>
#include <iostream>
#include <memory>

#include "../../../../main/shared/enums/passenger_segment_type/passenger_segment_type.hpp"

class PassengerSegmentTypeTestSuite {
public:
    static void testMapSegmentToString_Economy()
    {
        assert(mapSegmentToString(PassengerSegmentType::ECONOMY) == "Economy");
    }

    static void testMapSegmentToString_Business()
    {
        assert(mapSegmentToString(PassengerSegmentType::BUSINESS) == "Business");
    }

    static void testMapSegmentToString_FirstClass()
    {
        assert(mapSegmentToString(PassengerSegmentType::FIRST_CLASS) == "First Class");
    }

    static void testMapSegmentToString_Unknown()
    {
        assert(mapSegmentToString(static_cast<PassengerSegmentType>(999)) == "Unknown");
    }

    static void testMapStringToSegmentType_FirstClassSegment()
    {
        assert(mapStringToSegmentType(FIRST_CLASS_SEGMENT) == PassengerSegmentType::FIRST_CLASS);
    }

    static void testMapStringToSegmentType_BusinessClassSegment()
    {
        assert(mapStringToSegmentType(BUSINESS_CLASS_SEGMENT) == PassengerSegmentType::BUSINESS);
    }

    static void testMapStringToSegmentType_EconomyClassSegment()
    {
        assert(mapStringToSegmentType(ECONOMY_CLASS_SEGMENT) == PassengerSegmentType::ECONOMY);
    }

    static void testMapStringToSegmentType_Invalid()
    {
        assert(mapStringToSegmentType("UNKNOWN_SEGMENT") == PassengerSegmentType::ECONOMY);
    }

    static void testMapPassengerStringToSegmentType_FirstClass()
    {
        assert(mapPassengerStringToSegmentType(FIRST_CLASS) == PassengerSegmentType::FIRST_CLASS);
    }

    static void testMapPassengerStringToSegmentType_Business()
    {
        assert(mapPassengerStringToSegmentType(BUSINESS) == PassengerSegmentType::BUSINESS);
    }

    static void testMapPassengerStringToSegmentType_Economy()
    {
        assert(mapPassengerStringToSegmentType(ECONOMY) == PassengerSegmentType::ECONOMY);
    }

    static void testMapPassengerStringToSegmentType_Invalid()
    {
        assert(mapPassengerStringToSegmentType("UNKNOWN_PASSENGER") == PassengerSegmentType::ECONOMY);
    }

    static void runTests()
    {
        testMapSegmentToString_Economy();
        testMapSegmentToString_Business();
        testMapSegmentToString_FirstClass();
        testMapSegmentToString_Unknown();

        testMapStringToSegmentType_FirstClassSegment();
        testMapStringToSegmentType_BusinessClassSegment();
        testMapStringToSegmentType_EconomyClassSegment();
        testMapStringToSegmentType_Invalid();

        testMapPassengerStringToSegmentType_FirstClass();
        testMapPassengerStringToSegmentType_Business();
        testMapPassengerStringToSegmentType_Economy();
        testMapPassengerStringToSegmentType_Invalid();

        std::cout << "\nSUCCESS: Passenger Segment Type tests passed successfully.\n\n";
    }
};