#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <variant>

#include "unit.hpp"

const int CREW_MEMBER_COUNT = 8;

class CrewMember : public HumanUnitI
{
public:
    CrewMember(std::string _id, CrewMemberType _type) : id(_id), type(_type) {}

    bool invariant() const override
    {
        return getLuggageWeight() == 0 &&
            getBaggageWeight() == 0;
    }

    int getLuggageWeight() const override
    {
        return 0;
    }

    int getBaggageWeight() const override
    {
        return 0;
    }

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override
    {
        return type;
    }

    void showInfo() const override
    {
        std::cout << "Crew member: " << id << ", The " << mapCrewToString(type) << std::endl;

        std::cout << "Allowed baggage: 0" << std::endl;
        std::cout << "Allowed luggage: 0" << std::endl;

        std::cout << "Baggage weight: " << getBaggageWeight() << std::endl;
        std::cout << "Luggage weight: " << getLuggageWeight() << std::endl;
    }

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

    bool invariant() const override
    {
        for (const auto & person : persons)
        {
            if (!person->invariant()) return false;
        }

        return currentBaggageWeight <= allowedWeight;
    }

    int getBaggageWeight() const override
    {
        return currentBaggageWeight;
    }

    int getLuggageWeight() const override
    {
        return currentLuggageWeight;
    }

    int getAllowedBaggageWeight() const override
    {
        return allowedWeight;
    }

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override
    {
        return type;
    }

    void add(std::shared_ptr<HumanUnitI> person) override
    {
        if (person->invariant())
        {
            persons.push_back(person);

            currentBaggageWeight += person->getBaggageWeight();
            currentLuggageWeight += person->getLuggageWeight();
        } 
        else
        {
            std::cout << "Can't add new passanger" << '\n';
        }
    }

    void remove(std::shared_ptr<HumanUnitI> person) override {
        persons.erase(std::remove(persons.begin(), persons.end(), person), persons.end());
    }

    void showInfo() const override {
        std::cout << "INFO: Segment " << mapCrewToString(type) << "\n\n";

        std::cout << "Luggage load: " << currentLuggageWeight << " kg;" << '\n';
        std::cout << "Baggage bound load: " << allowedWeight << " kg;" << '\n';
        std::cout << "Baggage load: " << currentBaggageWeight << " kg;" << "\n\n";

        std::cout << "EACH PERSON INFO:\n\n";

        for (const auto & person : persons) {
            person->showInfo();
        }
    }

private:
    CrewMemberType type;
    int allowedWeight;
    int currentBaggageWeight;
    int currentLuggageWeight;
    std::vector<std::shared_ptr<HumanUnitI>> persons;
};