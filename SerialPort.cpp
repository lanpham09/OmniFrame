#include "SerialPort.h"
#include <iostream>
#include <string.h>
#include <cmath>

using namespace std;

SerialPort::SerialPort():
    fileDesignator(-1),
    portOpen(false)
{
    fileName = "NONE";
}

SerialPort::SerialPort(const char *device, rate baudRate ):
    fileDesignator(-1),
    portOpen(false)
{
    openPort(device, baudRate);
}

SerialPort::SerialPort(std::string device, rate baudRate ):
    fileDesignator(-1),
    portOpen(false)
{
    openPort(device.c_str(), baudRate);
}

SerialPort::~SerialPort()
{
    closePort();
}

bool SerialPort::openPort(const char *device, rate baudRate )
{

    if(portOpen)
        closePort();

    fileName = "NONE";

    // open the port
    fileDesignator = open(device, O_RDWR | O_NOCTTY);

    // set serial configurations
    cout << "fileDesignator " << fileDesignator<< endl;
    if(fileDesignator == -1) {
        cout << "AMCController: failed to open serial device." << endl;
        portOpen = false;
    }
    else {
        // verify that opened device is serial device (aka tty)
        if(!isatty(fileDesignator))
        {
            cout << "AMCController: this is not a serial device." << endl;
            portOpen = false;
            close(fileDesignator);
            fileDesignator = -1;

        } else {

            struct termios newtio;
            newtio.c_cflag = CS8 | CLOCAL | CREAD;
            switch( baudRate )
            {
            case  B_0:
                newtio.c_cflag = newtio.c_cflag | B0;
                break;
            case B_50:
                newtio.c_cflag = newtio.c_cflag | B50;
                break;
            case B_75:
                newtio.c_cflag = newtio.c_cflag | B75;
                break;
            case B_110:
                newtio.c_cflag = newtio.c_cflag | B110;
                break;
            case B_134:
                newtio.c_cflag = newtio.c_cflag | B134;
                break;
            case B_150:
                newtio.c_cflag = newtio.c_cflag | B150;
                break;
            case B_200:
                newtio.c_cflag = newtio.c_cflag | B200;
                break;
            case B_300:
                newtio.c_cflag = newtio.c_cflag | B300;
                break;
            case B_600:
                newtio.c_cflag = newtio.c_cflag | B600;
                break;
            case B_1200:
                newtio.c_cflag = newtio.c_cflag | B1200;
                break;
            case B_1800:
                newtio.c_cflag = newtio.c_cflag | B1800;
                break;
            case B_2400:
                newtio.c_cflag = newtio.c_cflag | B2400;
                break;
            case B_4800:
                newtio.c_cflag = newtio.c_cflag | B4800;
                break;
            case B_9600:
                newtio.c_cflag = newtio.c_cflag | B9600;
                break;
            case B_19200:
                newtio.c_cflag = newtio.c_cflag | B19200;
                break;
            case B_38400:
                newtio.c_cflag = newtio.c_cflag | B38400;
                break;
            case B_57600:
                newtio.c_cflag = newtio.c_cflag | B57600;
                break;
            case B_115200:
                newtio.c_cflag = newtio.c_cflag | B115200;
                break;
            case B_230400:
                newtio.c_cflag = newtio.c_cflag | B230400;
                break;
            }

            newtio.c_iflag = IGNPAR;
            newtio.c_oflag = 0;
            newtio.c_lflag = 0;
            tcflush(fileDesignator, TCIOFLUSH);
            tcsetattr(fileDesignator, TCSAFLUSH, &newtio);

            fileName = string(device);
            portOpen = true;

        }
    }

    return portOpen;
}

void SerialPort::closePort()
{
    if( portOpen )
        close( fileDesignator );

    fileDesignator = -1;
    fileName = "NONE";
    portOpen = false;
}

bool SerialPort::isOpen() const
{
    return fileDesignator !=-1;
}

/**
 * Flushes data buffer for the serial port.
 *
 */
