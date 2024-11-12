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

    template <typename Criteria>
    void removeMaxByCriteria(Criteria criterion) {
        if (data.empty()) {
            std::cout << "Can't remove element, struct is empty." << '\n';
        }

        // Найдем итератор на элемент с максимальным значением критерия
        auto maxIt = std::max_element(data.begin(), data.end(),
                                      [&](const T& a, const T& b) {
                                          return criterion(a) < criterion(b);
                                      });

        // Удаляем найденный элемент
        data.erase(maxIt);
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

    void dropSmallestBaggagePosition() override;
    
    void showInfo() const override;

private:
    std::string id;
    PassengerSegmentType passengerSegment;

    FixedVector<LuggagePos> luggage;
    FixedVector<BaggagePos> baggage;

    static HandLuggagePermission getHandLuggagePermission(PassengerSegmentType bookedPassengerSegmentType);

    static BaggagePermission getBaggagePermission(PassengerSegmentType bookedPassengerSegment);
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

    bool invariant() const override;

    int getBaggageWeight() const override;

    int getLuggageWeight() const override;

    int getAllowedBaggageWeight() const override;

    void add(std::shared_ptr<HumanUnitI> person) override;

    void remove(std::shared_ptr<HumanUnitI> person) override;

    std::variant<PassengerSegmentType, CrewMemberType> getType() const override;

    void showInfo() const override;

private:
    PassengerSegmentType type;
    int allowedWeight;
    int currentBaggageWeight;
    int currentLuggageWeight;
    std::vector<std::shared_ptr<HumanUnitI>> persons;
};