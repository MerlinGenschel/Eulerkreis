#include "moveCommand.h"
#include "Graph.h"

moveCommand::moveCommand(Graph* model, size_t id, QPointF pos)
    : model(model)
    , nodeId(id)
    , posNew(pos)
{
    const auto& node = model->getCoord(nodeId);
    posOld = QPointF(node.first, node.second);

    setText("Verschieben");
}

void moveCommand::undo()
{
    //qDebug()<< "Will Knoten " << nodeId << " verschieben";

    if(model)
        model->moveNodeTo(nodeId, posOld.x(), posOld.y());
    //k = nodeId;
}

void moveCommand::redo()
{
    //qDebug()<< "Will Knoten " << nodeId << " verschieben";
    if(model)
        model->moveNodeTo(nodeId, posNew.x(), posNew.y());
    //k = nodeId;
}

int moveCommand::id() const
{
    return 1;
}

bool moveCommand::mergeWith(const QUndoCommand* other)
{
    const moveCommand* command = dynamic_cast<const moveCommand*>(other);

    if(!command)
        return false;

    if(command->nodeId != nodeId)
        return false;

    posNew = command->posNew;

    return true;
}
