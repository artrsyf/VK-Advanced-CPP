#pragma once

#include <variant>
#include <memory>

#include "../../../shared/enums/passenger_segment_type/passenger_segment_type.hpp"
#include "../../../shared/enums/crew_member_type/crew_member_type.hpp"

class InvariantI 
{
public:
    virtual bool invariant() const = 0;
    virtual ~InvariantI() = default;
};

class UnitI : public InvariantI
{
public:
    virtual int getLuggageWeight() const = 0;
    virtual int getBaggageWeight() const = 0;
    virtual void showInfo() const = 0;
    virtual ~UnitI() = default;   
};

class IdentifiableI
{
public:
    virtual std::string getId() const = 0;
};

class FlexibleBaggageI
{
public:
    virtual void dropSmallestBaggagePosition() = 0;
};

class HumanUnitI : public UnitI
{
public:
    virtual std::variant<PassengerSegmentType, CrewMemberType> getType() const = 0;
};

class UnitSegmentI : public HumanUnitI 
{
public:
    virtual void add(std::shared_ptr<HumanUnitI> person) = 0;
    virtual void remove(std::shared_ptr<HumanUnitI> person) = 0;
    virtual int getAllowedBaggageWeight() const = 0;
    virtual ~UnitSegmentI() = default;
};