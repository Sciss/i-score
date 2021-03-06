#pragma once
#include <iscore/document/DocumentContext.hpp>

namespace Process { class ProcessFocusManager; }
namespace iscore {
class Document;
}  // namespace iscore

namespace Scenario
{
class ScenarioDocumentPresenter;
class BaseElementContext : public iscore::DocumentContext
{
    public:
        BaseElementContext(
                iscore::Document& doc,
                ScenarioDocumentPresenter& pres,
                Process::ProcessFocusManager& d);

        BaseElementContext(
                const iscore::DocumentContext& doc,
                ScenarioDocumentPresenter& pres);

        ScenarioDocumentPresenter& layerPresenter;
        Process::ProcessFocusManager& focusDispatcher;
};
}
