#ifndef GRAPHLINEPROXYMODEL_H
#define GRAPHLINEPROXYMODEL_H

#include <QAbstractListModel>
#include "graphlayout.h"

class GraphLineProxyModel : public QAbstractListModel
{
public:
    enum class Roles : int
    {
        StartXPosition = Qt::UserRole + 1,
        StartYPosition,
        FinishXPosition,
        FinishYPosition,
        StartNodeIndex,
        FinishNodeIndex
    };

    GraphLineProxyModel(GraphLayout *parentModel);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

private slots:
    void onModelUpdated();
    void onPositionUpdated(int index);

private:
    GraphLayout *parentModel;
};

#endif // GRAPHLINEPROXYMODEL_H
