#pragma once

#include <core/presenter/command/Command.hpp>
#include <QApplication>

class ClientNameChangedCommand : public iscore::Command
{
		// QUndoCommand interface
	public:
		ClientNameChangedCommand(QString oldval, QString newval):
			Command{QString(""),
					QString(""),
					QString("")},
			m_oldval{oldval},
			m_newval{newval}
		{

		}

		virtual bool mergeWith(const QUndoCommand *other) override
		{
			auto cmd = static_cast<const ClientNameChangedCommand*>(other);
			m_newval = cmd->m_newval;
			return true;
		}

		virtual void undo() override
		{
			auto target = qApp->findChild<NetworkSettingsModel*>("NetworkSettingsModel");
			target->setClientName(m_oldval);
		}

		virtual void redo() override
		{
			auto target = qApp->findChild<NetworkSettingsModel*>("NetworkSettingsModel");
			target->setClientName(m_newval);
		}

		virtual void deserialize(QByteArray) override
		{
		}

	private:
		QString m_oldval;
		QString m_newval;
};
