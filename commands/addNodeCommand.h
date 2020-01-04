#ifndef ADDNODECOMMAND_H
#define ADDNODECOMMAND_H

#include<QUndoCommand>
#include<QPointer>
#include<QPointF>

class Graph;

class addNodeCommand : public QUndoCommand
{
    QPointer<Graph> model;
    QPointF pos;
    int id;
public:
    addNodeCommand(Graph* model, QPointF pos);

    void undo() override;
    void redo() override;
};

#endif // ADDNODECOMMAND_H
