#include <iostream>
#include <memory>
#include <cassert>

#include "../../../../main/application/units/crew_member/crew_members.hpp"

class CrewMemberTestSuite {
public:
    static std::shared_ptr<CrewMember> createCrewMember(const std::string& id, CrewMemberType type)
    {
        return std::make_shared<CrewMember>(id, type);
    }

    static void testCrewMember()
    {
        auto crewMember = createCrewMember("ID_1", CrewMemberType::PILOT);

        assert(crewMember->invariant() == true);

        assert(crewMember->getLuggageWeight() == 0);

        assert(crewMember->getBaggageWeight() == 0);

        assert(std::get<CrewMemberType>(crewMember->getType()) == CrewMemberType::PILOT);

        assert(crewMember->getBaggagePositions().empty());

        crewMember->showInfo();
    }

    static void testCrewSegment()
    {
        int allowedWeight = 100;
        CrewSegment crewSegment(allowedWeight, CrewMemberType::PILOT);

        assert(crewSegment.invariant() == true);

        assert(crewSegment.getAllowedWeight() == allowedWeight);

        assert(crewSegment.getBaggageWeight() == 0);
        assert(crewSegment.getLuggageWeight() == 0);

        auto crewMember = createCrewMember("ID_2", CrewMemberType::PILOT);
        ReturnCodeType returnCode = crewSegment.add(crewMember);

        assert(returnCode == ReturnCodeType::ALLOCATED);

        assert(crewSegment.getBaggageWeight() == 0);
        assert(crewSegment.getLuggageWeight() == 0);

        assert(crewSegment.getBaggagePositions().empty());

        assert(crewSegment.invariant() == true);

        auto crewMemberRegister = createCrewMember("ID_5", CrewMemberType::FLIGHT_ATTENDANT);
        crewSegment.registerBaggage(crewMemberRegister);

        crewSegment.showInfo();
    }

    static void runTests()
    {
        testCrewMember();
        testCrewSegment();

        std::cout << "\nSUCCESS: Crew Member tests passed successfully.\n\n";
    }
};