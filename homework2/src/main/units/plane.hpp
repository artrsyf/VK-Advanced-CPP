#include <variant>

#include "passengers.hpp"
#include "crew_members.hpp"

using EnumVariant = std::variant<PassengerSegmentType, CrewMemberType>;

class Plane : public UnitI
{
public:
    bool invariant() const override
    {
        for (const auto & segment : segments)
        {
            if (!segment->invariant()) return false;
        }

        return true;
    }

    int getLuggageWeight() const override
    {
        int acc = 0;

        for (const auto & segment : segments)
        {
            acc += segment->getLuggageWeight();
        }

        return acc;
    }

    int getBaggageWeight() const override
    {
        int acc = 0;

        for (const auto & segment : segments)
        {
            acc += segment->getBaggageWeight();
        }

        return acc;
    }

    void addPassenger(std::shared_ptr<HumanUnitI> person)
    {
        auto segment = person->getType();
        auto personSegment = getSegmentByType(person->getType());

        personSegment->add(person);
    }

    void add(std::shared_ptr<UnitSegmentI> segment) {
        if (segment->invariant())
        {
            segments.push_back(segment);
        } 
        else
        {
            std::cout << "Can't add new segment" << '\n';
        }
    }

    void remove(std::shared_ptr<UnitSegmentI> segment) {
        segments.erase(std::remove(segments.begin(), segments.end(), segment), segments.end());
    }

    void showInfo() const override {
        std::cout << "INFO: Plane load:" << "\n\n";

        int totalBaggageWeight = 0;
        int totalLuggageWeight = 0;
        int allowedBaggageWeight = 0;
        for (const auto & segment : segments) {
            segment->showInfo();

            totalBaggageWeight += segment->getBaggageWeight();
            allowedBaggageWeight += segment->getAllowedBaggageWeight();
            totalLuggageWeight += segment->getLuggageWeight();
        }

        std::cout << "TOTAL:\n\n";
        std::cout << "Total luggage weight: " << totalLuggageWeight << " kg;\n";
        std::cout << "Total baggage load: " << totalBaggageWeight << "/" << allowedBaggageWeight << "kg.";
    }

private:
    std::vector<std::shared_ptr<UnitSegmentI>> segments;

    template <typename EnumType>
std::shared_ptr<UnitSegmentI> getSegmentByType(EnumType type)
{
    for (const auto& segment : segments)
    {
        auto segmentType = segment->getType(); // Это std::variant<PassengerSegmentType, CrewMemberType>

        // Используем std::visit для обработки обоих std::variant
        bool match = std::visit([&](auto&& arg) -> bool {
            using T = std::decay_t<decltype(arg)>; // Определяем тип, который содержится в segmentType (std::variant)

            // Проверяем, совпадает ли тип из segmentType с типом из type
            return std::visit([&](auto&& typeArg) -> bool {
                using U = std::decay_t<decltype(typeArg)>; // Определяем тип, который содержится в type (std::variant)
                // Проверяем совпадение типов и значений
                if constexpr (std::is_same_v<T, U>) {
                    return arg == typeArg; // Сравниваем значения
                }
                return false;
            }, type); // Это распаковка type (второй variant)

        }, segmentType); // Это распаковка segmentType (первый variant)

        if (match) {
            return segment;
        }
    }
    return nullptr;
}
};