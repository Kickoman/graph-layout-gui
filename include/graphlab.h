#ifndef GRAPHLAB_H
#define GRAPHLAB_H

#include <QObject>
#include <memory>
#include "graphlayout.h"

class GraphKeeper;

class GraphLab : public QObject
{
    Q_OBJECT

    Q_PROPERTY(GraphLayout* graphLayout READ getGraphLayout NOTIFY layoutReady)
public:
    explicit GraphLab(QObject *parent = nullptr);

    // Interface to QML
    Q_INVOKABLE
    void generateGraph(int nodes, int edges);

    Q_INVOKABLE
    void setGraph(const QString &graphDescription);

    Q_INVOKABLE
    GraphLayout *getGraphLayout() const;

signals:
    void layoutReady();

private:
    GraphLayout *graphLayout = nullptr;
    std::shared_ptr<GraphKeeper> graphKeeper;
};

#endif // GRAPHLAB_H
