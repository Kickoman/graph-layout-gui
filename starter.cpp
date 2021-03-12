#include "starter.h"
#include "randomgraphexample.h"
#include "tempinputwidget.h"
#include <QQuickView>
#include <QQmlError>
#include <QQmlContext>
#include <QMessageBox>

Starter::Starter(uint seed) : QObject(nullptr), seed(seed)
{

}

Starter::~Starter()
{

}

void Starter::start()
{
//    input->showFullScreen();

    auto *quickView = new QQuickView();
    quickView->showMaximized();
    auto *input = new TempInputWidget();
    input->show();
    input->activateWindow();
    quickView->setVisibility(QWindow::Visibility::Hidden);
//    quickView->hide();

//    connect(quickView, &QQuickView::windowStateChanged, input,
//            [&input](Qt::WindowState state){
//        if (state == Qt::WindowState::WindowActive)
//            input->hide();
//    });

    connect(input, &TempInputWidget::inputReceived, input,
            [this, input, quickView](int nodes, int edges){
        this->graph = new RandomGraphExample(nodes, edges, this->seed);
        this->layout = new GraphLayout(this->graph);

//        quickView->showMaximized()
        input->hide();
        quickView->setVisibility(QWindow::Visibility::FullScreen);
        quickView->rootContext()->setContextProperty("graphModel", this->layout);
        quickView->setSource(QUrl("qrc:/qml/main.qml"));
        if (quickView->status() == QQuickView::Status::Error)
        {
            auto errors = quickView->errors();
            QString errorsString;
            for (const auto &error : qAsConst(errors))
                errorsString.append(QString("%1\n").arg(error.toString()));
            QMessageBox::critical(nullptr,
                                  "Critical error",
                                  "Can't start view. Errors:\n" + errorsString);
            exit(-1);
        }
        quickView->setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
//        quickView->showMaximized();
        quickView->requestUpdate();
        input->deleteLater();
    });
//    emit input->inputReceived(5, 10);
}
