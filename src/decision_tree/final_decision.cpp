#include "decisions/decision_tree/final_decision.h"
#include <memory>
#include <stdexcept>

std::unique_ptr<DecisionTreeNode> FinalDecision::makeDecision()
{
	return std::make_unique<FinalDecision>(*this);
}

Action& FinalDecision::getActionRef()
{
	return this->rAction;
}