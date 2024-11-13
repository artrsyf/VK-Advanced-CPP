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

    return baggage.size() <= static_cast<size_t>(baggageQuantityBound) &&
        baggageWeight <= baggageWeightBound &&

        luggage.size() <= static_cast<size_t>(luggageQuantityBound) &&
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

    if (baggage.size() >= static_cast<size_t>(quantityBound))
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

    if (luggage.size() >= static_cast<size_t>(quantityBound))
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

FixedVector<BaggagePos> Passenger::getBaggagePositions() const
{
    return baggage;
}

int Passenger::dropBiggestBaggagePosition()
{
    auto removedBaggage = baggage.removeMaxByCriteria([](const BaggagePos& a, const BaggagePos& b) {
        return a.weight < b.weight;
    });

    return removedBaggage.weight;
}

void Passenger::showInfo() const
{
    BaggagePermission baggagePermission = getBaggagePermission(passengerSegment);
    int baggageQuantityBound = baggagePermission.allowedQuantity;
    int baggageWeightBound = baggagePermission.allowedWeight;

    HandLuggagePermission luggagePermission = getHandLuggagePermission(passengerSegment);
    int luggageQuantityBound = luggagePermission.allowedQuantity;
    int luggageWeightBound = luggagePermission.allowedWeight;

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
    
        throw std::invalid_argument("Unknown PassengerSegmentType");
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
    
        throw std::invalid_argument("Unknown PassengerSegmentType");
    }
}

bool PassengerSegment::invariant() const
{
    for (const auto & person : persons)
    {
        if (!person->invariant()) return false;
    }

    return currentBaggageWeight + currentLuggageWeight <= allowedWeight;
}

int PassengerSegment::getBaggageWeight() const
{
    return currentBaggageWeight;
}

int PassengerSegment::getLuggageWeight() const
{
    return currentLuggageWeight;
}

int PassengerSegment::getAllowedWeight() const
{
    return allowedWeight;
}

void PassengerSegment::registerBaggage(std::shared_ptr<HumanUnitI> person)
{
    int baggageWeight = person->getBaggageWeight();
    int weightLeft = allowedWeight - currentBaggageWeight - currentLuggageWeight;
    int toReleaseWeight = baggageWeight - weightLeft;

    while (toReleaseWeight > 0)
    {
        auto maxBaggagePersonIter = std::max_element(persons.begin(), persons.end(), 
        [](const std::shared_ptr<HumanUnitI>& personA, const std::shared_ptr<HumanUnitI>& personB) {
            // Находим максимальный вес среди багажа для каждого пассажира
            int maxWeightA = 0;
            auto personABaggagePositions = personA->getBaggagePositions();
            if (!personABaggagePositions.empty()) {
                maxWeightA = std::max_element(personABaggagePositions.begin(), personABaggagePositions.end(),
                    [](const BaggagePos& a, const BaggagePos& b) {
                        return a.weight < b.weight; // Сравниваем по весу
                    })->weight;
            }

            int maxWeightB = 0;
            auto personBBaggagePositions = personB->getBaggagePositions();
            if (!personBBaggagePositions.empty()) {
                maxWeightB = std::max_element(personBBaggagePositions.begin(), personBBaggagePositions.end(),
                    [](const BaggagePos& a, const BaggagePos& b) {
                        return a.weight < b.weight; // Сравниваем по весу
                    })->weight;
            }
            
            return maxWeightA < maxWeightB; // Сравниваем максимальные веса
        });

        auto personWithMaxBaggage = *maxBaggagePersonIter;
        if (auto personWithBaggageHandler = std::dynamic_pointer_cast<FlexibleBaggageI>(personWithMaxBaggage))
        {
            int realesedWeight = personWithBaggageHandler->dropBiggestBaggagePosition();
            if (auto personIdentifiable = std::dynamic_pointer_cast<IdentifiableI>(personWithMaxBaggage))
            {
                std::string personId = personIdentifiable->getId();
                std::cout << "!!PASSENGER'S BAGGAGE REMOVED FROM FLIGHT, ID = {" << personId << "}!!\n";
            }
            else
            {
                std::cout << "ERROR; Unable to get person id" << '\n';

                return;
            }

            toReleaseWeight -= realesedWeight;
            currentBaggageWeight -= realesedWeight;
        }
        else
        {
            std::cout << "ERROR; Unable to drop person baggage" << '\n';

            return;
        }
    }

    currentBaggageWeight += baggageWeight;
    transfered.push_back(person);
}

