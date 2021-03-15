#ifndef BASICGRAPHPARSER_H
#define BASICGRAPHPARSER_H

#include "igraph.h"
#include <memory>

class BasicGraphParser
{
public:
    static bool parseGraph(QString description, IGraph **res);
};

#endif // BASICGRAPHPARSER_H
