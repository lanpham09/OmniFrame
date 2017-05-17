#include "GraphicsView3D.h"

GraphicsView3D::GraphicsView3D(QWidget *parent ):QGraphicsView(parent)
{
    setWindowTitle(tr("3D Model Viewer"));

    this->setViewport( new QGLWidget( QGLFormat(QGL::SampleBuffers) ) );
    //this->setupViewport( thisGLWidget );
    this->setViewportUpdateMode( QGraphicsView::FullViewportUpdate );

}

void GraphicsView3D::resizeEvent(QResizeEvent *event){
    if (scene())
        scene()->setSceneRect( QRect(QPoint(0, 0), event->size()) );
    QGraphicsView::resizeEvent(event);
}

void GraphicsView3D::setSene( QGraphicsScene* thisSene )
{
    this->setScene( thisSene );
    this->show();
    resize(1024,768);
}
