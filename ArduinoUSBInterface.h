#ifndef ARDUINOUSBINTERFACE_H
#define ARDUINOUSBINTERFACE_H

// Requires LibSerial

#include <SerialStream.h>
#include <string>

#include "Utilities/Math.h"
#include "Utilities/Units.h"
#include "Utilities/Timer.h"
#include "Utilities/Thread.h"
#include "Utilities/utilities.h"

class ArduinoUSBInterface: public Thread
{

    //SerialPort* serial_port;

    static const unsigned int BUFFER_SIZE = 256;
    char serialBuffer[BUFFER_SIZE];

    bool portOpen;

    //static constexpr double ratio = .9;

    double T0_offset;
    double D1_offset;
    double D2_offset;
    double T3_offset;

protected:
    void run();

public:
    ArduinoUSBInterface( int deviceNumber );
    ~ArduinoUSBInterface();
    bool isOpen() const;

    Math::DH_Transform* T0;
    Math::DH_Transform* T1;
    Math::DH_Transform* T2;
    Math::DH_Transform* T3;

    void sendStart();
    void sendStop();



};

#endif // ARDUINOUSBINTERFACE_H
