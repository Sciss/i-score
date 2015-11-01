#include "Cut.hpp"

using namespace DeviceExplorer::Command;

Cut::Cut(const iscore::NodePath &parentPath, int row,
                              const QString& text,
                              Path<DeviceExplorerModel> &&model):
    iscore::SerializableCommand{factoryName(),
                                commandName(),
                                description()}
{
    m_model = model;
    m_parentPath = parentPath;
    m_row = row;

    setText(text);
}


void
Cut::undo() const
{
    auto& model = m_model.find();

    QModelIndex parentIndex = model.convertPathToIndex(m_parentPath);

    QModelIndex index = parentIndex.child(m_row, 0);

    DeviceExplorer::Result result;

    if(index.isValid())
    {
        result = model.pasteBefore_aux(index);
    }
    else
    {
        //we undo a cut of the previous last child
        index = parentIndex.child(m_row - 1, 0);
        if(!index.isValid())
        {
            index = parentIndex;
        }
        ISCORE_ASSERT(index.isValid());
        result = model.pasteAfter_aux(index);
    }

    model.setCachedResult(result);
}

void
Cut::redo() const
{
    auto& model = m_model.find();
    QModelIndex parentIndex = model.convertPathToIndex(m_parentPath);

    QModelIndex index = parentIndex.child(m_row, 0);
    const DeviceExplorer::Result result = model.cut_aux(index);
    model.setCachedResult(result);

}

void
Cut::serializeImpl(QDataStream& d) const
{
    d << m_model << m_parentPath;
    d << (qint32) m_row;

    d << (qint32) m_data.size();
    d.writeRawData(m_data.data(), m_data.size());

}

void
Cut::deserializeImpl(QDataStream& d)
{
    d >> m_model >> m_parentPath;
    qint32 v;
    d >> v;
    m_row = v;

    d >> v;
    int size = v;
    m_data.resize(size);
    d.readRawData(m_data.data(), size);
}