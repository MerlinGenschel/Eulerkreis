#include "connectCommand.h"
#include "Graph.h"

connectCommand::connectCommand(Graph* model, size_t src, size_t dest)
     : model(model)
     , src (src)
     , dest (dest)
{

}

void connectCommand::undo()
{
    if(model)
        model->addEdge(src, dest);
}

void connectCommand::redo()
{
    if(model)
        model->addEdge(src, dest);

}