ReturnCodeType PassengerSegment::add(std::shared_ptr<HumanUnitI> person)
{
    int weightLeft = allowedWeight - currentBaggageWeight - currentLuggageWeight;

    if (!person->invariant() ||
        persons.size() == static_cast<size_t>(passengersCapacity) ||
        person->getLuggageWeight() > weightLeft
    )
    {
        /* Выкинуть пассажира если
            1. Он не сохранаяет свой инвариант;
            2. Банально нет мест;
            3. Он не может поместить свою ручную кладь.
        */

        if (std::holds_alternative<PassengerSegmentType>(person->getType())) {
            PassengerSegmentType segmentType = std::get<PassengerSegmentType>(person->getType());
            std::string segmentTypeString = mapSegmentToString(segmentType);
            if (auto personIdentifiable = std::dynamic_pointer_cast<IdentifiableI>(person))
            {
                std::string personId = personIdentifiable->getId();
                std::cout << "!!CANT REGISTER " << segmentTypeString << " PASSENGER, ID = " << personId << "!!\n";
            }
            else
            {
                std::cout << "ERROR; Unable to get person id" << '\n';
            }
        }

        return ReturnCodeType::ALLOCATED;
    }
    
    currentLuggageWeight += person->getLuggageWeight();
    weightLeft = allowedWeight - currentBaggageWeight - currentLuggageWeight;

    if (std::holds_alternative<PassengerSegmentType>(person->getType())) {
        PassengerSegmentType segmentType = std::get<PassengerSegmentType>(person->getType());

        if (segmentType == PassengerSegmentType::BUSINESS || 
            segmentType == PassengerSegmentType::FIRST_CLASS) {
            if (person->getBaggageWeight() > weightLeft) {
                persons.push_back(person);

                return ReturnCodeType::NEED_TRANSFER;
            }
        }
    }

    while (person->getBaggageWeight() > weightLeft)
    {
        if (auto personWithBaggageHandler = std::dynamic_pointer_cast<FlexibleBaggageI>(person)) {
            personWithBaggageHandler->dropBiggestBaggagePosition();

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
    
    return ReturnCodeType::ALLOCATED;
}

std::variant<PassengerSegmentType, CrewMemberType> PassengerSegment::getType() const {
    return type;
}

FixedVector<BaggagePos> PassengerSegment::getBaggagePositions() const
{
    return persons[0]->getBaggagePositions();
}

void PassengerSegment::showInfo() const {
    std::cout << "INFO: Segment " << mapSegmentToString(type) << "\n\n";

    std::cout << "Luggage load: " << currentLuggageWeight << " kg;" << '\n';
    std::cout << "Baggage load: " << currentBaggageWeight << " kg;" << "\n\n";
    std::cout << "Total segment load: " << currentLuggageWeight + currentBaggageWeight << "/" << allowedWeight << " kg;" << '\n';

    std::cout << "EACH PERSON INFO:\n\n";

    for (const auto & person : persons) {
        person->showInfo();
    }

    if (!transfered.empty())
    {
        std::cout << "TRANSFERED BAGGAGE INFO:\n\n";
        std::cout << "Transfered " << transfered.size() << " passengers;\n";

        for (const auto & person : transfered)
        {   
            int personRegisteredBaggage = person->getBaggageWeight();
            if (auto personIdentifiable = std::dynamic_pointer_cast<IdentifiableI>(person))
            {
                std::string personId = personIdentifiable->getId();

                std::cout << "Place baggage of person with id: " << personId
                          << " with total weight: " << personRegisteredBaggage << " kg.\n";
            }
            else
            {
                std::cout << "ERROR; Unable to get person id" << '\n';
            }
            
        }
    }
}