#pragma once

#include <iostream>
#include <map>
#include <string>

const std::string FIRST_CLASS_SEGMENT = "FIRST_CLASS_SEGMENT";
const std::string BUSINESS_CLASS_SEGMENT = "BUSINESS_CLASS_SEGMENT";
const std::string ECONOMY_CLASS_SEGMENT = "ECONOMY_CLASS_SEGMENT";

const std::string FIRST_CLASS = "FIRST_CLASS";
const std::string BUSINESS = "BUSINESS";
const std::string ECONOMY = "ECONOMY";

enum class PassengerSegmentType {
    ECONOMY,
    BUSINESS,
    FIRST_CLASS
};

const std::map<PassengerSegmentType, int> segmentCapacityBind = {
    { PassengerSegmentType::ECONOMY, 200 },
    { PassengerSegmentType::BUSINESS, 10 },
    { PassengerSegmentType::FIRST_CLASS, 4 }
};

std::string mapSegmentToString(PassengerSegmentType segmentType);

PassengerSegmentType mapStringToSegmentType(std::string segmentTypeString);

PassengerSegmentType mapPassengerStringToSegmentType(std::string segmentTypeString);