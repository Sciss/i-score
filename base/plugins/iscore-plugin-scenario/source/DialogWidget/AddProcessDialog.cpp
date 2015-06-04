#include "AddProcessDialog.hpp"

#include "ProcessInterface/ProcessList.hpp"

#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QInputDialog>

AddProcessDialog::AddProcessDialog(QWidget *parent) :
    QWidget {parent}
{
    QHBoxLayout* addAutomLayout = new QHBoxLayout;
    addAutomLayout->setContentsMargins(0, 0, 0 , 0);
    this->setLayout(addAutomLayout);

    // Button
    QToolButton* addAutomButton = new QToolButton;
    addAutomButton->setText("+");
    addAutomButton->setObjectName("addAutom");

    // Text
    auto addAutomText = new QLabel("Add Process");
    addAutomText->setStyleSheet(QString("text-align : left;"));

    addAutomLayout->addWidget(addAutomButton);
    addAutomLayout->addWidget(addAutomText);

    connect(addAutomButton, &QToolButton::pressed,
    [ = ]()  // Lambda to create a process.
    {
        bool ok = false;
        auto process_list = ProcessList::getProcessesName();
        auto process_name = QInputDialog::getItem(this,
        tr("Choose a process"),
        tr("Choose a process"),
        process_list,
        0,
        false,
        &ok);

        if(ok)
        {
            emit okPressed(process_name);
        }
        addAutomButton->setDown(false);
    });
}