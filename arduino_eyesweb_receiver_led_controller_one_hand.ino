///////////////////////////////////////////////////////////////////
//
// BoF :: "arduino_eyesweb_receiver_led_controller_one_hand.ino"
//
// 2018/03/21 - 23:00 GMT+1
//
// XrosaXasorX @ synkhro . com
//
// www . synkhro . com
//
///////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////
//
// Constants.
//

// Constants for LED pins.
const int LED_R = 13;
const int LED_G = 12;
const int LED_V = 11;

// Constants for hand positions.
const int C_LEV_Z = 200;
const int C_LEV_D =  99;
const int C_LEV_C =  66;
const int C_LEV_B =  33;
const int C_LEV_A =   1;
const int C_LEV_0 =   0;


///////////////////////////////////////////////////////////////////
//
// Global variables.
//


// Byte read from serial device.
int incomingByte = 0;

// Counter for flashing LEDs (NO-OPERATOR).
long g_FlashCont = 0;

// Timestamp for No-Operator flashing.
unsigned long mymillis = 0;


///////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(9600);
  pinMode( LED_R, OUTPUT );
  pinMode( LED_G, OUTPUT );
  pinMode( LED_V, OUTPUT );
  for( int ll=1; ll<11; ll++ )
    {
    digitalWrite(LED_R, HIGH); delay(50);
    digitalWrite(LED_R, LOW ); delay(50);
    digitalWrite(LED_G, HIGH); delay(50);
    digitalWrite(LED_G, LOW ); delay(50);
    digitalWrite(LED_V, HIGH); delay(50);
    digitalWrite(LED_V, LOW ); delay(50);  
    }
}//setup
///////////////////////////////////////////////////////////////////


void loop() {

  // Some data is available from the Serial Device input.
  if( Serial.available() > 0 )
    {

    // Set timestamp.
    mymillis = millis();

    // Read a character from the "COM:" Serial Device.
    incomingByte = Serial.read();

    // Colored LEDs.
    if( (incomingByte > C_LEV_C) && (incomingByte < C_LEV_D) )
      {
      digitalWrite(LED_G, HIGH);
      digitalWrite(LED_R, LOW );
      digitalWrite(LED_V, LOW );
      }
    if( (incomingByte > C_LEV_B) && (incomingByte < C_LEV_C) )
      {
      digitalWrite(LED_G, LOW );
      digitalWrite(LED_R, HIGH);
      digitalWrite(LED_V, LOW );
      }
    if( (incomingByte > C_LEV_A) && (incomingByte < C_LEV_B) )
      {
      digitalWrite(LED_G, LOW );
      digitalWrite(LED_R, LOW );
      digitalWrite(LED_V, HIGH);
      }

    // No-Operator.
    if( incomingByte >= C_LEV_Z )
      {
      flasher(10);
      }
   
    }//if_serial
  else
    {
    if( (millis() - mymillis) > 1000 )
      flasher(10000);
    }//else_serial

}//loop
///////////////////////////////////////////////////////////////////


void flasher( long period )
  {
  
  g_FlashCont++;
  
  if( g_FlashCont < (1*period) )
    {
    digitalWrite(LED_V, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_R, HIGH);
    }
    
  if( (g_FlashCont > (1*period)) && (g_FlashCont < (2*period)) )
    {
    digitalWrite(LED_V, LOW );
    digitalWrite(LED_G, LOW );
    digitalWrite(LED_R, LOW );
    }
    
  if( g_FlashCont > (2*period) )
    { g_FlashCont = 0; }
    
}//flasher
///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// EoF :: "arduino_eyesweb_receiver_led_controller_one_hand.ino"
///////////////////////////////////////////////////////////////////
