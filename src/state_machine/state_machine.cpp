#include "decisions/state_machine/state_machine.h"
#include "decisions/state_machine/transition.h"
#include <utility>


StateMachine::StateMachine(int initialStateAction, int entryAction, int exitAction)
{
    machineStates.emplace_back(initialStateAction, entryAction, exitAction);
}

std::unique_ptr<std::vector<int>> StateMachine::update()
{
    std::unique_ptr<Transition> triggeredPtr;
    int triggeredIndex{};
    std::vector<std::unique_ptr<Transition>>& transitionsRef = machineStates[currentStateIndex].getTransitionsRef();

    for (auto& transition : transitionsRef) {

        if (transition->isTriggered()) {

            triggeredPtr = std::move(transition);
            break;
        }
        triggeredIndex++;
    }
    
    auto actionsPtr = std::make_unique<std::vector<int>>();

    if (triggeredPtr) {

        int targetStateIndex = triggeredPtr->getTargetStateIndex();

        actionsPtr->push_back(machineStates[currentStateIndex].getExitAction());    // Akcja wyjściowa obecnego stanu
        actionsPtr->push_back(triggeredPtr->getAction());   // Akcja przejścia
        actionsPtr->push_back(machineStates[targetStateIndex].getEntryAction());    // Akcja wejścia do nowego stanu

        transitionsRef[triggeredIndex] = std::move(triggeredPtr);
        currentStateIndex = targetStateIndex;    // zmień stan na nowy
        return std::move(actionsPtr);
    }
    else {

        actionsPtr->push_back(machineStates[currentStateIndex].getStateAction());   // brak przejścia, Akcja obecnego stanu
        return std::move(actionsPtr);
    }
}

void StateMachine::addState(int additionalStateAction, int entryAction, int exitAction)
{
    machineStates.emplace_back(additionalStateAction, entryAction, exitAction);
}

void StateMachine::addTransition(int stateIndex, std::unique_ptr<Transition> transitionPtr)
{
    machineStates[stateIndex].addTransition(std::move(transitionPtr));
}
