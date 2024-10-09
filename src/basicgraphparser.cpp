#include "basicgraphparser.h"
#include "basicgraph.h"
#include <QTextStream>
#include <QIODevice>


bool BasicGraphParser::parseGraph(QString description, Graph &res)
{
    QTextStream str(&description, QIODevice::ReadOnly);
    int nodesCount = 0;
    int edgesCount = 0;
    str >> nodesCount >> edgesCount;

    res.setNodesCount(nodesCount);

    for (int i = 0; i < edgesCount; ++i)
    {
        int a, b;
        str >> a >> b;
        --a;
        --b;
        res.connectNodes(a, b);
    }

    int values = 0;
    str >> values;

    for (int i = 0; i < values; ++i)
    {
        int index = 0;
        QString value;
        str >> index >> value;
        res.setNodeValue(index - 1, value);
    }
    return true;
}
