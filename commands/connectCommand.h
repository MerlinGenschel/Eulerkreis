#ifndef CONNECTCOMMAND_H
#define CONNECTCOMMAND_H

#include<QUndoCommand>
#include<QPointer>
#include<QPointF>

class Graph;
class paint;

class connectCommand : public QUndoCommand
{
    QPointer<Graph> model;
    int src;
    int dest;

public:
    connectCommand(Graph* model, int src, int dest);

    void undo() override;
    void redo() override;
};

#endif // CONNECTCOMMAND_H
