#include "passengers.hpp"

bool Passenger::invariant() const
{
    BaggagePermission baggagePermission = getBaggagePermission(passengerSegment);
    int baggageQuantityBound = baggagePermission.allowedQuantity;
    int baggageWeightBound = baggagePermission.allowedWeight;
    int baggageWeight = getBaggageWeight();

    HandLuggagePermission luggagePermission = getHandLuggagePermission(passengerSegment);
    int luggageQuantityBound = luggagePermission.allowedQuantity;
    int luggageWeightBound = luggagePermission.allowedWeight;
    int luggageWeight = getLuggageWeight();

    return baggage.size() <= baggageQuantityBound &&
        baggageWeight <= baggageWeightBound &&

        luggage.size() <= luggageQuantityBound &&
        luggageWeight <= luggageWeightBound;
}

int Passenger::getBaggageWeight() const
{
    int acc = 0;

    for (const auto & baggageItem : baggage)
    {
        acc += baggageItem.weight;
    }

    return acc;
}

int Passenger::getLuggageWeight() const
{
    int acc = 0;

    for (const auto & luggageItem : luggage)
    {
        acc += luggageItem.weight;
    }

    return acc;
}

std::variant<PassengerSegmentType, CrewMemberType> Passenger::getType() const
{
    return passengerSegment;
}

void Passenger::addBaggageItem(int weight)
{
    BaggagePermission permission = getBaggagePermission(passengerSegment);
    int quantityBound = permission.allowedQuantity;
    int weightBound = permission.allowedWeight;

    if (baggage.size() >= quantityBound)
    {
        std::cout << "Error: Cannot add more baggage items. Maximum allowed: " 
                    << quantityBound << std::endl; // Verbose

        std::cout << "!!PASSENGER'S BAGGAGE REMOVED FROM FLIGHT, ID = {" << id << "}!!" << '\n';

        return;
    }

    int weightLeft = weightBound - getBaggageWeight();

    if (weight > weightLeft) {
        std::cout << "Error: Can't add baggage position."
                    << "Item weight exceeds the limit of " 
                    << weightBound << " kg." << std::endl; // Verbose

        std::cout << "!!PASSENGER'S BAGGAGE REMOVED FROM FLIGHT, ID = {" << id << "}!!" << '\n';

        return;
    }

    baggage.add(weight);
}

void Passenger::addLuggageItem(int weight)
{
    HandLuggagePermission permission = getHandLuggagePermission(passengerSegment);
    int quantityBound = permission.allowedQuantity;
    int weightBound = permission.allowedWeight;

    if (luggage.size() >= quantityBound)
    {
        std::cout << "Error: Cannot add more luggage items. Maximum allowed: " 
                    << quantityBound << std::endl; // Verbose

        std::cout << "!!PASSENGER'S LUGGAGE REMOVED FROM FLIGHT, ID = {" << id << "}!!" << '\n';

        return;
    }

    int weightLeft = weightBound - getLuggageWeight();

    if (weight > weightLeft) {
        std::cout << "Error: Can't add luggage position." 
                    << "Item weight exceeds the limit of " 
                    << weightBound << " kg." << std::endl; // Verbose

        std::cout << "!!PASSENGER'S LUGGAGE REMOVED FROM FLIGHT, ID = {" << id << "}!!" << '\n';

        return;
    }

    luggage.add(weight);
}

std::string Passenger::getId() const
{
    return id;
}

void Passenger::dropSmallestBaggagePosition()
{
    baggage.removeMaxByCriteria([](const BaggagePos & pos) { return pos.weight; });
}

