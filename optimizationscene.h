#ifndef OPTIMIZATIONSCENE_H
#define OPTIMIZATIONSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>

class OptimizationScene: public QGraphicsScene
{
    Q_OBJECT

public:
    explicit OptimizationScene(QObject *parent = nullptr) : QGraphicsScene(parent) {};
    ~OptimizationScene() override {};

signals:
    void sceneClicked(QPointF point);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // OPTIMIZATIONSCENE_H
