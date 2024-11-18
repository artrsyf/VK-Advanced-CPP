#include <cassert>
#include <iostream>
#include <memory>

#include "../../../../main/application/units/passenger/passengers.hpp"

class PassengerTestSuite {
public:
    static void testPassengerInvariant()
    {
        Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);

        passenger.addBaggageItem(10);
        passenger.addLuggageItem(5);
        assert(passenger.invariant() == true);
    }

    static void testPassengerBaggageBound()
    {
        Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);

        passenger.addBaggageItem(10);
        passenger.addBaggageItem(5);
        assert(passenger.getBaggageWeight() == 10 && passenger.getBaggagePositions().size() == 1);
    }

    static void testPassengerLuggageBound()
    {
        Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);

        passenger.addLuggageItem(4);
        passenger.addLuggageItem(5);
        assert(passenger.getLuggageWeight() == 4);
    }

    static void testPassengerIdGetter()
    {
        Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);
        auto passengerPtr = std::make_shared<Passenger>(passenger);
        auto personIdentifiable = std::dynamic_pointer_cast<IdentifiableI>(passengerPtr);
        assert(personIdentifiable->getId() == "unique_id");
    }

    static void testPassengerShowInfo()
    {
        Passenger passenger("some_id", PassengerSegmentType::ECONOMY);
        passenger.addBaggageItem(3);
        passenger.addLuggageItem(2);
        passenger.showInfo();
        assert(true);
    }

    static void testPassengerLuggageWeightGetter()
    {
        Passenger passenger("some_id", PassengerSegmentType::ECONOMY);
        passenger.addLuggageItem(4);
        assert(passenger.getLuggageWeight() == 4);
    }

    static void testPassengerWeightCalculations()
    {
        Passenger passenger("unique_id", PassengerSegmentType::BUSINESS);

        passenger.addBaggageItem(10);
        passenger.addBaggageItem(15);
        assert(passenger.getBaggageWeight() == 25);

        passenger.addLuggageItem(5);
        assert(passenger.getLuggageWeight() == 5);
    }

    static void testPassengerAddBaggageItem()
    {
        Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);
        passenger.addBaggageItem(25);
        assert(passenger.getBaggageWeight() == 0);

        passenger.addBaggageItem(10);
        assert(passenger.getBaggageWeight() == 10);
    }

    static void testPassengerAddLuggageItem()
    {
        Passenger passenger("unique_id", PassengerSegmentType::ECONOMY);
        passenger.addLuggageItem(15);
        assert(passenger.getLuggageWeight() == 0);

        passenger.addLuggageItem(5);
        assert(passenger.getLuggageWeight() == 5);
    }

    static void testPassengerSegmentInvariant()
    {
        PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegment segment(200, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum));
        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);
        std::shared_ptr<Passenger> passenger2 = std::make_shared<Passenger>("passenger2", PassengerSegmentType::ECONOMY);

        passenger1->addBaggageItem(20);
        passenger2->addBaggageItem(15);

        segment.add(passenger1);
        segment.add(passenger2);

        assert(segment.invariant() == true);
    }

    static void testPassengerSegmentAdd()
    {
        PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegment segment(50, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum));
        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);
        std::shared_ptr<Passenger> passenger2 = std::make_shared<Passenger>("passenger2", PassengerSegmentType::ECONOMY);

        passenger1->addBaggageItem(20);
        passenger2->addBaggageItem(35);

        assert(segment.add(passenger1) == ReturnCodeType::ALLOCATED);
        assert(segment.add(passenger2) == ReturnCodeType::ALLOCATED);
    }

    static void testSegmentInabilityToAdd()
    {
        PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegment segment(3, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum));
        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);

        passenger1->addLuggageItem(4);

        ReturnCodeType returnCode = segment.add(passenger1);
        assert(returnCode == ReturnCodeType::ALLOCATED);
        assert(segment.getBaggageWeight() == 0 && segment.getLuggageWeight() == 0);
    }

    static void testSegmentBaggageDrop()
    {
        PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegment segment(3, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum));
        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);

        passenger1->addLuggageItem(2);
        passenger1->addBaggageItem(8);

        ReturnCodeType returnCode = segment.add(passenger1);
        assert(returnCode == ReturnCodeType::ALLOCATED);
        assert(segment.getBaggageWeight() == 0 && segment.getLuggageWeight() == 2);
    }

    static void testPassengerSegmentAllowedWeightGetter()
    {
        PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegment segment(50, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum));
        assert(segment.getAllowedWeight() == 50);
    }

    static void testDropBiggestBaggagePosition()
    {
        Passenger passenger("unique_id", PassengerSegmentType::FIRST_CLASS);
        passenger.addBaggageItem(12);
        passenger.addBaggageItem(32);

        int weightRemoved = passenger.dropBiggestBaggagePosition();
        assert(weightRemoved == 32);
        assert(passenger.getBaggageWeight() == 12);
    }

    static void testRegisterBaggage()
    {
        PassengerSegmentType segmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegment segment(100, segmentTypeEnum, segmentCapacityBind.at(segmentTypeEnum));
        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);

        passenger1->addBaggageItem(24);
        segment.registerBaggage(passenger1);
        assert(segment.getBaggageWeight() == 24);
    }

    static void testEconomyBaggageWipeDueTransfer()
    {
        PassengerSegmentType economySegmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegmentType businessSegmentTypeEnum = PassengerSegmentType::BUSINESS;
        PassengerSegment economySegment(20, economySegmentTypeEnum, segmentCapacityBind.at(economySegmentTypeEnum));
        PassengerSegment businessSegment(2, businessSegmentTypeEnum, segmentCapacityBind.at(businessSegmentTypeEnum));

        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);
        std::shared_ptr<Passenger> passenger2 = std::make_shared<Passenger>("passenger2", PassengerSegmentType::BUSINESS);
        std::shared_ptr<Passenger> passenger3 = std::make_shared<Passenger>("passenger3", PassengerSegmentType::ECONOMY);
        passenger1->addBaggageItem(13);
        passenger3->addBaggageItem(5);
        passenger2->addBaggageItem(8);

        economySegment.add(passenger1);
        economySegment.add(passenger3);
        ReturnCodeType codeType = businessSegment.add(passenger2);
        assert(codeType == ReturnCodeType::NEED_TRANSFER);

        economySegment.registerBaggage(passenger2);
        assert(economySegment.getBaggageWeight() == 5 + 8);
    }

    static void testSegmentTypeGetter()
    {
        PassengerSegmentType economySegmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegmentType businessSegmentTypeEnum = PassengerSegmentType::BUSINESS;
        PassengerSegment economySegment(30, economySegmentTypeEnum, segmentCapacityBind.at(economySegmentTypeEnum));
        PassengerSegment businessSegment(2, businessSegmentTypeEnum, segmentCapacityBind.at(businessSegmentTypeEnum));

        auto economyTypeVariant = economySegment.getType();
        if (std::holds_alternative<PassengerSegmentType>(economyTypeVariant)) {
            PassengerSegmentType economyTypeVariantUnwrapped = std::get<PassengerSegmentType>(economyTypeVariant);
            assert(economyTypeVariantUnwrapped == economySegmentTypeEnum);
        }

        auto businessTypeVariant = businessSegment.getType();
        if (std::holds_alternative<PassengerSegmentType>(businessTypeVariant)) {
            PassengerSegmentType businessTypeVariantUnwrapped = std::get<PassengerSegmentType>(businessTypeVariant);
            assert(businessTypeVariantUnwrapped == businessSegmentTypeEnum);
        }
    }

    static void testSegmentPositionsGetter()
    {
        PassengerSegmentType economySegmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegment economySegment(20, economySegmentTypeEnum, segmentCapacityBind.at(economySegmentTypeEnum));
        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);
        passenger1->addBaggageItem(13);
        economySegment.add(passenger1);

        assert(economySegment.getBaggagePositions().size() == 1);
    }

    static void testSegmentShowInfo()
    {
        PassengerSegmentType economySegmentTypeEnum = PassengerSegmentType::ECONOMY;
        PassengerSegmentType businessSegmentTypeEnum = PassengerSegmentType::BUSINESS;
        PassengerSegment economySegment(20, economySegmentTypeEnum, segmentCapacityBind.at(economySegmentTypeEnum));
        PassengerSegment businessSegment(2, businessSegmentTypeEnum, segmentCapacityBind.at(businessSegmentTypeEnum));

        std::shared_ptr<Passenger> passenger1 = std::make_shared<Passenger>("passenger1", PassengerSegmentType::ECONOMY);
        std::shared_ptr<Passenger> passenger2 = std::make_shared<Passenger>("passenger2", PassengerSegmentType::BUSINESS);
        passenger1->addBaggageItem(13);
        passenger2->addBaggageItem(8);

        economySegment.add(passenger1);
        economySegment.registerBaggage(passenger2);

        economySegment.showInfo();
        assert(true);
    }

    static void runTests()
    {
        testPassengerInvariant();
        testPassengerBaggageBound();
        testPassengerLuggageBound();
        testPassengerIdGetter();
        testPassengerShowInfo();
        testPassengerLuggageWeightGetter();
        testPassengerWeightCalculations();
        testPassengerAddBaggageItem();
        testPassengerAddLuggageItem();

        testPassengerSegmentInvariant();
        testPassengerSegmentAdd();
        testSegmentInabilityToAdd();
        testSegmentBaggageDrop();
        testPassengerSegmentAllowedWeightGetter();
        testDropBiggestBaggagePosition();
        testRegisterBaggage();
        testEconomyBaggageWipeDueTransfer();
        testSegmentTypeGetter();
        testSegmentPositionsGetter();
        testSegmentShowInfo();

        std::cout << "\nSUCCESS: Passenger tests passed successfully.\n\n";
    }
};
