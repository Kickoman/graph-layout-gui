#ifndef GRAPHLAB_H
#define GRAPHLAB_H

#include <QObject>
#include "igraph.h"
#include "graphlayout.h"

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
    IGraph *graph = nullptr;
    GraphLayout *graphLayout = nullptr;
};

#endif // GRAPHLAB_H
