#pragma once
#include "decisions/action_manager/action.h"
#include "decisions/decision_tree/decision_tree_node.h"
#include "decisions/decision_tree/decision.h"
#include "decisions/decision_tree/final_decision.h"
#include <iostream>
#include <gtest/gtest.h>


// StopAction: Represents an action to "stop"
class StopAction : public Action {
public:
    StopAction(float priority, float expiryTime = 10.0f, bool complete = false)
        : Action(priority, expiryTime, complete) {
    }

    void execute() override {
        std::cout << "StopAction executed!" << std::endl;
    }
};

// FollowAction: Represents an action to "follow"
class FollowAction : public Action {
public:
    FollowAction(float priority, float expiryTime = 10.0f, bool complete = false)
        : Action(priority, expiryTime, complete) {
    }

    void execute() override {
        std::cout << "FollowAction executed!" << std::endl;
    }
};

StopAction stop(1.0f);
FollowAction follow(1.0f);

class TestDecision : public Decision {
public:
    std::unique_ptr<DecisionTreeNode> getBranch() override {
        int distance = 4; // mniej niż 5, więc konsekwencją będzie StopAction

        if (distance < 5) {
            // Return FinalDecision with StopAction
            return std::make_unique<FinalDecision>(stop);
        }
        else {
            // Return FinalDecision with FollowAction
            return std::make_unique<FinalDecision>(follow);
        }
    }
};


TEST(DecisionTreeTest, ActionInheritedBasedOnDistance) {
    TestDecision rootNode;

    // Call the decision-making logic
    std::unique_ptr<DecisionTreeNode> decision = rootNode.makeDecision();

    // Verify that the decision is a FinalDecision
    ASSERT_TRUE(dynamic_cast<FinalDecision*>(decision.get()) != nullptr)
        << "Expected decision to be FinalDecision.";

    // Cast the decision to FinalDecision to access getActionRef()
    FinalDecision* finalDecision = dynamic_cast<FinalDecision*>(decision.get());
    ASSERT_TRUE(finalDecision != nullptr) << "Expected decision to be of type FinalDecision.";

    // Get the Action reference from FinalDecision
    Action& action = finalDecision->getActionRef();
    // Check the type of Action and execute
    if (dynamic_cast<StopAction*>(&action)) {
        std::cout << "StopAction is the chosen action." << std::endl;
        action.execute(); // Should output: StopAction executed!
    }
    else if (dynamic_cast<FollowAction*>(&action)) {
        FAIL() << "FollowAction chosen instead of StopAction." << std::endl;
        action.execute(); // Should output: FollowAction executed!
    }
    else {
        FAIL() << "Action type is neither StopAction nor FollowAction.";
    }
}
