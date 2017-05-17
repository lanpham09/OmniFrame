#include "mainwindow.h"
#include "ui_mainwindow.h"



#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    arduinoPos(0),
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    T0 = arduinoPos.T0;
    T1 = arduinoPos.T1;
    T2 = arduinoPos.T2;
    T3 = arduinoPos.T3;

    grapicSene = new OmnimagnetFrameScene(T0, T2, T3);
    ui->graphicsView->setScene( grapicSene );

    connect( &updateTimer, SIGNAL(timeout()), this, SLOT(update()) );
    connect( ui->button_startUSB, SIGNAL(clicked()), this, SLOT(sendUSBStart()) );
    connect( ui->button_stopUSB, SIGNAL(clicked()), this, SLOT(sendUSBStop() ) );
    updateTimer.start( 100 );

}

MainWindow::~MainWindow()
{
    updateTimer.stop();
    delete ui;
}

void MainWindow::sendUSBStart()
{
    arduinoPos.sendStart();
}

void MainWindow::sendUSBStop()
{
    arduinoPos.sendStop();
}

void MainWindow::update()
{
    ui->spinBox_T1->setValue( T0->theta().value(DEG) );
    ui->spinBox_D2->setValue( T1->d().value(MILLIMETER) );
    ui->spinBox_D3->setValue( T2->d().value(MILLIMETER) );
    ui->spinBox_T4->setValue( T3->theta().value(DEG));
}

void MainWindow::setT0(int value)
{
    T0->theta( value*M_PI/180.0 );
}

void MainWindow::setD1(int value)
{
    T1->d(Math::Distance(value*.95+45,MILLIMETER));
}

void MainWindow::setD2(int value)
{
    T2->d(Math::Distance(value*.7+310,MILLIMETER));
}

void MainWindow::setT3(int value)
{
    T3->theta(value*M_PI/180.0);
}
