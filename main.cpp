#include <QGuiApplication>
#include <QQuickView>
#include <QMessageBox>
#include <QQmlError>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::ApplicationAttribute::AA_EnableHighDpiScaling);
    QCoreApplication::setApplicationName("Graph lab");

    QGuiApplication a(argc, argv);
    QQuickView view;
    view.setSource(QUrl("qrc:/qml/main.qml"));
    if (view.status() == QQuickView::Status::Error)
    {
        auto errors = view.errors();
        QString errorsString;
        for (const auto &error : qAsConst(errors))
            errorsString.append(QString("%1\n").arg(error.toString()));
        QMessageBox::critical(nullptr,
                              "Critical error",
                              "Can't start view. Errors:\n" + errorsString);
        return -1;
    }
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    view.show();
    return a.exec();
}
