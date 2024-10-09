#ifndef BASICGRAPHPARSER_H
#define BASICGRAPHPARSER_H

#include <QString>

class Graph;

class BasicGraphParser
{
public:
    static bool parseGraph(QString description, Graph &res);
};

#endif // BASICGRAPHPARSER_H
