#pragma once

#include <Scenario/Commands/ScenarioCommandFactory.hpp>
#include <boost/optional/optional.hpp>
#include <iscore/command/SerializableCommand.hpp>
#include <iscore/tools/ModelPath.hpp>
#include <QString>
#include <QVector>

#include <iscore/tools/SettableIdentifier.hpp>

class DataStreamInput;
class DataStreamOutput;

namespace Scenario
{
class ScenarioModel;
class EventModel;
class StateModel;

namespace Command
{
class SplitEvent final : public iscore::SerializableCommand
{
        ISCORE_COMMAND_DECL(ScenarioCommandFactoryName(), SplitEvent, "Split an event")
        public:

            SplitEvent(
                const Path<Scenario::ScenarioModel>& scenario,
                const Id<EventModel>& event,
                const QVector<Id<StateModel>>& movingstates);

        void undo() const override;
        void redo() const override;

    protected:
        void serializeImpl(DataStreamInput&) const override;
        void deserializeImpl(DataStreamOutput&) override;

    private:
        Path<Scenario::ScenarioModel> m_scenarioPath;

        Id<EventModel> m_originalEvent;
        Id<EventModel> m_newEvent;
        QString m_createdName;
        QVector<Id<StateModel>> m_movingStates;
};
}
}
