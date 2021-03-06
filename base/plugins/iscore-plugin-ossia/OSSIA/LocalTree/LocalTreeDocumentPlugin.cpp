#include "LocalTreeDocumentPlugin.hpp"
#include <Network/Device.h>
#include <Editor/Value.h>
#include <Network/Address.h>


#include <Curve/CurveModel.hpp>
#include <Automation/AutomationModel.hpp>

#include <Scenario/Document/ScenarioDocument/ScenarioDocumentModel.hpp>
#include <Scenario/Document/BaseScenario/BaseScenario.hpp>
#include <Scenario/Document/Constraint/ConstraintModel.hpp>
#include <Scenario/Document/Event/EventModel.hpp>
#include <Scenario/Document/State/StateModel.hpp>
#include <Scenario/Document/State/ItemModel/MessageItemModel.hpp>
#include <Scenario/Document/TimeNode/TimeNodeModel.hpp>
#include <Scenario/Document/TimeNode/Trigger/TriggerModel.hpp>
#include <Scenario/Process/ScenarioModel.hpp>
#include <Scenario/Process/Algorithms/Accessors.hpp>

#include <State/Message.hpp>
#include <State/Value.hpp>

#include <Process/State/MessageNode.hpp>

#include <Curve/Segment/CurveSegmentData.hpp>

#include <core/document/Document.hpp>
#include <core/document/DocumentModel.hpp>
#include <iscore/document/DocumentInterface.hpp>
#include <OSSIA/OSSIA2iscore.hpp>
#include <OSSIA/iscore2OSSIA.hpp>

#include "Scenario/ScenarioComponent.hpp"

Ossia::LocalTree::DocumentPlugin::DocumentPlugin(
        std::shared_ptr<OSSIA::Device> localDev,
        iscore::Document& doc,
        QObject* parent):
    iscore::DocumentPlugin{doc, "LocalTree::DocumentPlugin", parent},
    m_localDevice{localDev}
{
    auto scenar = dynamic_cast<Scenario::ScenarioDocumentModel*>(
                      &m_context.document.model().modelDelegate());
    ISCORE_ASSERT(scenar);
    auto& cstr = scenar->baseScenario().constraint();
    auto comp = new ConstraintComponent(
                *m_localDevice,
                Id<iscore::Component>{0},
                cstr,
                *this,
                doc.context(),
                this);
    cstr.components.add(comp);

    con(doc, &iscore::Document::aboutToClose,
            this, [=,&cstr] () {
        // Remove the node from local device
        auto it = find_if(m_localDevice->children(), [&] (const auto& node)
        { return node == comp->node(); });
        ISCORE_ASSERT(it != m_localDevice->children().end());

        m_localDevice->erase(it);

        // Delete
        cstr.components.remove(comp);
    });
}
