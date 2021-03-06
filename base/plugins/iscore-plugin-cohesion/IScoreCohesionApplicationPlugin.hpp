#pragma once
#include <iscore/plugins/application/GUIApplicationContextPlugin.hpp>
#include <memory>
#include <vector>

#include "Record/RecordManager.hpp"
#include "Record/RecordMessagesManager.hpp"

class QAction;
namespace Scenario {
class ScenarioModel;
struct Point;
}  // namespace Scenario
namespace iscore {

class MenubarManager;
struct OrderedToolbar;
}  // namespace iscore

class IScoreCohesionApplicationPlugin final :
        public QObject,
        public iscore::GUIApplicationContextPlugin
{
    public:
        IScoreCohesionApplicationPlugin(const iscore::ApplicationContext& app);
        void populateMenus(iscore::MenubarManager*) override;
        std::vector<iscore::OrderedToolbar> makeToolbars() override;

        void record(Scenario::ScenarioModel&, Scenario::Point pt);
        void recordMessages(Scenario::ScenarioModel&, Scenario::Point pt);
        void stopRecord();

    private:
        QAction* m_snapshot{};
        QAction* m_curves{};

        QAction* m_stopAction{};

        std::unique_ptr<Recording::RecordManager> m_recManager;
        std::unique_ptr<Recording::RecordMessagesManager> m_recMessagesManager;
};
