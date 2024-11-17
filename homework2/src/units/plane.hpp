#pragma once

#include <variant>

#include "./passengers.hpp"
#include "./crew_members.hpp"

using EnumVariant = std::variant<PassengerSegmentType, CrewMemberType>;

class PlaneTestSuite;

class Plane : public UnitI
{
public:
    bool invariant() const override;

    int getLuggageWeight() const override;

    int getBaggageWeight() const override;
    
    void transferPersonBaggage(std::shared_ptr<HumanUnitI> person);

    void addPassenger(std::shared_ptr<HumanUnitI> person);

    void add(std::shared_ptr<UnitSegmentI> segment);

    void showInfo() const override;

private:
    std::vector<std::shared_ptr<UnitSegmentI>> segments;
    
    template <typename EnumType>
    std::shared_ptr<UnitSegmentI> getSegmentByType(EnumType type);

    friend class PlaneTestSuite;
};