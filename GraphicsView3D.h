#ifndef GRAPHICSVIEW3D_H
#define GRAPHICSVIEW3D_H

#include <QGraphicsView>
#include <QResizeEvent>
#include <QPoint>
#include <QRect>
#include <QGLWidget>
#include "openglscene.h"
#include <QGLFormat>

class GraphicsView3D : public QGraphicsView
{

public:
    GraphicsView3D(QWidget *parent =0);
    void resizeEvent(QResizeEvent *event) ;
    void setSene( QGraphicsScene* thisSene );
};

#endif // GRAPHICSVIEW3D_H
