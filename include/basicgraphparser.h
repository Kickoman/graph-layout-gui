#ifndef BASICGRAPHPARSER_H
#define BASICGRAPHPARSER_H

#include "igraph.h"
#include <memory>
#include <QString>

class BasicGraphParser
{
public:
    static bool parseGraph(QString description, PositionedGraph **res);
};

#endif // BASICGRAPHPARSER_H
