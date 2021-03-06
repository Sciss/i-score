#pragma once
#include <Scenario/Commands/ScenarioCommandFactory.hpp>
#include <boost/optional/optional.hpp>
#include <iscore/command/SerializableCommand.hpp>
#include <iscore/tools/ModelPath.hpp>

#include <iscore/tools/SettableIdentifier.hpp>
#include <iscore_plugin_scenario_export.h>
class DataStreamInput;
class DataStreamOutput;

namespace Scenario
{
class ConstraintViewModel;
class RackModel;
namespace Command
{
/**
         * @brief The ShowRackInViewModel class
         *
         * For a given constraint view model,
         * select the rack that is to be shown, and show it.
         */
class ISCORE_PLUGIN_SCENARIO_EXPORT ShowRackInViewModel final : public iscore::SerializableCommand
{
        ISCORE_COMMAND_DECL(ScenarioCommandFactoryName(), ShowRackInViewModel, "Show a rack")
        public:
            ShowRackInViewModel(
                Path<ConstraintViewModel>&& constraint_path,
                const Id<RackModel>& rackId);
        ShowRackInViewModel(
                const ConstraintViewModel& vm,
                const Id<RackModel>& rackId);

        void undo() const override;
        void redo() const override;

    protected:
        void serializeImpl(DataStreamInput&) const override;
        void deserializeImpl(DataStreamOutput&) override;

    private:
        Path<ConstraintViewModel> m_constraintViewPath;
        Id<RackModel> m_rackId {};
        Id<RackModel> m_previousRackId {};

};
}
}
