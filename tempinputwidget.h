#ifndef TEMPINPUTWIDGET_H
#define TEMPINPUTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class TempInputWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TempInputWidget(QWidget *parent = nullptr);

signals:
    void inputReceived(int nodes, int edges);

private slots:
    void onSubmitClicked();

private:
    QLineEdit *nodesInput;
    QLineEdit *edgesInput;
    QPushButton *submitButton;
};

#endif // TEMPINPUTWIDGET_H
