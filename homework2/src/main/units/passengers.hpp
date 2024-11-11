#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <iterator>

#include "unit.hpp"

const int INFINITY = std::numeric_limits<int>::max();

const int SEGEMNT_COUNT = 3;

template <typename T>
class FixedVector {
public:
    // Конструктор по умолчанию
    FixedVector() = default;

    // Конструктор с указанием размера
    explicit FixedVector(size_t size) : data(size), maxSize(size) {}

    // Метод для инициализации после создания объекта
    void initialize(size_t size) {
        if (!data.empty()) throw std::runtime_error("Already initialized");
        maxSize = size;
    }

    // Метод для добавления элемента с проверкой на переполнение
    void add(const T& item) {
        if (data.size() >= maxSize) {
            throw std::overflow_error("FixedVector overflow: Maximum size reached");
        }
        data.push_back(item);
    }

    // Доступ к элементам
    T& operator[](size_t index) {
        return data.at(index);
    }

    const T& operator[](size_t index) const {
        return data.at(index);
    }

    // Текущий размер
    size_t size() const {
        return data.size();
    }

    // Максимальный размер
    size_t capacity() const {
        return maxSize;
    }

    // Методы изменения размера запрещены
    void push_back(const T&) = delete;
    void emplace_back(const T&) = delete;
    void resize(size_t) = delete;

    auto begin() { return data.begin(); }
    auto end() { return data.end(); }
    auto begin() const { return data.begin(); }
    auto end() const { return data.end(); }

private:
    std::vector<T> data;
    size_t maxSize = 0; // Максимальный размер
};

struct BaggagePos
{
    int weight;

    BaggagePos() : weight(0) {}
    BaggagePos(int w) : weight(w) {}
};

struct LuggagePos
{
    int weight;

    LuggagePos() : weight(0) {}
    LuggagePos(int w) : weight(w) {}
};

struct HandLuggagePermission
{
    int allowedQuantity;
    int allowedWeight;

    HandLuggagePermission(int _allowedQuantity, int _allowedWeight) : allowedQuantity(_allowedQuantity), allowedWeight(_allowedWeight) {}
};

struct BaggagePermission
{
    int allowedQuantity;
    int allowedWeight;

    BaggagePermission(int _allowedQuantity, int _allowedWeight) : allowedQuantity(_allowedQuantity), allowedWeight(_allowedWeight) {}
};

class Passenger : public HumanUnitI 
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

    bool invariant() const override
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

    int getBaggageWeight() const override
    {
        int acc = 0;

        for (const auto & baggageItem : baggage)
        {
            acc += baggageItem.weight;
        }

        return acc;
    }

    int getLuggageWeight() const override
    {
        int acc = 0;

        for (const auto & luggageItem : luggage)
        {
            acc += luggageItem.weight;
        }

        return acc;
    }

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override
    {
        return passengerSegment;
    }

    void addBaggageItem(int weight)
    {
        BaggagePermission permission = getBaggagePermission(passengerSegment);
        int quantityBound = permission.allowedQuantity;
        int weightBound = permission.allowedWeight;

        if (baggage.size() >= quantityBound)
        {
            std::cout << "Error: Cannot add more baggage items. Maximum allowed: " 
                      << quantityBound << std::endl;

            return;
        }

        if (weight > weightBound) {
            std::cout << "Error: Item weight exceeds the limit of " 
                      << weightBound << " kg per item." << std::endl;

            return;
        }

        baggage.add(weight);
    }

    void addLuggageItem(int weight)
    {
        HandLuggagePermission permission = getHandLuggagePermission(passengerSegment);
        int quantityBound = permission.allowedQuantity;
        int weightBound = permission.allowedWeight;

        if (luggage.size() >= quantityBound)
        {
            std::cout << "Error: Cannot add more luggage items. Maximum allowed: " 
                      << quantityBound << std::endl;

            return;
        }

        if (weight > weightBound) {
            std::cout << "Error: Item weight exceeds the limit of " 
                      << weightBound << " kg per item." << std::endl;

            return;
        }

        luggage.add(weight);
    }
    
    void showInfo() const override
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
                  << " items, " << baggageWeightBound << " kg per item" << std::endl;
        std::cout << "Allowed luggage: " << luggageQuantityBound
                  << " items, " << luggageWeightBound << " kg per item" << std::endl;

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
private:
    std::string id;
    PassengerSegmentType passengerSegment;

    FixedVector<LuggagePos> luggage;
    FixedVector<BaggagePos> baggage;

    static HandLuggagePermission getHandLuggagePermission(PassengerSegmentType bookedPassengerSegmentType)
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

    static BaggagePermission getBaggagePermission(PassengerSegmentType bookedPassengerSegment)
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
};

struct BaggageSegmentSpacePermission
{
    int allowedWeight;

    BaggageSegmentSpacePermission(int _allowedWeight) : allowedWeight(_allowedWeight) {}
};

class PassengerSegment : public UnitSegmentI 
{
public:
    PassengerSegment(int _allowedWeight, PassengerSegmentType _type) :
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

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override {
        return type;
    }

    void showInfo() const override {
        std::cout << "INFO: Segment " << mapSegmentToString(type) << "\n\n";

        std::cout << "Luggage load: " << currentLuggageWeight << " kg;" << '\n';
        std::cout << "Baggage bound load: " << allowedWeight << " kg;" << '\n';
        std::cout << "Baggage load: " << currentBaggageWeight << " kg;" << "\n\n";

        std::cout << "EACH PERSON INFO:\n\n";

        for (const auto & person : persons) {
            person->showInfo();
        }
    }

private:
    PassengerSegmentType type;
    int allowedWeight;
    int currentBaggageWeight;
    int currentLuggageWeight;
    std::vector<std::shared_ptr<HumanUnitI>> persons;
};