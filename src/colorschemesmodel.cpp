#include "colorschemesmodel.h"

const QHash<int, QByteArray> ColorSchemesModel::RoleNames({
    {static_cast<int>(Roles::HeaderBackgroundColor)      , ("HeaderBackgroundColor")       },
    {static_cast<int>(Roles::HeaderTextColor)            , ("HeaderTextColor")             },
    {static_cast<int>(Roles::HeaderBorderColor)          , ("HeaderBorderColor")           },
    {static_cast<int>(Roles::HeaderBorderWidth)          , ("HeaderBorderWidth")           },
    {static_cast<int>(Roles::ControlsBackgroundColor)    , ("ControlsBackgroundColor")     },
    {static_cast<int>(Roles::ControlsTextColor)          , ("ControlsTextColor")           },
    {static_cast<int>(Roles::ControlsBorderColor)        , ("ControlsBorderColor")         },
    {static_cast<int>(Roles::ControlsBorderWidth)        , ("ControlsBorderWidth")         },
    {static_cast<int>(Roles::ButtonsBackgroundColor)     , ("ButtonsBackgroundColor")      },
    {static_cast<int>(Roles::ButtonsTextColor)           , ("ButtonsTextColor")            },
    {static_cast<int>(Roles::ButtonsRadius)              , ("ButtonsRadius")               },
    {static_cast<int>(Roles::SlidersFilledColor)         , ("SlidersFilledColor")          },
    {static_cast<int>(Roles::SlidersBackgroundColor)     , ("SlidersBackgroundColor")      },
    {static_cast<int>(Roles::SlidersControlColor)        , ("SlidersControlColor")         },
    {static_cast<int>(Roles::GraphNodeBackgroundColor)   , ("GraphNodeBackgroundColor")    },
    {static_cast<int>(Roles::GraphNodeTextColor)         , ("GraphNodeTextColor")          },
    {static_cast<int>(Roles::GraphNodeBorderColor)       , ("GraphNodeBorderColor")        },
    {static_cast<int>(Roles::GraphNodeBorderWidth)       , ("GraphNodeBorderWidth")        },
    {static_cast<int>(Roles::GraphFieldBackgroundColor)  , ("GraphFieldBackgroundColor")   },
    {static_cast<int>(Roles::GraphChessDarkColor)        , ("GraphChessDarkColor")         },
    {static_cast<int>(Roles::GraphChessLightColor)       , ("GraphChessLightColor")        }
});

const QVariantMap ColorSchemesModel::DefaultColorScheme({
    {QString(RoleNames.value(static_cast<int>(Roles::HeaderBackgroundColor)))      , "#276678"},
    {QString(RoleNames.value(static_cast<int>(Roles::HeaderTextColor)))            , "#000000"},
    {QString(RoleNames.value(static_cast<int>(Roles::HeaderBorderColor)))          , "#000000"},
    {QString(RoleNames.value(static_cast<int>(Roles::HeaderBorderWidth)))          , "5"},
    {QString(RoleNames.value(static_cast<int>(Roles::ControlsBackgroundColor)))    , "#1687a7"},
    {QString(RoleNames.value(static_cast<int>(Roles::ControlsTextColor)))          , "#000000"},
    {QString(RoleNames.value(static_cast<int>(Roles::ControlsBorderColor)))        , "#000000"},
    {QString(RoleNames.value(static_cast<int>(Roles::ControlsBorderWidth)))        , "0"},
    {QString(RoleNames.value(static_cast<int>(Roles::ButtonsBackgroundColor)))     , "gray"},
    {QString(RoleNames.value(static_cast<int>(Roles::ButtonsTextColor)))           , "black"},
    {QString(RoleNames.value(static_cast<int>(Roles::ButtonsRadius)))              , "0"},
    {QString(RoleNames.value(static_cast<int>(Roles::SlidersFilledColor)))         , "dark gray"},
    {QString(RoleNames.value(static_cast<int>(Roles::SlidersBackgroundColor)))     , "gray"},
    {QString(RoleNames.value(static_cast<int>(Roles::SlidersControlColor)))        , "black"},
    {QString(RoleNames.value(static_cast<int>(Roles::GraphNodeBackgroundColor)))   , "#1687a7"},
    {QString(RoleNames.value(static_cast<int>(Roles::GraphNodeTextColor)))         , "#000000"},
    {QString(RoleNames.value(static_cast<int>(Roles::GraphNodeBorderColor)))       , "#000000"},
    {QString(RoleNames.value(static_cast<int>(Roles::GraphNodeBorderWidth)))       , "0"},
    {QString(RoleNames.value(static_cast<int>(Roles::GraphFieldBackgroundColor)))  , "#f6f5f5"},
    {QString(RoleNames.value(static_cast<int>(Roles::GraphChessDarkColor)))        , "#f6f5f5"},
    {QString(RoleNames.value(static_cast<int>(Roles::GraphChessLightColor)))       , "#d3e0ea"}
});

ColorSchemesModel::ColorSchemesModel()
{

}

int ColorSchemesModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return RoleNames.size();
}

QVariant ColorSchemesModel::data(const QModelIndex &index, int role) const
{
    if (index.isValid())
    {
        auto key = RoleNames.value(role, "undefined");
        return colorScheme.value(key, DefaultColorScheme.value(key));
    }
    return {};
}

QHash<int, QByteArray> ColorSchemesModel::roleNames() const
{
    return RoleNames;
}

QString ColorSchemesModel::RoleToString(ColorSchemesModel::Roles role)
{
    return RoleNames.value(static_cast<int>(role), "Undefined");
}

ColorSchemesModel::Roles ColorSchemesModel::StringToRole(const QString &role)
{
    const auto values = RoleNames.values();
    for (const auto &value : values)
        if (QString(value).compare(role) == 0)
            return static_cast<Roles>(RoleNames.key(value));
    return Roles::Undefined;
}
