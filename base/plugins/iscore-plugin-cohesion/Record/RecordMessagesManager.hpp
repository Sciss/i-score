#pragma once
#include <Record/RecordTools.hpp>
#include <RecordedMessages/RecordedMessagesProcessModel.hpp>
namespace Recording
{
struct RecordMessagesData
{
};
class RecordMessagesManager final : public QObject
{
    public:
        RecordMessagesManager(const iscore::DocumentContext& ctx);

        void recordInNewBox(Scenario::ScenarioModel& scenar, Scenario::Point pt);
        // TODO : recordInExstingBox; recordFromState.
        void stopRecording();

        void commit();

    private:
        const iscore::DocumentContext& m_ctx;
        std::unique_ptr<RecordCommandDispatcher> m_dispatcher;
        std::vector<QMetaObject::Connection> m_recordCallbackConnections;

        Explorer::DeviceExplorerModel* m_explorer{};

        QTimer m_recordTimer;
        bool m_firstValueReceived{};
        std::chrono::steady_clock::time_point start_time_pt;

        RecordedMessages::ProcessModel* m_createdProcess{};
        QList<RecordedMessages::RecordedMessage> m_records;
};
}
