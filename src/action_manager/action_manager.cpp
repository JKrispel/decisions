#include "decisions/action_manager/action_manager.h"

void ActionManager::scheduleAction(std::unique_ptr<Action> action)
{
	queue.push(std::move(action));
}

void ActionManager::execute(float currentTime) // czas z pętli gry
{   
	// currentTime = getTime()	finalna wersja
    float priorityCutoff = 100.0f;  // bardzo niski domyślny priorytet, umożliwi to dodanie pierwszej Akcji do active
        // lepsza opcja to podawanie skali priority przez użytkownika - maxPrio
        // oraz zwykła inicjalizacja priorityCutoff
    if (!active.empty()) {
        // *active.begin()->priority < maxPrio
        priorityCutoff = (*active.begin())->priority;
    }
    std::vector<std::unique_ptr<Action>> queueSnapshot;

    while (!queue.empty()) {
        // utwórz snapshot queue
        std::unique_ptr<Action> action = std::move(const_cast<std::unique_ptr<Action>&>(queue.top()));

        // zrób snapshot queue dla ważnych Akcji
        if (action->expiryTime > currentTime) {
            queueSnapshot.push_back(std::move(action));  // nowym posiadaczem jest queueSnapshot
        }
        queue.pop();
    }

    for (auto it = queueSnapshot.begin(); it != queueSnapshot.end();) {
        // Akcja po dereferencji iteratora
        auto& rAction = *it;
        // jeśli nie natrafisz w queue na Akcje o wyższym priorytecie, to wyjdź z pętli
        if (rAction->priority >= priorityCutoff) {

            break;  // cutoff
        }
        // jeśli Akcja to interrupter, wykonaj go zamiast pozostałych
        if (rAction->interrupt()) {           
            // zastąp active daną Akcją
            active.clear();
            priorityCutoff = rAction->priority;
            active.insert(std::move(rAction));
            // usuń ją z queueSnapshot
            it = queueSnapshot.erase(it);
            continue;
        }
        else {
            // sprawdź, czy możemy dodać Akcję
            bool canAddToActive = true;

            if (!active.empty()) {

                for (const auto& pActiveAction : active) {

                    if (!pActiveAction->canDoBoth(rAction)) {

                        canAddToActive = false;
                        break;
                    }
                }
            }
            // jeżeli może być wykonana wraz z inną akcją, wykonaj
            if (canAddToActive) {               
                // dodaj Akcję do active
                priorityCutoff = rAction->priority;
                active.insert(std::move(rAction));
                // usuń ją z queueSnapshot
                it = queueSnapshot.erase(it);
                continue;
            }
        }
        ++it;
    }
    // usuń lub wykonaj Akcje z active
    for (auto it = active.begin(); it != active.end();) {

        if ((*it)->isComplete()) {

            it = active.erase(it);
        }
        else {
            (*it)->execute();
            ++it;
        }
    }
    // zbuduj ponownie queue dla ważnych Akcji
    for (auto& action : queueSnapshot) {
       
        queue.push(std::move(action));
    }
}
