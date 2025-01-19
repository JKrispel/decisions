#include "decisions/action_manager/action.h"
#include <iostream>

bool Action::interrupt()
{
    return false;
}

bool Action::canDoBoth(const std::unique_ptr<Action>& other)
{   
    return false;   
}

bool Action::isComplete() const
{
    return complete;
}
