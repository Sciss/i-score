#pragma once
#include <Scenario/Application/ScenarioEditionSettings.hpp>
#include <iscore/plugins/application/GUIApplicationContextPlugin.hpp>

#include <QVector>
#include <vector>
#include <Scenario/Palette/ScenarioPoint.hpp>
#include <iscore_plugin_scenario_export.h>

namespace Process {
class LayerPresenter;
class ProcessFocusManager;
}
namespace iscore {
class Document;
class MenubarManager;
struct OrderedToolbar;
}  // namespace iscore

class QAction;
namespace Scenario {
class ObjectMenuActions;
class ScenarioActions;
class TemporalScenarioPresenter;
class ToolMenuActions;
class ScenarioModel;
class ScenarioInterface;
class StateModel;

class ISCORE_PLUGIN_SCENARIO_EXPORT ScenarioApplicationPlugin final :
        public QObject,
        public iscore::GUIApplicationContextPlugin
{
        Q_OBJECT
        friend class ScenarioContextMenuManager;
    public:
        ScenarioApplicationPlugin(const iscore::ApplicationContext& app);
        ~ScenarioApplicationPlugin();

        void populateMenus(iscore::MenubarManager*) override;
        std::vector<iscore::OrderedToolbar> makeToolbars() override;
        std::vector<QAction*> actions() override;

        QVector<ScenarioActions*>& pluginActions()
        { return m_pluginActions; }

        const Scenario::ScenarioModel* focusedScenarioModel() const;
        const Scenario::ScenarioInterface* focusedScenarioInterface() const;
        TemporalScenarioPresenter* focusedPresenter() const;

        void reinit_tools();

        Scenario::EditionSettings& editionSettings()
        { return m_editionSettings; }

        Process::ProcessFocusManager* processFocusManager() const;

    signals:
        void keyPressed(int);
        void keyReleased(int);

        void startRecording(Scenario::ScenarioModel&, Scenario::Point);
        void startRecordingMessages(Scenario::ScenarioModel&, Scenario::Point);
        void stopRecording();

        void playState(Id<StateModel>);
        void playAtDate(const TimeValue&);

    protected:
        void prepareNewDocument() override;

        void on_documentChanged(
                iscore::Document* olddoc,
                iscore::Document* newdoc) override;

        void on_activeWindowChanged() override;

    private:
        QMetaObject::Connection m_focusConnection, m_defocusConnection, m_contextMenuConnection;
        Scenario::EditionSettings m_editionSettings;

        ObjectMenuActions* m_objectAction{};
        ToolMenuActions* m_toolActions{};
        QVector<ScenarioActions*> m_pluginActions;

        QAction *m_selectAll{};
        QAction *m_deselectAll{};

        void on_presenterFocused(Process::LayerPresenter* lm);
        void on_presenterDefocused(Process::LayerPresenter* lm);
};
}
