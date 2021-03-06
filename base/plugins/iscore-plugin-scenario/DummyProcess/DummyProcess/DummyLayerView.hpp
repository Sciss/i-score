#pragma once
#include <Process/LayerView.hpp>
#include <QString>
#include <iscore_lib_dummyprocess_export.h>


class QGraphicsItem;
class QPainter;
class QQuickView;
class QQuickItem;

namespace Dummy
{
class ISCORE_LIB_DUMMYPROCESS_EXPORT DummyLayerView final : public Process::LayerView
{
        Q_OBJECT
    public:
        explicit DummyLayerView(QGraphicsItem* parent);

        void setText(const QString& text)
        {
            m_text = text;
            update();
        }

    signals:
        void pressed();


    private:
        void paint_impl(QPainter*) const override;
        void mousePressEvent(QGraphicsSceneMouseEvent*) override;
        void mouseMoveEvent(QGraphicsSceneMouseEvent*) override;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent*) override;
        QString m_text;
        QQuickView* m_view{};
        QQuickItem* m_item{};
};
}
