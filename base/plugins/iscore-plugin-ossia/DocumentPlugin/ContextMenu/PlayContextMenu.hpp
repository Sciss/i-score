#pragma once
#include "source/Control/Menus/AbstractMenuActions.hpp"

class PlayContextMenu : public AbstractMenuActions
{
    public:
        PlayContextMenu(ScenarioControl* parent);
        void fillMenuBar(iscore::MenubarManager *menu) override;
        void fillContextMenu(QMenu* menu, const Selection&) override;

        QList<QAction *> actions() override;

    private:
        QAction* m_playStates;
        QAction *m_playEvents;
        QAction *m_playConstraints;

};