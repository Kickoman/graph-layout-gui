#include "basicgraphparser.h"
#include "basicgraph.h"
#include <QTextStream>

bool BasicGraphParser::parseGraph(QString description, PositionedGraph **res)
{
    QTextStream str(&description, QIODevice::ReadOnly);
    int nodesCount = 0;
    int edgesCount = 0;
    str >> nodesCount >> edgesCount;

    auto *graph = new BasicGraph();
    *res = graph;

    graph->setNodesCount(nodesCount);

    for (int i = 0; i < edgesCount; ++i)
    {
        int a, b;
        str >> a >> b;
        --a;
        --b;
        graph->connectNodes(a, b);
    }

    int values = 0;
    str >> values;

    for (int i = 0; i < values; ++i)
    {
        int index = 0;
        QString value;
        str >> index >> value;
        graph->setNodeValue(index - 1, value);
    }
    return true;
}
