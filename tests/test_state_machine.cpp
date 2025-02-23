#pragma once
#include "decisions/state_machine/state_machine.h"
#include "decisions/state_machine/state.h"
#include <iostream>
#include <gtest/gtest.h>

// możliwe Akcje
enum class NpcAction {
    WAIT,
    ATTACK,
};

int hp = 100;   // jakaś zmienna świata gry

class TestTransition : public Transition {

public:
    TestTransition(int targetStateIndex, int transitionAction)
        : Transition(targetStateIndex, transitionAction) {
    }

    bool isTriggered() override {

        if (hp < 5) {

            return true;
        }
        else {
            return false;
        }
    }
};


TEST(StateMachineTest, ExampleStateMachine) {
    // konstrukcja 1 stanowej maszyny z przejściem do tego samego Stanu
    auto testMachine = std::make_unique<StateMachine>(  // heap allocation (obiekt jest całkiem złożony)
        static_cast<int>(NpcAction::WAIT),  // state Action
        static_cast<int>(NpcAction::WAIT),  // entry 
        static_cast<int>(NpcAction::WAIT)); // exit

    // Przejście zależne od hp, ze Stanu o indeksie 0 (początkowego) do Stanu o indeksie 0, wykonując akcję Attack
    testMachine->addTransition(0, std::make_unique<TestTransition>(0, static_cast<int>(NpcAction::ATTACK)));

    // działanie Maszyny Stanów
    std::unique_ptr<std::vector<int>> resultActions = testMachine->update(); // Akcje wynikowe
    ASSERT_EQ(resultActions->at(0), static_cast<int>(NpcAction::WAIT)) << "Expected WAIT but got a different action.";

    hp = 3; // *hp spada poniżej 5*
    resultActions = testMachine->update();   // ponowne podjęcie decyzji
    // [wyjściowa->WAIT, przejściowa->ATTACK, wyjściowa->WAIT]
    ASSERT_EQ(resultActions->at(0), static_cast<int>(NpcAction::WAIT)) << "Expected WAIT but got a different action.";
    ASSERT_EQ(resultActions->at(1), static_cast<int>(NpcAction::ATTACK)) << "Expected ATTACK but got a different action.";
    ASSERT_EQ(resultActions->at(2), static_cast<int>(NpcAction::WAIT)) << "Expected WAIT but got a different action.";
}
