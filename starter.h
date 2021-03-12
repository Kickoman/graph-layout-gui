#ifndef STARTER_H
#define STARTER_H

#include <QObject>
#include "igraph.h"
#include "graphlayout.h"

class Starter : public QObject
{
    Q_OBJECT
public:
    explicit Starter(uint seed = 0);
    ~Starter() override;

    void start();


private:
    const uint seed = 0;
    IGraph *graph = nullptr;
    GraphLayout *layout = nullptr;
};

#endif // STARTER_H
