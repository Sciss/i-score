#include <Scenario/Application/Menus/ObjectMenuActions.hpp>
#include <Scenario/Application/Menus/ToolMenuActions.hpp>
#include <Scenario/Application/Menus/TransportActions.hpp>

#include <Scenario/Application/Menus/Plugin/ScenarioActionsFactory.hpp>
#include "ScenarioCommonContextMenuFactory.hpp"
#include <iscore/menu/MenuInterface.hpp>


namespace Scenario
{
QList<ScenarioActions *> ScenarioCommonActionsFactory::make(ScenarioApplicationPlugin *ctrl)
{
    return QList<ScenarioActions *>{
        new ObjectMenuActions(iscore::ToplevelMenuElement::ObjectMenu, ctrl),
        new ToolMenuActions(iscore::ToplevelMenuElement::ToolMenu, ctrl),
        new TransportActions(iscore::ToplevelMenuElement::PlayMenu, ctrl)
    };
}
}
