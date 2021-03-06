#include <Loop/LoopProcessModel.hpp>
#include <Scenario/Commands/TimeNode/AddTrigger.hpp>
#include <Scenario/Commands/TimeNode/RemoveTrigger.hpp>
#include <Scenario/Document/TimeNode/TimeNodeModel.hpp>
#include <QByteArray>

#include "LoopTriggerCommandFactory.hpp"
#include <Scenario/Process/ScenarioInterface.hpp>
#include <iscore/command/SerializableCommand.hpp>
#include <iscore/serialization/DataStreamVisitor.hpp>
#include <iscore/tools/ModelPath.hpp>
#include <iscore/tools/ModelPathSerialization.hpp>

bool LoopTriggerCommandFactory::matches(
        const Scenario::TimeNodeModel& tn) const
{
  return dynamic_cast<Loop::ProcessModel*>(tn.parent());
}

iscore::SerializableCommand* LoopTriggerCommandFactory::make_addTriggerCommand(
        const Scenario::TimeNodeModel& tn) const
{
  if(dynamic_cast<Loop::ProcessModel*>(tn.parent()))
  {
    return new Scenario::Command::AddTrigger<Loop::ProcessModel>(tn);
  }
  return nullptr;
}

iscore::SerializableCommand* LoopTriggerCommandFactory::make_removeTriggerCommand(
        const Scenario::TimeNodeModel& tn) const
{
  if(dynamic_cast<Loop::ProcessModel*>(tn.parent()))
  {
    return new Scenario::Command::RemoveTrigger<Loop::ProcessModel>(tn);
  }
  return nullptr;
}
