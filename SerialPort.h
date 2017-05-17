#ifndef SERIALPORT_H
#define SERIALPORT_H
/************************
  SeiralPort.h and SerialPort.cpp give a wrapper for simple serial IO

  To open a serial port you can use
    SerialPort myPort("/dev/mySerialTTY/",B_9600); // Where B_9600 specifies the baud rate.
    or
    SerialPort myPort;
    myPort.open("/dev/mySerialTTY/",B_9600);

  To send Data (say a c_string)
    myPort.writeData( dataPointer, numberOfBytes);
    myPort.writeByte( byte );

  To read Data
    myPort.readData( dataBufferPointer, numberOfBytesToRead, ms_timeout, startDeliminator, endDeliminator);
        Function only reads data if data is available within ms_timeout (microsecond resolution)
         milli-seconds of the function call.

        If a start deliminator is specified, it will shift the read data untill startDelim
         is found in the input stream and continue reading until the number of specified bytes has
         been read after the start deliminator.  If and end deliminator is specified and is not found
         after the specified number of bytes has been read the funciton returns -bytes read;

        Function Returs:
          bytes_read if sucessfully completed, should be equal to the number of bytes requested.

          0 if serial file is unset (fileDesignaor = -1)

          -bytes_read if the specified number of bytes cound not be read beacuse data was not available in specified timout time,
            or if the end Deliminator was not achieved.  If a message length of 15 was requested a return of -1 to -14 means the
            number was not reached and -15 means that the end deliminator was not achieved.

    myPort.readByte( ms_timout ); // returns one byte of data if a byte is available within the specified ms_timeout


  To remove all existing data from buffer:
    myPort.flushData();

  To check if data is available to read:
    myPort.isDataAvailable( ms_timeout );  // checks to see if data is available.
                                           // Returns true as soon as it is.
                                           // Waits till ms_timout before returning false if it is not yet.

************************/

#include <unistd.h> // UNIX standard function definitions
#include <fcntl.h> // File control definitions
#include <errno.h> // Error number definitions
#include <termios.h> // POSIX terminal control definitionss
#include <sys/ioctl.h>
#include <sys/select.h> // Allows for checking ports for data
#include <string>

class SerialPort
{
    int fileDesignator;
    fd_set rfds;
    struct timeval tv;
    std::string fileName;
    bool portOpen;

public:
    enum rate { B_0, B_50, B_75, B_110, B_134, B_150, B_200, B_300, B_600, B_1200, B_1800, B_2400, B_4800, B_9600, B_19200, B_38400, B_57600, B_115200, B_230400 };
    SerialPort();
    SerialPort(const char *device, rate baudRate = B_9600);
    SerialPort(std::string device, rate baudRate = B_9600);
    ~SerialPort();

    bool openPort( const char *device, rate baudRate = B_9600 );
    void closePort();

    bool writeData( unsigned char* buffer, int bytes );
    bool writeByte( unsigned char byteToWrite );

    unsigned char readByte(double ms_timout = 0 );

    int readData( unsigned char *buffer, int bytes, double ms_timout = 0, const unsigned char startDelim = 0, const unsigned char endDelim = 0 );
    std::string getLine( const unsigned char endDelim = '\n' );

    bool isDataAvailable(double ms_timeout = 0);

    bool flushData();

    bool isOpen() const;
};



#endif // SERIALPORT_H
