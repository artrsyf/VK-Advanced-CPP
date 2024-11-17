#pragma once

#include <map>
#include <memory>
#include <variant>

#include "../domain/domain.hpp"
#include "../utils/structures/fixed_vector/fixed_vector.hpp"

enum ReturnCodeType {
    ALLOCATED,
    NEED_TRANSFER,
};

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

inline std::string mapSegmentToString(PassengerSegmentType segmentType)
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

inline PassengerSegmentType mapStringToSegmentType(std::string segmentTypeString)
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

inline PassengerSegmentType mapPassengerStringToSegmentType(std::string segmentTypeString)
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

const std::string PILOT = "PILOT";
const std::string FLIGHT_ATTENDANT = "FLIGHT_ATTENDANT";

enum class CrewMemberType {
    PILOT,
    FLIGHT_ATTENDANT,
};

inline std::string mapCrewToString(CrewMemberType type)
{
    switch (type) {
    case CrewMemberType::PILOT:
        return "Pilot";

    case CrewMemberType::FLIGHT_ATTENDANT:
        return "Flight attendant";

    default:
        return "Unknown";
    }
}

inline CrewMemberType mapStringToCrew(std::string typeString)
{
    if (typeString == PILOT) {
        return CrewMemberType::PILOT;
    } else if (typeString == FLIGHT_ATTENDANT) {
        return CrewMemberType::FLIGHT_ATTENDANT;
    } else {
        std::cout << "Unrecognized crew member type" << std::endl;
        return CrewMemberType::FLIGHT_ATTENDANT;
    }
}

class InvariantI {
public:
    virtual bool invariant() const = 0;
    virtual ~InvariantI() = default;
};

class UnitI : public InvariantI {
public:
    virtual int getLuggageWeight() const = 0;
    virtual int getBaggageWeight() const = 0;
    virtual void showInfo() const = 0;
    virtual ~UnitI() = default;
};

class IdentifiableI {
public:
    virtual std::string getId() const = 0;
};

class FlexibleBaggageI {
public:
    virtual int dropBiggestBaggagePosition() = 0;
};

class HumanUnitI : public UnitI {
public:
    virtual FixedVector<BaggagePos> getBaggagePositions() const = 0;
    virtual std::variant<PassengerSegmentType, CrewMemberType> getType() const = 0;
};

class UnitSegmentI : public HumanUnitI {
public:
    virtual ReturnCodeType add(std::shared_ptr<HumanUnitI> person) = 0;
    virtual void registerBaggage(std::shared_ptr<HumanUnitI> person) = 0;
    virtual int getAllowedWeight() const = 0;
    virtual ~UnitSegmentI() = default;
};