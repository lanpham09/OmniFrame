#ifndef OMNIMAGNETFRAMESCENE_H
#define OMNIMAGNETFRAMESCENE_H

#include <QtGui>
#include <QtOpenGL>
#include <GL/glu.h>

#include <QGraphicsScene>
#include <QLabel>
#include <QTime>


#include "OpenGL_Object.h"
#include "model.h"
#include "Assembly.h"

#include "baseAssy.h"
#include "virticalSupportAssy.h"
#include "horizontalSupportAssy.h"
#include "omnimagnetAssy.h"


#include "Utilities/Math.h"
#include "point3d.h"

class OmnimagnetFrameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    OmnimagnetFrameScene(Math::HomogeneousTransform* T1 = 0, Math::HomogeneousTransform* T2 = 0, Math::HomogeneousTransform* T3 = 0 );

    void drawBackground(QPainter *painter, const QRectF &rect);


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent * wheelEvent);

private:
    QDialog *createDialog(const QString &windowTitle) const;

    void setModel(Model *model);

    bool m_wireframeEnabled;
    bool m_normalsEnabled;

    QColor m_backgroundColor;

    std::vector<OpenGL_Object* > modelList;
    std::vector<Math::HomogeneousTransform* > transformList;
    Assembly* modelAssembly;

    virticalSupportAssy vAssy;
    horizontalSupportAssy hAssy;
    omnimagnetAssy oAssy;
    baseAssy bAssy;

    QTime m_time;
    int m_lastTime;
    int m_mouseEventTime;

    float m_distance;
    Math::Orientation lastOrient;
    Math::Vector m_rotation;

    QGraphicsRectItem *m_lightItem;
};

#endif // OMNIMAGNETFRAMESCENE_H
