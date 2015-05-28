#include "AbstractConstraintPresenter.hpp"
#include "AbstractConstraintView.hpp"
#include "AbstractConstraintViewModel.hpp"

#include "Document/Event/EventModel.hpp"
#include "Document/Constraint/ConstraintModel.hpp"
#include "Document/Constraint/Box/BoxPresenter.hpp"
#include "Document/Constraint/Box/BoxView.hpp"
#include "Commands/Constraint/AddProcessToConstraint.hpp"
#include <QGraphicsScene>

#include "Temporal/TemporalConstraintViewModel.hpp"
#include "FullView/FullViewConstraintViewModel.hpp"
/**
 * TODO Mettre dans la doc :
 * L'abstract constraint presenter a deux interfaces :
 *  - une qui est relative à la gestion de la vue (setScaleFactor)
 *  - une qui est là pour interagir avec le modèle (on_defaul/min/maxDurationChanged)
 */

AbstractConstraintPresenter::AbstractConstraintPresenter(QString name,
    const AbstractConstraintViewModel& model,
    AbstractConstraintView* view,
    QObject* parent) :
    NamedObject {name, parent},
    m_viewModel {model},
    m_view {view}
{
    connect(&m_viewModel.model().selection, &Selectable::changed,
            m_view, &AbstractConstraintView::setSelected);

    connect(&m_viewModel.model(),   &ConstraintModel::minDurationChanged,
    this,                           &AbstractConstraintPresenter::on_minDurationChanged);
    connect(&m_viewModel.model(),   &ConstraintModel::defaultDurationChanged,
    this,                           &AbstractConstraintPresenter::on_defaultDurationChanged);
    connect(&m_viewModel.model(),   &ConstraintModel::maxDurationChanged,
    this,                           &AbstractConstraintPresenter::on_maxDurationChanged);

    connect(&m_viewModel.model(), &ConstraintModel::heightPercentageChanged,
            this, &AbstractConstraintPresenter::heightPercentageChanged);

    connect(&m_viewModel, &AbstractConstraintViewModel::boxShown,
    this,                &AbstractConstraintPresenter::on_boxShown);
    connect(&m_viewModel, &AbstractConstraintViewModel::boxHidden,
    this,                &AbstractConstraintPresenter::on_boxHidden);
    connect(&m_viewModel, &AbstractConstraintViewModel::boxRemoved,
    this,                &AbstractConstraintPresenter::on_boxRemoved);

    connect(&m_viewModel.model(), &ConstraintModel::playDurationChanged,
            [&] (const TimeValue& t) { m_view->setPlayWidth(t.toPixels(m_zoomRatio));});

    connect(&m_viewModel.model().consistency, &ModelConsistency::validChanged,
            m_view, &AbstractConstraintView::setValid);
}

void AbstractConstraintPresenter::updateScaling()
{
    const auto& cm = m_viewModel.model();
    // prendre en compte la distance du clic à chaque côté
    m_view->setDefaultWidth(cm.defaultDuration().toPixels(m_zoomRatio));
    m_view->setMinWidth(cm.minDuration().toPixels(m_zoomRatio));
    m_view->setMaxWidth(cm.maxDuration().isInfinite(),
                        cm.maxDuration().isInfinite()? -1 : cm.maxDuration().toPixels(m_zoomRatio));

    if(box())
    {
        box()->setWidth(m_view->defaultWidth() - 20);
    }

    updateHeight();
}

void AbstractConstraintPresenter::on_zoomRatioChanged(ZoomRatio val)
{
    m_zoomRatio = val;
    updateScaling();

    if(box())
    {
        box()->on_zoomRatioChanged(m_zoomRatio);
    }
}

const id_type<ConstraintModel>& AbstractConstraintPresenter::id() const
{
    return model().id();
}

void AbstractConstraintPresenter::on_defaultDurationChanged(const TimeValue& val)
{
    m_view->setDefaultWidth(val.toPixels(m_zoomRatio));

    emit askUpdate();
    m_view->update();
}

void AbstractConstraintPresenter::on_minDurationChanged(const TimeValue& min)
{
    m_view->setMinWidth(min.toPixels(m_zoomRatio));

    emit askUpdate();
    m_view->update();
}

void AbstractConstraintPresenter::on_maxDurationChanged(const TimeValue& max)
{
    m_view->setMaxWidth(max.isInfinite(),
                        max.isInfinite()? -1 : max.toPixels(m_zoomRatio));

    emit askUpdate();
    m_view->update();
}

void AbstractConstraintPresenter::updateHeight()
{
    if(m_viewModel.isBoxShown())
    {
        m_view->setHeight(box()->height() + 60);
    }
    else
    {
        // TODO faire vue appropriée plus tard
        m_view->setHeight(25);
    }

    emit askUpdate();
    m_view->update();
    emit heightChanged();
}

bool AbstractConstraintPresenter::isSelected() const
{
    return m_viewModel.model().selection.get();
}

BoxPresenter* AbstractConstraintPresenter::box() const
{
    return m_box;
}

const ConstraintModel& AbstractConstraintPresenter::model() const
{
    return m_viewModel.model();
}

const AbstractConstraintViewModel&AbstractConstraintPresenter::abstractConstraintViewModel() const
{
    return m_viewModel;
}

AbstractConstraintView*AbstractConstraintPresenter::view() const
{
    return m_view;
}

void AbstractConstraintPresenter::on_boxShown(const id_type<BoxModel>& boxId)
{
    clearBoxPresenter();
    createBoxPresenter(m_viewModel.model().box(boxId));

    updateHeight();
}

void AbstractConstraintPresenter::on_boxHidden()
{
    clearBoxPresenter();

    updateHeight();
}

void AbstractConstraintPresenter::on_boxRemoved()
{
    clearBoxPresenter();

    updateHeight();
}

void AbstractConstraintPresenter::clearBoxPresenter()
{
    if(m_box)
    {
        m_box->deleteLater();
        m_box = nullptr;
    }
}

void AbstractConstraintPresenter::createBoxPresenter(BoxModel* boxModel)
{
    auto boxView = new BoxView {m_view};
    boxView->setPos(0, 5);

    // Cas par défaut
    m_box = new BoxPresenter {*boxModel,
                              boxView,
                              this};

    m_box->on_zoomRatioChanged(m_zoomRatio);

    connect(m_box, &BoxPresenter::askUpdate,
            this,  &AbstractConstraintPresenter::updateHeight);

    connect(m_box, &BoxPresenter::pressed, this, &AbstractConstraintPresenter::pressed);
    connect(m_box, &BoxPresenter::moved, this, &AbstractConstraintPresenter::moved);
    connect(m_box, &BoxPresenter::released, this, &AbstractConstraintPresenter::released);
}