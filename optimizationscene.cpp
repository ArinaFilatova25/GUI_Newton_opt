#include "optimizationscene.h"

void OptimizationScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    emit sceneClicked(event->scenePos());
}
