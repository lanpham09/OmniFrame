#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "OmnimagnetFrameScene.h"

#include "Utilities/Math.h"
#include "ArduinoUSBInterface.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setT0(int value);
    void setD1(int value);
    void setD2(int value);
    void setT3(int value);
    void update();
    void sendUSBStart();
    void sendUSBStop();
    
private:
    Ui::MainWindow *ui;
    OmnimagnetFrameScene* grapicSene;

    ArduinoUSBInterface arduinoPos;

    Math::DH_Transform* T0;
    Math::DH_Transform* T1;
    Math::DH_Transform* T2;
    Math::DH_Transform* T3;

    QTimer updateTimer;
};

#endif // MAINWINDOW_H
