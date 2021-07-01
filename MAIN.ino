/*********************************************************************
 This is an example for our nRF52 based Bluefruit LE modules

 Pick one up today in the adafruit shop!

 Adafruit invests time and resources providing this open source code,
 please support Adafruit and open-source hardware by purchasing
 products from Adafruit!

 MIT license, check LICENSE for more information
 All text above, and the splash screen below must be included in
 any redistribution
*********************************************************************/

/*
 * This sketch demonstrate the central API(). A additional bluefruit
 * that has bleuart as peripheral is required for the demo.
 */
#include <bluefruit.h>



#include "Arduino.h"
int incoming;

#include <Adafruit_NeoPixel.h>

BLEClientBas  clientBas;  // battery client
BLEClientDis  clientDis;  // device information client
BLEClientUart clientUart; // bleuart client

#define NEO_PIN 8 
#define NEO_COUNT 1

Adafruit_NeoPixel strip(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800); 

int pixels=1; 
byte hello=1;
int a=1;  

int pd = 300; // input from pure data -- 300 is placeholder for nothing
// int L_Target = 0;  // what loop -- for the display ONLY
// int T_Target = 0; // what track -- for the display ONLY 

int lightstate = 5;  // blink state. Blinks until pure data loads.
int button = 0;
int OUT=0;
int temp = 0;
int wtf=0; // this resets when new bluetooth info comes in... 


// LIGHTS

int RED1 = 0;  // used mainly for record
int GREEN1 = 0;
int RED2=0; // ABOVE TRACK, alternate record
int GREEN2=0; // ABOVE CLEAR
int YELLOW=0; // session record on or off
int BLUE=0; // monitoring on or off

// These get the actual arduino reads from the pins: 
int RecPress = 0;  // send 1 to pure data (pure data uses this to trigger "RECORD"
int PlayPress = 0; // send 2 
int BackPress = 0; // send 4
int NextPress = 0; // send 5
int FifthPress = 0; // sends a 3 
int TrackPress = 0; // sends an 8 apparently? 

// flags make sure button presses are sent only once... 
int recflag = 0;
int playflag=0;
int backflag=0;
int nextflag=0;
int fifthflag=0; // this is new
int trackflag=0; // also new

// clear combos
int CLEARnRECflag = 0;
int CLEARnPLAYflag=0;
int CLEARnBACKflag=0;
int CLEARnNEXTflag=0;

// track combos
int TRACKnRECflag = 0;
int TRACKnPLAYflag=0;
int TRACKnBACKflag=0;
int TRACKnNEXTflag=0;



#define R_switch A1
#define P_switch A0
#define Prev_switch 10
#define Next_switch 12
#define Fifth_switch 11 // clear
#define Track_switch A5


#define R_light A3
#define P_light A2 // you USED to do by end, so you'll have to change
#define BLUE_light 13
#define YELLOW_light 9
#define GREEN_light 6 // NEW
#define RED_light 5 // NEW



void setup()
{

pinMode (R_switch, INPUT_PULLUP); // record 
pinMode (P_switch, INPUT_PULLUP); // play
pinMode (Prev_switch, INPUT_PULLUP); // play
pinMode (Next_switch, INPUT_PULLUP); // next
pinMode (Fifth_switch, INPUT_PULLUP); // clear?
pinMode (Track_switch, INPUT_PULLUP); // track switch 

pinMode(R_light, OUTPUT); // record light
pinMode(P_light, OUTPUT);  // play light 
pinMode(BLUE_light, OUTPUT); // using for live record
pinMode(YELLOW_light, OUTPUT);  // using for monitor
pinMode(GREEN_light, OUTPUT);  // using for monitor
pinMode(RED_light, OUTPUT);  // using for monitor





  
  Serial.begin(9600);
   while ( !Serial ) { delay(1); }  // for nrf52840 with native usb  ---> NEED TO UNCOMMENT THIS! 


//  Serial.println("Bluefruit52 Central BLEUART Example");
//  Serial.println("-----------------------------------\n");
  
  // Initialize Bluefruit with maximum connections as Peripheral = 0, Central = 1
  // SRAM usage required by SoftDevice will increase dramatically with number of connections
  Bluefruit.begin(0, 1);
  
  Bluefruit.setName("Bluefruit52 Central");

  // Configure Battyer client
  clientBas.begin();  

  // Configure DIS client
  clientDis.begin();

  // Init BLE Central Uart Serivce
  clientUart.begin();
//  clientUart.setRxCallback(bleuart_rx_callback);

  // Increase Blink rate to different from PrPh advertising mode
  Bluefruit.setConnLedInterval(250);

  // Callbacks for Central
  Bluefruit.Central.setConnectCallback(connect_callback);
  Bluefruit.Central.setDisconnectCallback(disconnect_callback);

  /* Start Central Scanning
   * - Enable auto scan if disconnected
   * - Interval = 100 ms, window = 80 ms
   * - Don't use active scan
   * - Start(timeout) with timeout = 0 will scan forever (until connected)
   */
  Bluefruit.Scanner.setRxCallback(scan_callback);
  Bluefruit.Scanner.restartOnDisconnect(true);
  Bluefruit.Scanner.setInterval(160, 80); // in unit of 0.625 ms
  Bluefruit.Scanner.useActiveScan(false);
  Bluefruit.Scanner.start(0);                   // // 0 = Don't stop scanning after n seconds
}

