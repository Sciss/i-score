#pragma once

#include <Process/TimeValue.hpp>
#include <iscore/plugins/customfactory/FactoryInterface.hpp>
#include <QByteArray>
#include <QString>
#include <iscore_lib_process_export.h>
#include <iscore/tools/SettableIdentifier.hpp>

class QGraphicsItem;
class QObject;
struct VisitorVariant;

namespace Process
{
class LayerModel;
class LayerPresenter;
class LayerView;
class ProcessModel;

/**
     * @brief The ProcessFactory class
     *
     * Interface to make processes, like Scenario, Automation...
     */

class ISCORE_LIB_PROCESS_EXPORT ProcessFactory :
        public iscore::AbstractFactory<ProcessFactory>
{
        ISCORE_ABSTRACT_FACTORY_DECL(
                ProcessFactory,
                "507ae654-f3b8-4aae-afc3-7ab8e1a3a86f")
    public:
        virtual ~ProcessFactory();
        virtual QString prettyName() const = 0;

        virtual ProcessModel* makeModel(
                const TimeValue& duration,
                const Id<ProcessModel>& id,
                QObject* parent) = 0;

        // The layers may need some specific static data to construct,
        // this provides it (for the sake of commands)
        virtual QByteArray makeStaticLayerConstructionData() const = 0;

        // throws if the serialization method is not implemented by the subclass
        virtual ProcessModel* load(
                const VisitorVariant&,
                QObject* parent) = 0;

        // TODO Make it take a view name, too (cf. logical / temporal).
        // Or make it be created by the ViewModel, and the View be created by the presenter.
        virtual LayerPresenter* makeLayerPresenter(
                const LayerModel&,
                LayerView*,
                QObject* parent) = 0;

        virtual LayerView* makeLayerView(
                const LayerModel& view,
                QGraphicsItem* parent) = 0;
};
}
