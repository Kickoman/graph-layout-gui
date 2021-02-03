#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include <QAbstractItemModel>
#include <QSharedPointer>
#include "graphengine.h"

class GraphModel
{
public:
    GraphModel(const QSharedPointer<GraphEngine> &graphEngine);

    QVariantList getAllNodes() const;
    QVariantList getAllLinks() const;
    int getNodeIndexByGuid(const QString &guid) const;
    double getNodePosition(int index) const;

    void recalculatePositions();

signals:
    void positionsUpdated();
    void positionUpdated(int nodeIndex);

private:
    QSharedPointer<GraphEngine> graphEngine;
};

#endif // GRAPHMODEL_H
