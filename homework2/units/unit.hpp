#pragma once

#include <variant>
#include <memory>

#include "../../../shared/enums/passenger_segment_type/passenger_segment_type.hpp"
#include "../../../shared/enums/crew_member_type/crew_member_type.hpp"
#include "../../../shared/enums/return_code_type/return_code_type.hpp"
#include "../../../utils/structures/fixed_vector/fixed_vector.hpp"
#include "../../../domain/domain.hpp"

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
    virtual int dropBiggestBaggagePosition() = 0;
};

class HumanUnitI : public UnitI
{
public:
    virtual FixedVector<BaggagePos> getBaggagePositions() const = 0;
    virtual std::variant<PassengerSegmentType, CrewMemberType> getType() const = 0;
};

class UnitSegmentI : public HumanUnitI 
{
public:
    virtual ReturnCodeType add(std::shared_ptr<HumanUnitI> person) = 0;
    virtual void registerBaggage(std::shared_ptr<HumanUnitI> person) = 0;
    virtual int getAllowedWeight() const = 0;
    virtual ~UnitSegmentI() = default;
};