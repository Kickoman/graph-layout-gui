#include "tempinputwidget.h"

#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QIntValidator>
#include <QMessageBox>

TempInputWidget::TempInputWidget(QWidget *parent) : QWidget(parent)
{
    auto *layout = new QFormLayout();

    nodesInput = new QLineEdit("5", this);
    edgesInput = new QLineEdit("10", this);

    nodesInput->setValidator(new QIntValidator(1, 200, this));
    edgesInput->setValidator(new QIntValidator(0, 200*(200-1)/2, this));

    layout->addRow("Nodes count", nodesInput);
    layout->addRow("Edges count", edgesInput);

    submitButton = new QPushButton("Submit", this);
    connect(submitButton, &QPushButton::clicked, this, &TempInputWidget::onSubmitClicked);
    layout->addWidget(submitButton);

    this->setLayout(layout);
}

void TempInputWidget::onSubmitClicked()
{
    if (nodesInput->hasAcceptableInput() && edgesInput->hasAcceptableInput())
    {
        int nodesCount = nodesInput->text().toInt();
        int edgesCount = nodesInput->text().toInt();
        emit inputReceived(nodesCount, edgesCount);
    }
    else
        QMessageBox::critical(this, "Incorrect input",
                              "Your values are incorrect, my dude");
}
