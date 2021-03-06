#pragma once
#include <Loop/LoopProcessMetadata.hpp>
#include <Process/Process.hpp>
#include <Scenario/Document/BaseScenario/BaseScenarioContainer.hpp>
#include <QByteArray>
#include <QString>
#include <QVector>


#include <Process/TimeValue.hpp>
#include <iscore/selection/Selection.hpp>
#include <iscore/serialization/VisitorInterface.hpp>
#include <iscore/tools/SettableIdentifier.hpp>
#include <iscore_plugin_loop_export.h>

class DataStream;
class JSONObject;
namespace Process { class LayerModel; }
class ProcessStateDataInterface;
class QObject;
namespace Scenario
{
class TimeNodeModel;
class ConstraintModel;
}

namespace Loop
{
class ISCORE_PLUGIN_LOOP_EXPORT ProcessModel final :
        public Process::ProcessModel,
        public Scenario::BaseScenarioContainer
{
        ISCORE_SERIALIZE_FRIENDS(Loop::ProcessModel, DataStream)
        ISCORE_SERIALIZE_FRIENDS(Loop::ProcessModel, JSONObject)

    public:
        explicit ProcessModel(
                const TimeValue& duration,
                const Id<Process::ProcessModel>& id,
                QObject* parentObject);

        explicit ProcessModel(
                const Loop::ProcessModel& source,
                const Id<Process::ProcessModel>& id,
                QObject* parentObject);

        template<typename Impl>
        explicit ProcessModel(
                Deserializer<Impl>& vis,
                QObject* parent) :
            Process::ProcessModel{vis, parent},
            BaseScenarioContainer{this}
        {
            vis.writeTo(*this);
        }

        using BaseScenarioContainer::event;
        using QObject::event;

        // Process interface
        ProcessModel* clone(
                const Id<Process::ProcessModel>& newId,
                QObject* newParent) const override;

        UuidKey<Process::ProcessFactory>concreteFactoryKey() const override
        {
            return Metadata<ConcreteFactoryKey_k, ProcessModel>::get();
        }

        QString prettyName() const override;
        QByteArray makeLayerConstructionData() const override;

        void setDurationAndScale(const TimeValue& newDuration) override;
        void setDurationAndGrow(const TimeValue& newDuration) override;
        void setDurationAndShrink(const TimeValue& newDuration) override;

        void startExecution() override;
        void stopExecution() override;
        void reset() override;

        ProcessStateDataInterface* startStateData() const override;
        ProcessStateDataInterface* endStateData() const override;

        Selection selectableChildren() const override;
        Selection selectedChildren() const override;
        void setSelection(const Selection& s) const override;

        void serialize_impl(const VisitorVariant& vis) const override;

        ~ProcessModel();
    protected:
        Process::LayerModel* makeLayer_impl(
                const Id<Process::LayerModel>& viewModelId,
                const QByteArray& constructionData,
                QObject* parentObject) override;
        Process::LayerModel* loadLayer_impl(
                const VisitorVariant&,
                QObject* parentObject) override;
        Process::LayerModel* cloneLayer_impl(
                const Id<Process::LayerModel>& newId,
                const Process::LayerModel& source,
                QObject* parentObject) override;

};


const QVector<Id<Scenario::ConstraintModel> > constraintsBeforeTimeNode(
        const Loop::ProcessModel& scen,
        const Id<Scenario::TimeNodeModel>& timeNodeId);
}
