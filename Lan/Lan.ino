  
  /****************************************************************
   *
   *    Authors :Lan Pham, Anderw Petruska, Trenton Prestwich
   *    Date: Feb 2, 2017 (update by Lan)
   *    Sketch Name: Ultimate poition finder
   *    Sketch Description: Reads data from sensors on node 0 (aka arm 0)
   *       producing position measuement in mm and rotation in degrees
   *
   * *************************************************************
   *
   *    Hardware Info:
   *      Arduino Due            : 12 bit resolution, should have range of 4096 but we get 3730 
   *      Rotating Potentiometer : Range of 0 to 340 degrees, capable of full rotation
   *      Linear Potentiometer   : Range of 0 to 500 mm
   *      
   *      Each arms needs to be calibrated for their potentiometers
   */
  //============================= Declare Header Libraries Here =============================//

  //============================= Declare Global Variables Here =============================//
  static String DEVICE_NAME("Name: 0");
  
  static int DECIMAL_MULTIPLY = 100000;
  
  static double SENSOR_LENGTH = 500.0;
                                  //{Omni Rotation, Horizontal Linear, Vertical Linear, Center Rotation,TC,TC,TC}
  static double SENSOR_GAIN[7] = {(double)90/1059, -(double)500/3730, (double)90/1059, (double)180/4095.00, 1.0, 1.0, 1.0};//{2.094, 166.66, 166.66, 2.094, 1, 1, 1};//6.14355897
  static double SENSOR_OFFSET[7] = {0, -500, 0, 0, 0, 0, 0};
  static int NUM_READINGS = 10;
  static int OMNIMAGNETPin = 0;
  static int HORIZONTALPin = 1;
  static int VERTICALPin = 2;
  static int CENTERPin = 3;
 
  float celsius1 = 0;
  float celsius2 = 0;
  float celsius3 = 0;    
  //static int TC1 = 4;
  //static int TC2 = 5;
  //static int TC3 = 6;
 
  
  char inByte = 0;
  
  boolean sendData; 
  //================================== Begin Setup Function =================================//
  
  // The setup() function is called when a sketch starts. Use it to initialize variables, 
  // pin modes, start using libraries, etc. The setup function will only run once, after 
  // each powerup or reset of the Arduino board.
  
  void setup()
  {
      Serial.begin(9600); 
      sendData = false;

  } //end setup() function
  
  
  //================================== Begin Loop Function ==================================//
  
  // After creating a setup() function, which initializes and sets the initial values, the 
  // loop() function does precisely what its name suggests, and loops consecutively, allowing 
  // your program to change and respond. Use it to actively control the Arduino board.

  //loop for user input into serial monitor. S starts, X stops, N prints device and else Unknown
  void loop()
  {
    
    if ( Serial.available() > 0 )
    {
       inByte = Serial.read();
       
       if( inByte == 'N')
       {
          Serial.print(DEVICE_NAME);
          Serial.print("\n"); 
       }
       else if( inByte == 'S')
       {
         sendData = true;
       }
       else if( inByte  == 'X' )
       {
         sendData = false;
       }
       else
       {
         Serial.print("Unknown:\n" );
       }       

    }
    
    //When system is S start, data will be sent
    if( sendData )
    {
      Serial.println("sendData"); ////////////////////////////////////LAN ADDED PRINT STATEMENTS
        // subtract the last reading:
        int ones;
        int decimal;
        String strOut = "";
        double voltageBits;
        double value;
        for( int i = 0; i < 7; i++)   //Reads each of the 7 Analog pins on the Due 
        {
            analogReadResolution(12); // make sure were in 12 bit resolution mode!
            
            // average NUM_READINGS consecituve readings with a 50 us delay inbetween
            voltageBits = analogRead(i);   // read voltage
            Serial.print("voltageBits Reading = ");
            Serial.println(voltageBits);
            for( int j=1; j< NUM_READINGS; j++ )
            {
              delayMicroseconds(50);
              voltageBits += analogRead(i);   // read voltage
            }
            
            voltageBits /= (double)NUM_READINGS; // averge and scale to full voltage range
            Serial.print("Average and Scaled to Full Voltage Range = ");
            Serial.println(voltageBits);
        
            value = voltageBits*SENSOR_GAIN[i] - SENSOR_OFFSET[i]; // Convert to a physical value
            Serial.print("Physical Value = ");
            Serial.println(value);
            byte* dataPtr = (byte *) &value;
            
            Serial.write( dataPtr,sizeof(value) ); //will print symboles unless communicating with something
            
            //formates values for printing
            ones = value;                         
            decimal = (value - ones )*DECIMAL_MULTIPLY;
            //strOut += "C" + String(i) + ": ";
            strOut += ones;
            strOut += ".";
            strOut += decimal;
            strOut += " ";
        }
        strOut+= "\n\r";
 
         Serial.print(strOut);
        
    }
    
    delay(200);
  
  } //end loop() function
