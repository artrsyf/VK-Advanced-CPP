#pragma once

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

std::string mapSegmentToString(PassengerSegmentType segmentType);

PassengerSegmentType mapStringToSegmentType(std::string segmentTypeString);

PassengerSegmentType mapPassengerStringToSegmentType(std::string segmentTypeString);