bool SerialPort::flushData( ) {

    if( portOpen )
    {
        ioctl(fileDesignator, TCFLSH, TCIOFLUSH );
    }
    return portOpen; // otherwise
}


/**
 * Reads data from the serial port and puts it in buffer.
 *
 * Function only reads data if data is available within ms_timeout (microsecond resolution)
 *  milli-seconds of the function call.
 *
 * If a start deliminator is specified, it will shift the read data untill startDelim
 *  is found in the input stream and continue reading until the number of specified bytes has
 *  been read after the start deliminator.  If and end deliminator is specified and is not found
 *  after the specified number of bytes has been read the funciton returns -bytes read;
 *
 * Function Returs:
 *   bytes_read if sucessfully completed, should be equal to the number of bytes requested.
 *
 *   0 if serial file is unset (fileDesignaor = -1)
 *
 *  -bytes_read if the specified number of bytes cound not be read beacuse data was not available in specified timout time,
 *   or if the end Deliminator was not achieved.  If a message length of 15 was requested a return of -1 to -14 means the
 *   number was not reached and -15 means that the end deliminator was not achieved.
 *
 */
int SerialPort::readData( unsigned char *buffer, int bytes,  double ms_timeout, const unsigned char startDelim, const unsigned char endDelim)
{
    if( fileDesignator == -1 )
        return 0; // no input file setup

    int bytes_read = 0;

    while (bytes_read < bytes && isDataAvailable( ms_timeout ) )
    {
        int bytes_left = bytes - bytes_read;
        int byters = read(fileDesignator, buffer + bytes_read*sizeof(char), bytes_left );
        bytes_read += byters;

        // see if start deliminator is start of message
        if( startDelim )
        {
            // find index of start deliminator
            int startIndex = 0;
            for( ; startIndex < bytes_read && buffer[startIndex] != startDelim; startIndex ++ );

            // if not start of message
            if( startIndex > 0 )
            {
                // shift message down to start with start index
                for( int index = 0; index < (bytes_read-startIndex); index ++ )
                    buffer[index] = buffer[index+startIndex];

                // reduce effective number of bytes read
                bytes_read -= startIndex;
            }
        }

    }
    if( (bytes_read < bytes) || (endDelim && buffer[bytes-1] != endDelim) )
        return -bytes_read; // did not complete task as desired or did not end with end deliminator
    return bytes_read;
}

unsigned char SerialPort::readByte(double ms_timout)
{
    unsigned char buf[1] = {0};
    readData( buf, 1, ms_timout);
    return buf[0];
}

std::string SerialPort::getLine( const unsigned char endDelim )
{
    std::string returnString = "";
    unsigned char buf[512] = {0};
    int numRead = -1;
    while( numRead <= 0 )
    {
        numRead = readData(buf, 512, 25, 0, endDelim);
        for( int i=0; i< std::abs(numRead); i++ )
        {
            char value = buf[i];
            returnString += std::string(&value);
        }
    }
    return returnString;
}

bool SerialPort::writeData( unsigned char* buffer, int bytes)
{
    int bytesWritten = 0;
    if( fileDesignator !=-1 )
    {
        bytesWritten = write(fileDesignator, buffer, bytes);
    }
    cout << "wrote " << bytesWritten << endl;
    return bytesWritten == bytes;
}

bool SerialPort::writeByte( unsigned char byteToWrite )
{
    return writeData( &byteToWrite, sizeof(unsigned char));
}


bool SerialPort::isDataAvailable( double ms_timeout )
{
    tv.tv_sec  = (int)ms_timeout/1000;
    tv.tv_usec = (ms_timeout-1000*tv.tv_sec)*1000;

    FD_ZERO(&rfds);
    FD_SET(fileDesignator,&rfds);

    int retval = select(fileDesignator+1, &rfds, NULL, NULL, &tv);


    if( retval == -1 )
        cout << "Error occured in isDataAvailable Serial Port Call to " << fileName << endl;

    return (retval > 0);
}
