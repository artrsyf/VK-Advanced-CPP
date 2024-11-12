#pragma once

#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iterator>
#include <variant>

#include "../interfaces/unit.hpp"

const int INFINITY = std::numeric_limits<int>::max();

const int SEGEMNT_COUNT = 3;

class Passenger : public HumanUnitI, public FlexibleBaggageI, public IdentifiableI
{
public:
    Passenger(
        const std::string & _id,
        PassengerSegmentType _passengerSegment
    ) : 
        id(_id), 
        passengerSegment(_passengerSegment)
    {
        luggage.initialize(getHandLuggagePermission(passengerSegment).allowedQuantity);
        baggage.initialize(getBaggagePermission(passengerSegment).allowedQuantity);
    }

    bool invariant() const override;

    int getBaggageWeight() const override;

    int getLuggageWeight() const override;

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override;

    void addBaggageItem(int weight);

    void addLuggageItem(int weight);

    std::string getId() const override;

    FixedVector<BaggagePos> getBaggagePositions() const override;

    int dropBiggestBaggagePosition() override;
    
    void showInfo() const override;

private:
    std::string id;
    PassengerSegmentType passengerSegment;

    FixedVector<LuggagePos> luggage;
    FixedVector<BaggagePos> baggage;

    static HandLuggagePermission getHandLuggagePermission(PassengerSegmentType bookedPassengerSegmentType);

    static BaggagePermission getBaggagePermission(PassengerSegmentType bookedPassengerSegment);
};

class PassengerSegment : public UnitSegmentI 
{
public:
    PassengerSegment(int _allowedWeight, PassengerSegmentType _type) :
        type(_type),
        allowedWeight(_allowedWeight),
        currentBaggageWeight(0),
        currentLuggageWeight(0) {}

    bool invariant() const override;

    int getBaggageWeight() const override;

    int getLuggageWeight() const override;

    int getAllowedWeight() const override;

    void registerBaggage(std::shared_ptr<HumanUnitI> person) override;

    ReturnCodeType add(std::shared_ptr<HumanUnitI> person) override;

    void remove(std::shared_ptr<HumanUnitI> person) override;

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override;

    void showInfo() const override;

    FixedVector<BaggagePos> getBaggagePositions() const override;

private:
    PassengerSegmentType type;
    int allowedWeight;
    int currentBaggageWeight;
    int currentLuggageWeight;
    std::vector<std::shared_ptr<HumanUnitI>> persons;
    std::vector<std::shared_ptr<HumanUnitI>> transfered;
};