void Passenger::showInfo() const
{
    BaggagePermission baggagePermission = getBaggagePermission(passengerSegment);
    int baggageQuantityBound = baggagePermission.allowedQuantity;
    int baggageWeightBound = baggagePermission.allowedWeight;
    int baggageWeight = getBaggageWeight();

    HandLuggagePermission luggagePermission = getHandLuggagePermission(passengerSegment);
    int luggageQuantityBound = luggagePermission.allowedQuantity;
    int luggageWeightBound = luggagePermission.allowedWeight;
    int luggageWeight = getLuggageWeight();

    std::cout << "Passenger: " << id << std::endl;
    std::cout << "Segment: " << mapSegmentToString(passengerSegment) << std::endl;

    std::cout << "Allowed baggage: " << baggageQuantityBound
                << " items, " << baggageWeightBound << " kg" << std::endl;
    std::cout << "Allowed luggage: " << luggageQuantityBound
                << " items, " << luggageWeightBound << " kg" << std::endl;

    std::cout << "Actual baggage: " << baggage.size() << " items" << std::endl;
    for (size_t i = 0; i < baggage.size(); ++i) {
        std::cout << " - Item " << (i + 1) << ": " << baggage[i].weight << " kg" << std::endl;
    }
    std::cout << "Baggage weight: " << getBaggageWeight() << std::endl;

    std::cout << "Actual luggage: " << luggage.size() << " items" << std::endl;
    for (size_t i = 0; i < luggage.size(); ++i) {
        std::cout << " - Item " << (i + 1) << ": " << luggage[i].weight << " kg" << std::endl;
    }
    std::cout << "Luggage weight: " << getLuggageWeight() << std::endl;
}

HandLuggagePermission Passenger::getHandLuggagePermission(PassengerSegmentType bookedPassengerSegmentType)
{
    switch (bookedPassengerSegmentType)
    {
    case PassengerSegmentType::ECONOMY:
        return HandLuggagePermission(1, 10); 

    case PassengerSegmentType::BUSINESS:
        return HandLuggagePermission(2, 24); 

    case PassengerSegmentType::FIRST_CLASS:
        return HandLuggagePermission(2, 60); 
    
    default:
        /* Error handling */
    
        break;
    }
}

BaggagePermission Passenger::getBaggagePermission(PassengerSegmentType bookedPassengerSegment)
{
    switch (bookedPassengerSegment)
    {
    case PassengerSegmentType::ECONOMY:
        return BaggagePermission(1, 24);

    case PassengerSegmentType::BUSINESS:
        return BaggagePermission(2, 40);

    case PassengerSegmentType::FIRST_CLASS:
        return BaggagePermission(2, INFINITY);
    
    default:
        /* Error handling */
    
        break;
    }
}

bool PassengerSegment::invariant() const
{
    for (const auto & person : persons)
    {
        if (!person->invariant()) return false;
    }

    return currentBaggageWeight <= allowedWeight;
}

int PassengerSegment::getBaggageWeight() const
{
    return currentBaggageWeight;
}

int PassengerSegment::getLuggageWeight() const
{
    return currentLuggageWeight;
}

int PassengerSegment::getAllowedBaggageWeight() const
{
    return allowedWeight;
}

void PassengerSegment::add(std::shared_ptr<HumanUnitI> person)
{
    if (!person->invariant())
    {
        std::cout << "ERROR: Can't add new passanger bc of limits" << '\n';
        return;
    }

    int baggageWeightLeft = allowedWeight - currentBaggageWeight;
    while (person->getBaggageWeight() > baggageWeightLeft)
    {
        if (auto personWithBaggageHandler = std::dynamic_pointer_cast<FlexibleBaggageI>(person)) {
            personWithBaggageHandler->dropSmallestBaggagePosition();

            if (auto personIdentifiable = std::dynamic_pointer_cast<IdentifiableI>(person))
            {
                std::string personId = personIdentifiable->getId();
                std::cout << "!!PASSENGER'S BAGGAGE REMOVED FROM FLIGHT, ID = {" << personId << "}!!" << '\n';
            }
            else
            {
                std::cout << "ERROR; Unable to get person id" << '\n';
            }
        }
        else
        {
            std::cout << "ERROR; Unable to drop person baggage" << '\n';
        }
    }

    persons.push_back(person);

    currentBaggageWeight += person->getBaggageWeight();
    currentLuggageWeight += person->getLuggageWeight();
}

void PassengerSegment::remove(std::shared_ptr<HumanUnitI> person) {
    persons.erase(std::remove(persons.begin(), persons.end(), person), persons.end());
}

std::variant<PassengerSegmentType, CrewMemberType> PassengerSegment::getType() const {
    return type;
}

void PassengerSegment::showInfo() const {
    std::cout << "INFO: Segment " << mapSegmentToString(type) << "\n\n";

    std::cout << "Luggage load: " << currentLuggageWeight << " kg;" << '\n';
    std::cout << "Baggage bound load: " << allowedWeight << " kg;" << '\n';
    std::cout << "Baggage load: " << currentBaggageWeight << " kg;" << "\n\n";

    std::cout << "EACH PERSON INFO:\n\n";

    for (const auto & person : persons) {
        person->showInfo();
    }
}