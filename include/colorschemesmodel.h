#ifndef COLORSCHEMESMODEL_H
#define COLORSCHEMESMODEL_H

#include <QAbstractListModel>

class ColorSchemesModel : public QAbstractListModel
{
public:

    enum class Roles : int
    {
        HeaderBackgroundColor = Qt::UserRole + 1,
        HeaderTextColor,
        HeaderBorderColor,
        HeaderBorderWidth,

        ControlsBackgroundColor,
        ControlsTextColor,
        ControlsBorderColor,
        ControlsBorderWidth,

        ButtonsBackgroundColor,
        ButtonsTextColor,
        ButtonsRadius,

        SlidersFilledColor,
        SlidersBackgroundColor,
        SlidersControlColor,

        GraphNodeBackgroundColor,
        GraphNodeTextColor,
        GraphNodeBorderColor,
        GraphNodeBorderWidth,

        GraphFieldBackgroundColor,
        GraphChessDarkColor,
        GraphChessLightColor,

        Undefined
    };

    ColorSchemesModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;
private:
    static const QHash<int, QByteArray> RoleNames;
    static const QVariantMap DefaultColorScheme;
    static QString RoleToString(Roles role);
    static Roles StringToRole(const QString &role);

    QVariantMap colorScheme;
};

#endif // COLORSCHEMESMODEL_H
