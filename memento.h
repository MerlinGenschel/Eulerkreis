#ifndef MEMENTO_H
#define MEMENTO_H

#include <Graph.h>

class memento
{
    friend class Graph;

    std::vector<Graph> zustand;

    memento();
public:
    ~memento() = default;
};

#endif // MEMENTO_H
