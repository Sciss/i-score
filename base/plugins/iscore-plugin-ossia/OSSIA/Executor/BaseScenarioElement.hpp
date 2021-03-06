#pragma once
#include <memory>

#include <QObject>

namespace OSSIA
{
    class TimeValue;
    class StateElement;
}

namespace Scenario
{
class BaseScenario;
}
class DeviceList;
namespace RecreateOnPlay {
class ConstraintElement;
class EventElement;
class StateElement;
class TimeNodeElement;
}  // namespace RecreateOnPlay


namespace RecreateOnPlay
{
struct Context;
class BaseScenarioElement final : public QObject
{
    public:
        BaseScenarioElement(
                const Scenario::BaseScenario& element,
                const Context&,
                QObject* parent);

        ConstraintElement* baseConstraint() const;

        TimeNodeElement* startTimeNode() const;
        TimeNodeElement* endTimeNode() const;

        EventElement* startEvent() const;
        EventElement* endEvent() const;

        StateElement* startState() const;
        StateElement* endState() const;

    private:
        void baseScenarioConstraintCallback(const OSSIA::TimeValue&position,
                                            const OSSIA::TimeValue&date,
                                            std::shared_ptr<OSSIA::StateElement> state);

        const Context& m_ctx;
        ConstraintElement* m_ossia_constraint{};

        TimeNodeElement* m_ossia_startTimeNode{};
        TimeNodeElement* m_ossia_endTimeNode{};

        EventElement* m_ossia_startEvent{};
        EventElement* m_ossia_endEvent{};

        StateElement* m_ossia_startState{};
        StateElement* m_ossia_endState{};
};
}
