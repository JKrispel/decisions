#pragma once
#include "decisions/decision_tree/decision_tree_node.h"
#include "decisions/decision_tree/decision.h"
#include "decisions/decision_tree/final_decision.h"
#include <iostream>
#include <gtest/gtest.h>

// Possible Actions
enum class NpcAction {
    FOLLOW,
    STOP,
};

class TestDecision : public Decision {
public:
    std::unique_ptr<DecisionTreeNode> getBranch() override {
        int distance = 4; // mniej niż 5, więc konsekwencją będzie StopAction

        if (distance < 5) {
            // Return FinalDecision with StopAction
            return std::make_unique<FinalDecision<NpcAction>>(NpcAction::STOP);
        }
        else {
            // Return FinalDecision with FollowAction
            return std::make_unique<FinalDecision<NpcAction>>(NpcAction::FOLLOW);
        }
    }
};


TEST(DecisionTreeTest, ActionInheritedBasedOnDistance) {
    TestDecision rootNode;

    // Call the decision-making logic
    std::unique_ptr<DecisionTreeNode> decision = rootNode.getBranch();

    // Verify that the decision is a FinalDecision<NpcAction>
    auto* finalDecision = dynamic_cast<FinalDecision<NpcAction>*>(decision.get());
    ASSERT_NE(finalDecision, nullptr) << "Expected decision to be of type FinalDecision<NpcAction>.";

    // Get the stored action type
    NpcAction actionType = finalDecision->getActionType();

    // Check if the action type is STOP
    ASSERT_EQ(actionType, NpcAction::STOP) << "Expected NpcAction::STOP but got a different action.";
}
