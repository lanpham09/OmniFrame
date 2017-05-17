#include "ArduinoUSBInterface.h"

#include <iostream>
#include <sstream>
#include <fstream>

ArduinoUSBInterface::ArduinoUSBInterface( int deviceNumber ):
    T0_offset(M_PI/2.0),
    D1_offset(45),
    D2_offset(200),
    T3_offset(0)
{

    string serialFileName = "/dev/ttyACM";
    string desiredName( "Name: " + to_string<int>(deviceNumber) );

    bool deviceFound = false;
    int deviceNum = 0;
    while( !deviceFound && deviceNum < 10 )
    {
        string deviceFileName( serialFileName + to_string<int>(deviceNum));
        std::fstream fs;
        fs.open(deviceFileName.c_str());
        if( fs.is_open() )
        {
            fs.close();

            serial_port = new SerialPort( deviceFileName, SerialPort::B_9600);
            //serial_port = new SerialPort( deviceFileName);
            //serial_port->Open(SerialPort::BAUD_9600, SerialPort::CHAR_SIZE_8, SerialPort::PARITY_DEFAULT, SerialPort::STOP_BITS_1, SerialPort::FLOW_CONTROL_HARD);

            const unsigned char data = 'N';

            string deviceName;
            serial_port->writeByte(data);
            deviceName = serial_port->getLine('\n');

            /*bool responded = false;
            int tries = 0;
            while( !responded && tries < 5 )
            {

                serial_port->WriteByte(data);
                try
                {

                    deviceName = serial_port->ReadLine(200,'\n');
                    deviceName.erase(deviceName.end()-1,deviceName.end()); // remove the \n from the end of the string

                    responded = true;
                } catch (SerialPort::ReadTimeout e)
                {
                    responded = false;
                }
                tries ++;
            }*/


            if( deviceName == desiredName )
            {
                deviceFound = true;
            } else {
                serial_port->closePort();
                //serial_port->Close();
            }

        }
        deviceNum ++;
    }

    if( deviceNum == 10 )
    {
        cout << "Arduino Device " << deviceNumber << " not found!" << endl;
        exit(0);
    }



    int tryNumber = 0;
    while( !serial_port->isOpen() && tryNumber < 100)
    {
        tryNumber ++;
        if( serial_port )
            delete serial_port;

        serialFileName = "/dev/ttyACM"+to_string<int>(tryNumber);

        serial_port= new SerialPort( serialFileName, SerialPort::B_9600);

        //serial_port= new SerialPort( serialFileName );
        //serial_port->Open(SerialPort::BAUD_9600);

    }


    T0 = new Math::DH_Transform(Math::Distance(0,INCH),     Math::Distance(0,INCH),     M_PI, 0, Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME, 0);
    T1 = new Math::DH_Transform(Math::Distance(0,INCH),     Math::Distance(0,INCH),        0, 0, Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME, T0);
    T2 = new Math::DH_Transform(Math::Distance(2.5,INCH),   Math::Distance(0,INCH), M_PI/2.0, 0, Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME, T1);
    T3 = new Math::DH_Transform(Math::Distance(0,INCH),     Math::Distance(0,INCH),-M_PI/2.0, 0, Math::UNDEFINED_FRAME, Math::UNDEFINED_FRAME, T2);

    start();
    sendStart();

}


ArduinoUSBInterface::~ArduinoUSBInterface()
{
    this->stop();

    // Have it Stop Sending Data
    serial_port->writeByte('X');

    delete T3;
    delete T2;
    delete T1;
    delete T0;

    serial_port->closePort();
    delete serial_port;
    // delete positionLowPassFilter;

}

void ArduinoUSBInterface::run( )
{
    while( isRunning() && serial_port && serial_port->isOpen() )
    {
        if( serial_port->isDataAvailable() )
        {
            //serial_port->Read(serialBuffer, BUFFER_SIZE);
            string line = serial_port->getLine('\n');
            //cout << "Response: " << line << " \t got: " << line.size() << endl;//serial_port->getline(serialBuffer,BUFFER_SIZE,'\n');
            if( line.size() > 3 )
            {
                std::stringstream inputStream(line);
                double val;

                inputStream >> val;
                T0->theta( val + T0_offset );
                //cout << "-- " << T0->theta()<< "\t";

                inputStream >> val;
                T1->d( Math::Distance(val+ D1_offset, MILLIMETER) );
                // cout << T1->d() << "\t";

                inputStream >> val;
                T2->d( Math::Distance(val+ D2_offset, MILLIMETER) );
                // cout << T2->d() << "\t";

                inputStream >> val;
                T3->theta( val + T3_offset );
                // cout << T3->theta() << "\n";

            }
            // serial_port->flush();
            //memset(serialBuffer,0,BUFFER_SIZE);

        } else {
            Timing::Timer::wait(10);
        }

    }
    return ;
}

bool ArduinoUSBInterface::isOpen() const
{
    return serial_port->isOpen();
}


void ArduinoUSBInterface::sendStart()
{
    serial_port->writeByte('S');
}

void ArduinoUSBInterface::sendStop()
{
    serial_port->writeByte('X');
}
