#pragma once
#include "decisions/decision_tree/decision_tree_node.h"
#include "decisions/decision_tree/decision.h"
#include "decisions/decision_tree/final_decision.h"
#include <iostream>
#include <gtest/gtest.h>

// możliwe Akcje
enum NpcAction {
    FOLLOW,
    STOP,
};

class TestDecision : public Decision {
public:
    std::unique_ptr<DecisionTreeNode> getBranch() override {
        int distance = 4; // mniej niż 5, więc konsekwencją będzie StopAction

        if (distance < 5) {

            return std::make_unique<FinalDecision>(NpcAction::STOP);
        }
        else {

            return std::make_unique<FinalDecision>(NpcAction::FOLLOW);
        }
    }
};


TEST(DecisionTreeTest, ActionInheritedBasedOnDistance) {
    TestDecision rootNode;

    // algorytm decyzyjny
    std::unique_ptr<DecisionTreeNode> decision = rootNode.getBranch();

    // zweryfikuj, że typ to FinalDecision<NpcAction>
    auto* finalDecision = dynamic_cast<FinalDecision*>(decision.get());
    ASSERT_NE(finalDecision, nullptr) << "Expected decision to be of type FinalDecision<NpcAction>.";

    int actionType = finalDecision->getActionType();

    ASSERT_EQ(actionType, NpcAction::STOP) << "Expected NpcAction::STOP but got a different action.";
}
