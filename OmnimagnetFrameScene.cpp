#include "OmnimagnetFrameScene.h"

#include <iostream>
using namespace std;

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

QDialog *OmnimagnetFrameScene::createDialog(const QString &windowTitle) const
{
    QDialog *dialog = new QDialog(0, Qt::CustomizeWindowHint | Qt::WindowTitleHint);

    dialog->setWindowOpacity(0.8);
    dialog->setWindowTitle(windowTitle);
    dialog->setLayout(new QVBoxLayout);

    return dialog;
}


OmnimagnetFrameScene::OmnimagnetFrameScene( Math::HomogeneousTransform* T1, Math::HomogeneousTransform* T2, Math::HomogeneousTransform* T3 )
    : m_wireframeEnabled(false)
    , m_normalsEnabled(false)
    , m_backgroundColor(0, 170, 255)
    , modelAssembly(0)
    , m_lastTime(0)
    , m_distance(1.4f)
{
    QWidget *instructions = createDialog(tr("Instructions"));
    instructions->layout()->addWidget(new QLabel(tr("Use mouse wheel to zoom model, and click and drag to rotate model")));
    instructions->layout()->addWidget(new QLabel(tr("Move the sun around to change the light position")));

    addWidget(instructions);

    QPointF pos(10, 10);
    foreach (QGraphicsItem *item, items()) {
        item->setFlag(QGraphicsItem::ItemIsMovable);
        item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

        const QRectF rect = item->boundingRect();
        item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
        pos += QPointF(0, 10 + rect.height());
    }

    QRadialGradient gradient(40, 40, 40, 40, 40);
    gradient.setColorAt(0.2, Qt::yellow);
    gradient.setColorAt(1, Qt::transparent);

    m_lightItem = new QGraphicsRectItem(0, 0, 80, 80);
    m_lightItem->setPen(Qt::NoPen);
    m_lightItem->setBrush(gradient);
    m_lightItem->setFlag(QGraphicsItem::ItemIsMovable);
    m_lightItem->setPos(1279, -9);
    addItem(m_lightItem);

    // Load Models
    // modelList.push_back(new Model("Solidworks Models/40-4040 - 4.obj"));
    // transformList.push_back(new Math::HomogeneousTransform(Math::Orientation(Math::cPI/2.0,Math::Vector(1,0,0),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME), Math::Displacement(30,0,0,Math::UNDEFINED_FRAME,CENTIMETER)));

    modelList.push_back( bAssy );
    transformList.push_back(new Math::HomogeneousTransform(Math::Orientation(0,Math::Vector(1,0,0),Math::UNDEFINED_FRAME,Math::UNDEFINED_FRAME), Math::Displacement(0,0,0,Math::UNDEFINED_FRAME,METER)));

    modelList.push_back( vAssy );
    transformList.push_back( T1 );

    modelList.push_back( hAssy );
    transformList.push_back( T2 );

    modelList.push_back( oAssy );
    transformList.push_back( T3 );



    modelAssembly = new Assembly(modelList,transformList);

    lastOrient = Math::Orientation(-M_PI/2.0,Math::Vector(1,0,0))*Math::Orientation(M_PI/3.0,Math::Vector(0,0,1))*Math::Orientation(-M_PI/20.0,Math::Vector(-1,1,0));

    m_time.start();

}

void OmnimagnetFrameScene::drawBackground(QPainter *painter, const QRectF &)
{

    //cout << painter->paintEngine()->type() << " " << QPaintEngine::OpenGL2<< endl;
    if (painter->paintEngine()->type() != QPaintEngine::OpenGL &&
            painter->paintEngine()->type() != QPaintEngine::OpenGL2) {
        qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
        return;
    }

    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // setup Projection
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(70, width() / height(), 0.01, 1000);


    // Setup Lighting Location
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    const float pos[] = { m_lightItem->x() - width() / 2, height() / 2 - m_lightItem->y(), 512, 0 };
    //cout << m_lightItem->x() << " " << m_lightItem->y() << endl;
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    //glColor4f(m_modelColor.redF(), m_modelColor.greenF(), m_modelColor.blueF(), 1.0f);
    glPopMatrix();


    lastOrient = lastOrient*Math::Orientation(m_rotation.norm(), m_rotation, Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME);
    Math::Displacement newDisp(0,-.25, -m_distance, Math::UNDEFINED_FRAME);

    modelAssembly->placeObject( Math::HomogeneousTransform(lastOrient, newDisp ) );

//    cout << Math::HomogeneousTransform(lastOrient, newDisp ) << endl;

    m_rotation = Math::Zero();


    modelAssembly->render();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    QTimer::singleShot(20, this, SLOT(update()));
}




void OmnimagnetFrameScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
    if (event->isAccepted())
        return;
    if (event->buttons() & Qt::LeftButton) {
        const QPointF delta = event->scenePos() - event->lastScenePos();
        const Math::Vector angularImpulse = Math::Vector(delta.y(), delta.x(), 0) * 0.01;

        m_rotation += angularImpulse;

        event->accept();
        update();
    }
}

void OmnimagnetFrameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
    if (event->isAccepted())
        return;

    m_mouseEventTime = m_time.elapsed();
    //m_angularMomentum = m_accumulatedMomentum = Point3d();
    event->accept();
}

void OmnimagnetFrameScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    if (event->isAccepted())
        return;

    event->accept();
    update();
}

void OmnimagnetFrameScene::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    QGraphicsScene::wheelEvent(event);
    if (event->isAccepted())
        return;

    m_distance += event->delta() / 500.0;//qPow(1.2, -event->delta() / 120);
    event->accept();
    update();
}

