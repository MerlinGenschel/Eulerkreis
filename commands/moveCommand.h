#ifndef MOVECOMMAND_H
#define MOVECOMMAND_H

#include<QUndoCommand>
#include<QPointer>
#include<QPointF>

class Graph;
class paint;

class moveCommand : public QUndoCommand
{
    QPointer<Graph> model;
    size_t nodeId;
    QPointF posNew;
    QPointF posOld;
public:
    moveCommand(Graph* modell, size_t id, QPointF pos);

    void undo() override;
    void redo() override;
    int id() const override;
    bool mergeWith(const QUndoCommand* other) override;
};

#endif // MOVE_H
