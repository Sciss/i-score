#pragma once
#include "GenericToolState.hpp"
#include "States/CreateEventState.hpp"

class CreationToolState : public GenericToolState
{
    public:
        CreationToolState(const ScenarioStateMachine& sm);

        void on_scenarioPressed() override;
        void on_scenarioMoved() override;
        void on_scenarioReleased() override;

    private:
        template<typename EventFun,
                 typename TimeNodeFun,
                 typename NothingFun>
        void mapWithCollision(
                EventFun&& ev_fun,
                TimeNodeFun&& tn_fun,
                NothingFun&& nothing_fun,
                const id_type<EventModel>& createdEvent,
                const id_type<TimeNodeModel>& createdTimeNode)
        {
            auto collidingEvents = getCollidingModels(m_sm.presenter().events(), createdEvent);
            if(!collidingEvents.empty())
            {
                ev_fun(collidingEvents.first()->id());
                return;
            }

            auto collidingTimeNodes = getCollidingModels(m_sm.presenter().timeNodes(), createdTimeNode);
            if(!collidingTimeNodes.empty())
            {
                tn_fun(collidingTimeNodes.first()->id());
                return;
            }

            nothing_fun();
        }

        CreateFromEventState* m_createFromEventState{};
        QState* m_waitState{};
};