/**
 * Callback invoked when scanner pick up an advertising data
 * @param report Structural advertising data
 */
void scan_callback(ble_gap_evt_adv_report_t* report)
{
  // Check if advertising contain BleUart service
  if ( Bluefruit.Scanner.checkReportForService(report, clientUart) )
  {
//    Serial.print("BLE UART service detected. Connecting ... ");

    // Connect to device with bleuart service in advertising
    Bluefruit.Central.connect(report);
  }else
  {      
    // For Softdevice v6: after received a report, scanner will be paused
    // We need to call Scanner resume() to continue scanning
    Bluefruit.Scanner.resume();
  }
}

/**
 * Callback invoked when an connection is established
 * @param conn_handle
 */
void connect_callback(uint16_t conn_handle)
{
 // Serial.println("Connected");

 // Serial.print("Dicovering Device Information ... ");
  if ( clientDis.discover(conn_handle) )
  {
 //   Serial.println("Found it");
    char buffer[32+1];
    
    // read and print out Manufacturer
    memset(buffer, 0, sizeof(buffer));
    if ( clientDis.getManufacturer(buffer, sizeof(buffer)) )
    {
 //     Serial.print("Manufacturer: ");
  //    Serial.println(buffer);
    }

    // read and print out Model Number
    memset(buffer, 0, sizeof(buffer));
    if ( clientDis.getModel(buffer, sizeof(buffer)) )
    {
  //    Serial.print("Model: ");
 //     Serial.println(buffer);
    }

  //  Serial.println();
  }else
  {
  //  Serial.println("Found NONE");
  }

 // Serial.print("Dicovering Battery ... ");
  if ( clientBas.discover(conn_handle) )
  {
  //  Serial.println("Found it");
 //   Serial.print("Battery level: ");
  //  Serial.print(clientBas.read());
 //   Serial.println("%");
  }else
  {
 //   Serial.println("Found NONE");
  }

 // Serial.print("Discovering BLE Uart Service ... ");
  if ( clientUart.discover(conn_handle) )
  {
  //  Serial.println("Found it");

  //  Serial.println("Enable TXD's notify");
    clientUart.enableTXD();

  //  Serial.println("Ready to receive from peripheral");
  }else
  {
  //  Serial.println("Found NONE");
    
    // disconnect since we couldn't find bleuart service
    Bluefruit.disconnect(conn_handle);
  }  
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;
  
 // Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}

/**
 * Callback invoked when uart received data
 * @param uart_svc Reference object to the service where the data 
 * arrived. In this example it is clientUart
 */
 void bleuart_rx_callback(BLEClientUart& uart_svc)
{
 // Serial.print("[RX]: ");
  
// if ( uart_svc.available() )   // MIGHT NEED TO CHANGE THIS WHILE... TOO SLOW? 
 // {
    // Serial.print( (char) uart_svc.read() );
    // pd = int (uart_svc.read());
  //  }

 // Serial.println();
 }






void loop()
{



 if (Serial.available() > 0) 
  {
//  INCOMING DATA PROCESSING
     incoming = int(Serial.read());
 if ((incoming >= 0) && (incoming < 256))
 {
  pd=incoming; 
  
     
 if (pd < 10){lightstate=pd; OUT=lightstate; pd=300;wtf=1;}
 if ((pd > 29) && (pd < 90)){OUT=pd; pd=300;wtf=1;}
  
  if (pd==11){RED1=1;pd=300;}  
  if (pd==21){RED1=0; pd=300;}
 if (pd==12){GREEN1=1;pd=300;}
 if (pd==22){GREEN1=0;pd=300;}
 if (pd==13){BLUE=1;pd=300;}
 if (pd==23){BLUE=0;pd=300;}
 if (pd==14){YELLOW=1;pd=300;}
  if (pd==24){YELLOW=0;pd=300;}
 if (pd==15){RED2=1; pd=300;}
 if (pd==25){RED2=0; pd=300;}
 if (pd==16){GREEN2=1; pd=300;} 
 if (pd==26){GREEN2=0; pd=300;} 
  



   
     }
    

   
 if (RED1==1){digitalWrite(R_light, HIGH);}
 if (RED1==0){digitalWrite(R_light, LOW);}
 if (GREEN1==1){digitalWrite(P_light, HIGH);}
 if (GREEN1==0){digitalWrite(P_light, LOW);}
  if (BLUE==1){digitalWrite(BLUE_light, HIGH);}
 if (BLUE==0){digitalWrite(BLUE_light, LOW);}
 if (YELLOW==1){digitalWrite(YELLOW_light, HIGH);}
 if (YELLOW==0){digitalWrite(YELLOW_light, LOW);}
 if (RED2==1){digitalWrite(RED_light, HIGH);}
 if (RED2==0){digitalWrite(RED_light, LOW);}
 if (GREEN2==1){digitalWrite(GREEN_light, HIGH);}
 if (GREEN2==0){digitalWrite(GREEN_light, LOW);}
 

 }
    
  

// USER INPUT PROCESSING

RecPress=digitalRead(R_switch);
PlayPress=digitalRead(P_switch);
BackPress=digitalRead(Prev_switch);
NextPress=digitalRead(Next_switch);
FifthPress=digitalRead(Fifth_switch);
TrackPress=digitalRead(Track_switch);  

 
button=0;





if (RecPress==HIGH&&recflag==0){
   button=1;
   recflag=1;
 }

 if (PlayPress==HIGH&&playflag==0){
   button=2;
   playflag=1;
 }


if (FifthPress==HIGH&&fifthflag==0){        // CLEAR IS SUPER SIMPLE NOW
    button=3;
    fifthflag=1;
 }


if (BackPress==HIGH&&backflag==0){
   button=4;
   backflag=1;
 }
  
if (NextPress==HIGH && nextflag==0){
   button=5;
   nextflag=1;
   }

if (TrackPress==HIGH && trackflag==0){   
     button=8;
   trackflag=1;
   }


// CLEAR COMBOS

if (RecPress==HIGH&&FifthPress==HIGH&&CLEARnRECflag==0){
   button=9;
   CLEARnRECflag=1;
 }

if (PlayPress==HIGH&&FifthPress==HIGH&&CLEARnPLAYflag==0){
   button=10;
   CLEARnPLAYflag=1;
 }

if (BackPress==HIGH&&FifthPress==HIGH&&CLEARnBACKflag==0){
   button=7;
   CLEARnBACKflag=1;
 }

if (NextPress==HIGH&&FifthPress==HIGH&&CLEARnNEXTflag==0){
   button=6;
   CLEARnNEXTflag=1;
 }

// TRACK COMBOS

 

if (RecPress==HIGH&&TrackPress==HIGH&&TRACKnRECflag==0){
   button=11;
   TRACKnRECflag=1;
 }

if (PlayPress==HIGH&&TrackPress==HIGH&&CLEARnPLAYflag==0){
   button=12;
   TRACKnPLAYflag=1;
 }

if (BackPress==HIGH&&TrackPress==HIGH&&CLEARnBACKflag==0){
   button=13;
   TRACKnBACKflag=1;
 }

if (NextPress==HIGH&&TrackPress==HIGH&&CLEARnNEXTflag==0){
   button=14;
   TRACKnNEXTflag=1;
 }

   
if (RecPress==LOW)recflag=0;
if (PlayPress==LOW)playflag=0;
if (NextPress==LOW)nextflag=0;
if (BackPress==LOW)backflag=0;
if (TrackPress==LOW)trackflag=0;
if (FifthPress==LOW)fifthflag=0;

if (FifthPress==LOW&&RecPress==LOW)CLEARnRECflag=0;
if (FifthPress==LOW&&PlayPress==LOW)CLEARnPLAYflag=0;
if (FifthPress==LOW&&BackPress==LOW)CLEARnBACKflag=0;
if (FifthPress==LOW&&NextPress==LOW)CLEARnNEXTflag=0;

if (TrackPress==LOW&&RecPress==LOW)TRACKnRECflag=0;
if (TrackPress==LOW&&PlayPress==LOW)TRACKnPLAYflag=0;
if (TrackPress==LOW&&BackPress==LOW)TRACKnBACKflag=0;
if (TrackPress==LOW&&NextPress==LOW)TRACKnNEXTflag=0;

if (button>0) {
 byte data=byte(button);
 Serial.write(data);
 delay(350);
 button=0;
 }



 
 if ( Bluefruit.Central.connected() )
  {
 if ( clientUart.discovered() )
 {

if (wtf == 1){
 uint8_t data;
//// byte data2;
  data = uint8_t (OUT);
 // data2 = byte (pd);
 // Serial.println(F("-----------")); 
 // Serial.println(F("Outgoing data"));
 // Serial.write(data2);                        <<this one worked for PD. 
  clientUart.write(data);
 delay(1);
wtf=0;
OUT=0;
 }
    
     }
  }
  
  }
