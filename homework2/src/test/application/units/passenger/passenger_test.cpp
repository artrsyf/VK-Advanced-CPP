#include <iostream>
#include <cassert>
#include "../../../../main/application/units/passenger/passengers.hpp"

// Функция для тестирования Passenger::invariant
void testPassengerInvariant() {
    Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);
    
    // Тестируем с багажом, который не превышает лимитов
    passenger.addBaggageItem(10);
    passenger.addLuggageItem(5);
    assert(passenger.invariant() == true);
}

// Функция для тестирования Passenger::getBaggageWeight и getLuggageWeight
void testPassengerWeightCalculations() {
    Passenger passenger("unique_id", PassengerSegmentType::BUSINESS);

    passenger.addBaggageItem(10);
    passenger.addBaggageItem(15);
    assert(passenger.getBaggageWeight() == 25);

    passenger.addLuggageItem(5);
    assert(passenger.getLuggageWeight() == 5);
}

// Функция для тестирования Passenger::addBaggageItem с проверкой на переполнение
void testPassengerAddBaggageItem() {
    Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);
    passenger.addBaggageItem(25); // Превышение веса багажа для ECONOMY
    assert(passenger.getBaggageWeight() == 0); // Багаж не добавлен

    passenger.addBaggageItem(10); // Успешно добавлен
    assert(passenger.getBaggageWeight() == 10);
}

// Функция для тестирования Passenger::addLuggageItem с проверкой на переполнение
void testPassengerAddLuggageItem() {
    Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);
    passenger.addLuggageItem(15); // Превышение веса ручной клади для ECONOMY
    assert(passenger.getLuggageWeight() == 0); // Ручная кладь не добавлена

    passenger.addLuggageItem(5); // Успешно добавлено
    assert(passenger.getLuggageWeight() == 5);
}

// Функция для тестирования PassengerSegment::invariant
void testPassengerSegmentInvariant() {
    PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
    PassengerSegment segment(200, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum)); // лимит в 200 кг
    std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);
    std::shared_ptr<Passenger> passenger2 = std::make_shared<Passenger>("passenger2", PassengerSegmentType::ECONOMY);

    passenger1->addBaggageItem(20);
    passenger2->addBaggageItem(15);

    segment.add(passenger1);
    segment.add(passenger2);

    assert(segment.invariant() == true); // В пределах допустимого
}

// Функция для тестирования PassengerSegment::add и реакции на переполнение
void testPassengerSegmentAdd() {
    PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
    PassengerSegment segment(50, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum)); // лимит в 50 кг
    std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);
    std::shared_ptr<Passenger> passenger2 = std::make_shared<Passenger>("passenger2", PassengerSegmentType::ECONOMY);

    passenger1->addBaggageItem(20);
    passenger2->addBaggageItem(35);

    assert(segment.add(passenger1) == ReturnCodeType::ALLOCATED);
    assert(segment.add(passenger2) == ReturnCodeType::ALLOCATED); // Пассажир не добавлен, требуется трансфер
}

// Функция для тестирования Passenger::dropBiggestBaggagePosition
void testDropBiggestBaggagePosition() {
    Passenger passenger("unique_id", PassengerSegmentType::FIRST_CLASS);
    passenger.addBaggageItem(12);
    passenger.addBaggageItem(32);

    int weightRemoved = passenger.dropBiggestBaggagePosition();
    assert(weightRemoved == 32);
    assert(passenger.getBaggageWeight() == 12); 
}

// Функция для тестирования PassengerSegment::registerBaggage
void testRegisterBaggage() {
    PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
    PassengerSegment segment(100, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum)); // лимит в 100 кг
    std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);

    passenger1->addBaggageItem(24);
    segment.registerBaggage(passenger1); // Регистрируем багаж пассажира
    assert(segment.getBaggageWeight() == 24);
}

// Основная функция, запускающая все тесты
void runTests() {
    testPassengerInvariant();
    testPassengerWeightCalculations();
    testPassengerAddBaggageItem();
    testPassengerAddLuggageItem();
    testPassengerSegmentInvariant();
    testPassengerSegmentAdd();
    testDropBiggestBaggagePosition();
    testRegisterBaggage();
    
    std::cout << "All tests passed successfully.\n";
}

int main() {
    runTests();
    return 0;
}
