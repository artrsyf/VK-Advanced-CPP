#include "passenger_segment_type.hpp"

std::string mapSegmentToString(PassengerSegmentType segmentType)
{
    switch (segmentType) {
    case PassengerSegmentType::ECONOMY:
        return "Economy";
    case PassengerSegmentType::BUSINESS:
        return "Business";
    case PassengerSegmentType::FIRST_CLASS:
        return "First Class";
    default:
        return "Unknown";
    }
}

PassengerSegmentType mapStringToSegmentType(std::string segmentTypeString)
{
    if (segmentTypeString == FIRST_CLASS_SEGMENT) {
        return PassengerSegmentType::FIRST_CLASS;
    } else if (segmentTypeString == BUSINESS_CLASS_SEGMENT) {
        return PassengerSegmentType::BUSINESS;
    } else if (segmentTypeString == ECONOMY_CLASS_SEGMENT) {
        return PassengerSegmentType::ECONOMY;
    } else {
        std::cout << "Unrecognized segment type" << std::endl;
        return PassengerSegmentType::ECONOMY;
    }
}

PassengerSegmentType mapPassengerStringToSegmentType(std::string segmentTypeString)
{
    if (segmentTypeString == FIRST_CLASS) {
        return PassengerSegmentType::FIRST_CLASS;
    } else if (segmentTypeString == BUSINESS) {
        return PassengerSegmentType::BUSINESS;
    } else if (segmentTypeString == ECONOMY) {
        return PassengerSegmentType::ECONOMY;
    } else {
        std::cout << "Unrecognized segment type1" << std::endl;
        return PassengerSegmentType::ECONOMY;
    }
}