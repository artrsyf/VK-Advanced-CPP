#include "crew_members.hpp"

bool CrewMember::invariant() const
{
    return getLuggageWeight() == 0 && getBaggageWeight() == 0;
}

int CrewMember::getLuggageWeight() const
{
    return 0;
}

int CrewMember::getBaggageWeight() const
{
    return 0;
}

std::variant<PassengerSegmentType, CrewMemberType> CrewMember::getType() const
{
    return type;
}

FixedVector<BaggagePos> CrewMember::getBaggagePositions() const
{
    return FixedVector<BaggagePos>();
}

void CrewMember::showInfo() const
{
    std::cout << "Crew member: " << id << ", The " << mapCrewToString(type) << std::endl;

    std::cout << "Allowed baggage: 0" << std::endl;
    std::cout << "Allowed luggage: 0" << std::endl;

    std::cout << "Baggage weight: " << getBaggageWeight() << std::endl;
    std::cout << "Luggage weight: " << getLuggageWeight() << std::endl;
}

bool CrewSegment::invariant() const
{
    for (const auto& person : persons) {
        if (!person->invariant())
            return false;
    }

    return currentBaggageWeight <= allowedWeight;
}

int CrewSegment::getBaggageWeight() const
{
    return currentBaggageWeight;
}

int CrewSegment::getLuggageWeight() const
{
    return currentLuggageWeight;
}

int CrewSegment::getAllowedWeight() const
{
    return allowedWeight;
}

std::variant<PassengerSegmentType, CrewMemberType> CrewSegment::getType() const
{
    return type;
}

ReturnCodeType CrewSegment::add(std::shared_ptr<HumanUnitI> person)
{
    if (person->invariant()) {
        persons.push_back(person);

        currentBaggageWeight += person->getBaggageWeight();
        currentLuggageWeight += person->getLuggageWeight();
    }

    return ReturnCodeType::ALLOCATED;
}

FixedVector<BaggagePos> CrewSegment::getBaggagePositions() const
{
    return persons[0]->getBaggagePositions();
}

void CrewSegment::showInfo() const
{
    std::cout << "INFO: Segment " << mapCrewToString(type) << "\n\n";

    std::cout << "Luggage load: " << currentLuggageWeight << " kg;" << '\n';
    std::cout << "Baggage bound load: " << allowedWeight << " kg;" << '\n';
    std::cout << "Baggage load: " << currentBaggageWeight << " kg;"
              << "\n\n";

    std::cout << "EACH PERSON INFO:\n\n";

    for (const auto& person : persons) {
        person->showInfo();
    }
}