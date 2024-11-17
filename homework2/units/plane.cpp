#include "plane.hpp"

bool Plane::invariant() const
{
    for (const auto& segment : segments) {
        if (!segment->invariant())
            return false;
    }

    return true;
}

int Plane::getLuggageWeight() const
{
    int acc = 0;

    for (const auto& segment : segments) {
        acc += segment->getLuggageWeight();
    }

    return acc;
}

int Plane::getBaggageWeight() const
{
    int acc = 0;

    for (const auto& segment : segments) {
        acc += segment->getBaggageWeight();
    }

    return acc;
}

void Plane::transferPersonBaggage(std::shared_ptr<HumanUnitI> person)
{
    EnumVariant economyVariant = PassengerSegmentType::ECONOMY;
    auto economySegment = getSegmentByType(economyVariant);
    economySegment->registerBaggage(person);
}

void Plane::addPassenger(std::shared_ptr<HumanUnitI> person)
{
    auto segment = person->getType();
    auto personSegment = getSegmentByType(person->getType());

    ReturnCodeType codeType = personSegment->add(person);
    if (codeType == ReturnCodeType::NEED_TRANSFER) {
        transferPersonBaggage(person);
    }
}

void Plane::add(std::shared_ptr<UnitSegmentI> segment)
{
    if (segment->invariant()) {
        segments.push_back(segment);
    }
}

void Plane::showInfo() const
{
    std::cout << "INFO: Plane load:"
              << "\n\n";

    int totalBaggageWeight = 0;
    int totalLuggageWeight = 0;
    int allowedWeight = 0;
    for (const auto& segment : segments) {
        segment->showInfo();

        totalBaggageWeight += segment->getBaggageWeight();
        allowedWeight += segment->getAllowedWeight();
        totalLuggageWeight += segment->getLuggageWeight();
    }

    std::cout << "TOTAL:\n\n";
    std::cout << "Total luggage weight: " << totalLuggageWeight << " kg;\n";
    std::cout << "Total baggage weight: " << totalBaggageWeight << " kg;\n";
    std::cout << "Total load: " << totalBaggageWeight + totalLuggageWeight << "/" << allowedWeight << "kg.\n";
}

template<typename EnumType>
std::shared_ptr<UnitSegmentI> Plane::getSegmentByType(EnumType type)
{
    for (const auto& segment : segments) {
        auto segmentType = segment->getType();
        bool match = std::visit([&](auto&& arg) -> bool {
            using T = std::decay_t<decltype(arg)>;

            return std::visit([&](auto&& typeArg) -> bool {
                using U = std::decay_t<decltype(typeArg)>;
                if constexpr (std::is_same_v<T, U>) {
                    return arg == typeArg;
                }
                return false;
            },
                type);
        },
            segmentType);

        if (match) {
            return segment;
        }
    }
    return nullptr;
}