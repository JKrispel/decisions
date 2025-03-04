#include "decisions/decision_tree/final_decision.h"

std::unique_ptr<DecisionTreeNode> FinalDecision::makeDecision() {

	return std::make_unique<FinalDecision>(*this);
}

int FinalDecision::getActionType() const
{
	return actionType;
}