#ifndef REMOVENODECOMMAND_H
#define REMOVENODECOMMAND_H

#include<QUndoCommand>
#include<QPointer>
#include<QPointF>

class Graph;

class removeNodeCommand : public QUndoCommand
{
    QPointer<Graph> model;
    QPointF pos;
    std::size_t id;
public:
    removeNodeCommand(Graph* model, std::size_t id);

    void undo() override;
    void redo() override;
};

#endif // REMOVENODECOMMAND_H
