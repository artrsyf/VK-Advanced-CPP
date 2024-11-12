#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <variant>

#include "../interfaces/unit.hpp"

const int CREW_MEMBER_COUNT = 8;

class CrewMember : public HumanUnitI
{
public:
    CrewMember(std::string _id, CrewMemberType _type) : id(_id), type(_type) {}

    bool invariant() const override;

    int getLuggageWeight() const override;

    int getBaggageWeight() const override;

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override;

    FixedVector<BaggagePos> getBaggagePositions() const override;

    void showInfo() const override;

private:
    std::string id;
    CrewMemberType type;
};

class CrewSegment : public UnitSegmentI 
{
public:
    CrewSegment(int _allowedWeight, CrewMemberType _type) :
        type(_type),
        allowedWeight(_allowedWeight),
        currentBaggageWeight(0),
        currentLuggageWeight(0) {}

    bool invariant() const override;

    int getBaggageWeight() const override;

    int getLuggageWeight() const override;

    void registerBaggage(std::shared_ptr<HumanUnitI> person) override { /* NOT IMPLEMENTED */ };

    int getAllowedBaggageWeight() const override;

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override;

    ReturnCodeType add(std::shared_ptr<HumanUnitI> person) override;

    void remove(std::shared_ptr<HumanUnitI> person) override;

    FixedVector<BaggagePos> getBaggagePositions() const override;

    void showInfo() const override;

private:
    CrewMemberType type;
    int allowedWeight;
    int currentBaggageWeight;
    int currentLuggageWeight;
    std::vector<std::shared_ptr<HumanUnitI>> persons;
};