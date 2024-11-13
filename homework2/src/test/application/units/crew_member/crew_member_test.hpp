#include <iostream>
#include <memory>
#include <cassert>

#include "../../../../main/application/units/crew_member/crew_members.hpp"

class CrewMemberTestSuite
{
public:
    // Вспомогательная функция для создания объекта `CrewMember`
    static std::shared_ptr<CrewMember> createCrewMember(const std::string& id, CrewMemberType type) {
        return std::make_shared<CrewMember>(id, type);
    }

    // Тесты для класса CrewMember
    static void testCrewMember() {
        auto crewMember = createCrewMember("ID_1", CrewMemberType::PILOT);

        // Test invariant (ожидаем, что багаж и ручная кладь пусты для экипажа)
        assert(crewMember->invariant() == true);

        // Test getLuggageWeight (должен вернуть 0)
        assert(crewMember->getLuggageWeight() == 0);

        // Test getBaggageWeight (должен вернуть 0)
        assert(crewMember->getBaggageWeight() == 0);

        // Test getType (должен вернуть тип CrewMemberType::PILOT)
        assert(std::get<CrewMemberType>(crewMember->getType()) == CrewMemberType::PILOT);

        // Test getBaggagePositions (должен вернуть пустой вектор FixedVector<BaggagePos>)
        assert(crewMember->getBaggagePositions().empty());

        // Проверка showInfo (вывод информации о члене экипажа)
        crewMember->showInfo();
    }

    // Тесты для класса CrewSegment
    static void testCrewSegment() {
        int allowedWeight = 100; // Допустимый вес для сегмента экипажа
        CrewSegment crewSegment(allowedWeight, CrewMemberType::PILOT);

        // Проверка invariant (ожидаем, что текущий вес багажа <= разрешенного)
        assert(crewSegment.invariant() == true);

        // Проверка getAllowedWeight (должен вернуть 100)
        assert(crewSegment.getAllowedWeight() == allowedWeight);

        // Проверка getBaggageWeight и getLuggageWeight (должны быть 0, так как экипаж без багажа)
        assert(crewSegment.getBaggageWeight() == 0);
        assert(crewSegment.getLuggageWeight() == 0);

        // Добавление члена экипажа в сегмент
        auto crewMember = createCrewMember("ID_2", CrewMemberType::PILOT);
        ReturnCodeType returnCode = crewSegment.add(crewMember);

        // Проверка ReturnCodeType после добавления
        assert(returnCode == ReturnCodeType::ALLOCATED);

        // Проверка getBaggageWeight и getLuggageWeight после добавления члена экипажа
        assert(crewSegment.getBaggageWeight() == 0);
        assert(crewSegment.getLuggageWeight() == 0);

        // Проверка getBaggagePositions (должен вернуть пустой FixedVector<BaggagePos>)
        assert(crewSegment.getBaggagePositions().empty());

        // Проверка invariant (должен оставаться true, так как вес багажа <= допустимого)
        assert(crewSegment.invariant() == true);

        // Проверка showInfo (вывод информации о сегменте экипажа)
        crewSegment.showInfo();
    }

    static void runTests()
    {
        testCrewMember();
        testCrewSegment();

        std::cout << "\nSUCCESS: Crew Member tests passed successfully.\n\n";
    }
};