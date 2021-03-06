#pragma once
#include <iscore/plugins/panel/PanelPresenter.hpp>

namespace Library
{
class LibraryPanelPresenter : public iscore::PanelPresenter
{
    public:
        LibraryPanelPresenter(
                iscore::PanelView* view,
                QObject* parent);

        int panelId() const override;

        void on_modelChanged(
                iscore::PanelModel* oldm,
                iscore::PanelModel* newm) override;

    private:
        QMetaObject::Connection m_mvConnection;
};
}
