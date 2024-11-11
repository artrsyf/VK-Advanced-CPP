#include <string>
#include <iostream>

const std::string FIRST_CLASS_SEGMENT = "FIRST_CLASS_SEGMENT";
const std::string BUSINESS_CLASS_SEGMENT = "BUSINESS_CLASS_SEGMENT";
const std::string ECONOMY_CLASS_SEGMENT = "ECONOMY_CLASS_SEGMENT";

const std::string FIRST_CLASS = "FIRST_CLASS";
const std::string BUSINESS = "BUSINESS";
const std::string ECONOMY = "ECONOMY";

enum class PassengerSegmentType
{
    ECONOMY,
    BUSINESS,
    FIRST_CLASS
};

std::string mapSegmentToString(PassengerSegmentType segmentType)
{
    switch (segmentType) 
    {
        case PassengerSegmentType::ECONOMY: return "Economy";
        case PassengerSegmentType::BUSINESS: return "Business";
        case PassengerSegmentType::FIRST_CLASS: return "First Class";
        default: return "Unknown";
    }
}

PassengerSegmentType mapStringToSegmentType(std::string segmentTypeString) {
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

PassengerSegmentType mapPassengerStringToSegmentType(std::string segmentTypeString) {
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