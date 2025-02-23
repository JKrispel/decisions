#include "decisions/state_machine/state.h"

State::State(int stateAction, int entryAction, int exitAction) :
	stateAction(stateAction), entryAction(entryAction), exitAction(exitAction) {}

int State::getStateAction()
{
	return stateAction;
}

int State::getEntryAction()
{
	return entryAction;
}

int State::getExitAction()
{
	return exitAction;
}

void State::addTransition(std::unique_ptr<Transition> transition)
{
	transitions.push_back(std::move(transition));
}

std::vector<std::unique_ptr<Transition>>& State::getTransitionsRef()
{
	return transitions;  // referencja, Przejścia dalej są własnośćią Stanu
}
