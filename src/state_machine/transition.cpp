#include "decisions/state_machine/transition.h"


int Transition::getTargetStateIndex()
{
	return targetStateIndex;
}

int Transition::getAction()
{
	return transitionAction;
}
