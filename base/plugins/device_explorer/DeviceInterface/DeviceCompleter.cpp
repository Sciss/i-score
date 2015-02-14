#include "DeviceCompleter.hpp"
#include "../Panel/DeviceExplorerModel.hpp"

#include <QApplication>
/*
void recursivelyGetAddresses(const DeviceExplorerModel& explorer,
							 QModelIndex index,
							 QString currentAddress,
							 QStringList& list)
{
	for(int i = 0; i < explorer.rowCount(index); i++)
	{
		auto nodeIndex = index.child(i, explorer.getNameColumn());
		QString nodeName = explorer.data(nodeIndex, explorer.getNameColumn()).toString();

		QString nodeAddress = currentAddress + "/" + nodeName;
		list << nodeAddress;

		recursivelyGetAddresses(explorer, nodeIndex, nodeAddress, list);
	}
}

QStringList getAddresses(QString device)
{
	QStringList s;
	auto treemodel =
			qApp->findChild<DeviceExplorerModel*>("DeviceExplorerModel");


	for(int i = 0; i < treemodel->rowCount(QModelIndex()); i++)
	{
		auto deviceIndex = treemodel->index(i,
											treemodel->getNameColumn(),
											QModelIndex());

		if(treemodel->isDevice(deviceIndex))
		{
			QString devicestr = treemodel->data(deviceIndex, treemodel->getNameColumn()).toString();
			if(devicestr == device)
			{
				recursivelyGetAddresses(*treemodel,
										deviceIndex,
										QString{"/%1"}.arg(device),
										s);

			}
		}
	}

	return s;
}
*/

DeviceCompleter::DeviceCompleter(DeviceExplorerModel* treemodel,
								 QObject* parent):
	QCompleter{parent}
{
	setModel(treemodel);

	setCompletionColumn(0);
	setCompletionRole(Qt::DisplayRole);
	setCaseSensitivity(Qt::CaseInsensitive);
}

QString DeviceCompleter::pathFromIndex(const QModelIndex& index) const
{
	QString path;

	QModelIndex iter = index;

	while(iter.isValid())
	{
		path = QString{"%1/"}.arg(iter.data(0).toString()) + path;
		iter = iter.parent();
	}

	return "/" + path.remove(path.length() - 1, 1);
}

QStringList DeviceCompleter::splitPath(const QString& path) const
{
	QString p2 = path;
	if(p2.at(0) == QChar('/'))
	{
		p2.remove(0, 1);
	}

	return p2.split("/");
}
/*

#include <QMenu>
#include "../Panel/Node.hpp"
QMenu* nodeToQMenu(const Node* n)
{
	QMenu* menu = new QMenu{n->name()};

	for(const Node* child : n->children())
	{
		if(child->hasChildren())
			menu->addMenu(nodeToQMenu(child));
		else
			menu->addAction(child->name());
	}

	return menu;
}


QMenu* rootNodeToQMenu()
{
	auto treemodel =
			qApp->findChild<DeviceExplorerModel*>("DeviceExplorerModel");
	if(treemodel->rootNode())
	{
		auto menu = nodeToQMenu(treemodel->rootNode());
		menu->setTitle(QObject::tr("Devices"));
		return menu;
	}

	return new QMenu{QObject::tr("No device")};
}
*/