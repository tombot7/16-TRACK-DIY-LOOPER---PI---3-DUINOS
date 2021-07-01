#include <bluefruit.h>

// OLED
//www.diyusthad.com
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>


#define OLED_RESET 4
Adafruit_SSD1306 display(128, 64, &Wire, OLED_RESET);


#define NEO_PIN 8 
#define NEO_COUNT 1
Adafruit_NeoPixel strip(NEO_COUNT, NEO_PIN, NEO_GRB + NEO_KHZ800); 

  #define BUTTON_A  9
  #define BUTTON_B  6
  #define BUTTON_C  5

// #define VBATPIN A6

                     
int pd = 300; // input from pure data -- 300 is placeholder for nothing
int L_Target = 0;  // what loop
int T_Target = 0; // what track
int lightstate = 5;  // blink state. Blinks until pure data loads.
int Lone = 0;
int Ltwo = 0;
int Lthree=0;
int Lfour=0;
int Tone = 0;
int Ttwo = 0;
int Tthree = 0;
int Tfour = 0;
int MODE = 0;

int button = 0;
int temp = 0;
int reset=0;
float measuredvbat = 0; 

BLEDis  bledis;
BLEUart bleuart;
BLEBas  blebas;

#define STATUS_LED  (17)
#define BLINKY_MS   (2000)

uint32_t blinkyms;

void setup()
{

pinMode(BUTTON_A, INPUT_PULLUP);
 pinMode(BUTTON_B, INPUT_PULLUP);
 pinMode(BUTTON_C, INPUT_PULLUP);

strip.begin ();
strip.show();

// MORE DISPLAY

display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //or 0x3C
  display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor (0,20);             // Start at top-left corner
  display.println(F("Looking..."));

  display.display();
  delay(300);

  // DISPLAY END

  
  Serial.begin(9600);
    //  while ( !Serial ) { delay(1); }  // for nrf52840 with native usb

  Serial.println("Bluefruit52 BLEUART Example");

  // Setup LED pins and reset blinky counter
  pinMode(STATUS_LED, OUTPUT);
  blinkyms = millis();

  // Setup the BLE LED to be enabled on CONNECT
  // Note: This is actually the default behaviour, but provided
  // here in case you want to control this manually via PIN 19
  Bluefruit.autoConnLed(false);

  Bluefruit.begin();
  Bluefruit.setName("Bluefruit52");
  Bluefruit.Periph.setConnectCallback(connect_callback);
  Bluefruit.Periph.setDisconnectCallback(disconnect_callback);

  // Configure and Start Device Information Service
  bledis.setManufacturer("Adafruit Industries");
  bledis.setModel("Bluefruit Feather52");
  bledis.begin();

  // Configure and Start BLE Uart Service
  bleuart.begin();

  // Start BLE Battery Service
  blebas.begin();
   blebas.write(100);

  // Set up Advertising Packet
  setupAdv();

  // Start Advertising
  Bluefruit.Advertising.start();
}

void setupAdv(void)
{
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  // Include bleuart 128-bit uuid
  Bluefruit.Advertising.addService(bleuart);

  // There is no room for Name in Advertising packet
  // Use Scan response for Name
  Bluefruit.ScanResponse.addName();
}

void loop()
{

  if(!digitalRead(BUTTON_A)) {MODE=0;reset=1;}
  if(!digitalRead(BUTTON_B)) {MODE=1;reset=1;}
  if(!digitalRead(BUTTON_C)) {MODE=2;reset=1;}
  
// Serial.print ("Mode:");
// Serial.print (MODE); 
  
  // Blinky!
 // if (blinkyms+BLINKY_MS < millis()) {
    // blinkyms = millis();
    // digitalToggle(STATUS_LED);
  // }


  if ( bleuart.available() )
  {
    uint8_t ch;
    ch = (uint8_t) bleuart.read();
    pd = int(ch); 
Serial.println(pd);

if (pd < 10) {lightstate = pd; pd=300; reset=1;} 


if (pd > 69&&pd < 75) {L_Target=pd-70;pd=300;reset=1;}
if (pd >79&&pd< 85) {T_Target=pd-80;pd=300;reset=1;}

if (pd > 29&&pd < 35) {Lone=pd-30;pd=300;reset=1;}
if (pd > 34&&pd < 40) {Ltwo=pd-35;pd=300;reset=1;}
if (pd > 39&&pd < 45) {Lthree=pd-40;pd=300;reset=1;}
if (pd > 44&pd <50 ) {Lfour=pd-45;pd=300;reset=1;}

if (pd > 49&&pd < 55) {Tone=pd-50;pd=300;reset=1;}
if (pd > 54&&pd < 60) {Ttwo=pd-55;pd=300;reset=1;}
if (pd > 59&&pd < 65) {Tthree=pd-60;pd=300;reset=1;}
if (pd > 64&pd <70 ) {Tfour=pd-65;pd=300;reset=1;}

  }
 
 



if (reset==1){ 
reset=0;

display.clearDisplay();

if (MODE==4){
 // used for testing
 display.clearDisplay();
display.setTextSize(3);             
display.setTextColor(SSD1306_WHITE);
display.setCursor (10,20);
display.println(MODE);
delay (100);
 }

if (MODE==0){

display.setTextSize(6);             
display.setTextColor(SSD1306_WHITE);  


display.setCursor (10,20); 
display.println(L_Target + 1);
display.setCursor (50,20); 
display.println("-");
display.setCursor (90,20); 
 display.println(T_Target + 1);  

}

if (MODE==1) {

display.setTextSize(4);             
display.setTextColor(SSD1306_WHITE); 

display.setCursor (4,3);    
display.println(Lone);        
display.setCursor (37,3); 
display.println(Ltwo);   
display.setCursor (71,3); 
display.println(Lthree);   
display.setCursor (103,3); 
display.println(Lfour);   


display.setCursor (4,35);    
display.println(Tone);        
display.setCursor (37,35); 
display.println(Ttwo);   
display.setCursor (71,35); 
display.println(Tthree);   
display.setCursor (103,35); 
display.println(Tfour);   

display.fillRect(((L_Target*33)+3), 5, 25, 25, SSD1306_WHITE);
display.fillRect(((T_Target*33)+3), 38, 25, 25, SSD1306_WHITE);
}

if (MODE==2){
  
display.setTextSize(3);             
display.setTextColor(SSD1306_WHITE);  
display.setCursor (0,0); 
  
// measuredvbat = analogRead(VBATPIN);
// measuredvbat *= 2;    // we divided by 2, so multiply back
// measuredvbat *= 3.3;  // Multiply by 3.3V, our reference voltage
// measuredvbat /= 1024; // convert to voltage


display.println(measuredvbat);

display.setCursor (0,33);
display.println("3.2-4.2"); 
  
} // End of Mode 7

display.display();

 



 if (lightstate == 0)  {
    strip.setPixelColor(0, 0, 0, 0, 0);
    strip.show();  
}

 if (lightstate == 5) {
   strip.setPixelColor(0, 111, 50, 66, 28);
      strip.show ();
}



if (lightstate == 1) {
     strip.setPixelColor(0, 255, 0, 0, 0);
      strip.show();
}

if (lightstate == 2) {
     strip.setPixelColor(0, 255, 255, 0, 0);
      strip.show();
}

if (lightstate == 3) {
     strip.setPixelColor(0, 0, 255, 0, 0);
      strip.show();
}

if (lightstate == 4) {
     strip.setPixelColor(0, 0, 0, 255, 0);
      strip.show();
}

   }  // END OF RESET IF
  
} // END OF LOOP {}

// callback invoked when central connects
void connect_callback(uint16_t conn_handle)
{
  // Get the reference to current connection
  BLEConnection* connection = Bluefruit.Connection(conn_handle);

  char central_name[32] = { 0 };
  connection->getPeerName(central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);

    display.clearDisplay();
    display.setTextSize(6);
    display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor (0,0);             // Start at top-left corner
   
  display.println(F("CNX"));
  display.display(); 
  delay(100);
  display.clearDisplay(); 
}

/**
 * Callback invoked when a connection is dropped
 * @param conn_handle connection where this event happens
 * @param reason is a BLE_HCI_STATUS_CODE which can be found in ble_hci.h
 */
void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.println();
  Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor (0,0);             // Start at top-left corner
  display.println(F("disconnected!"));
  display.display(); 
  delay(300);
  
}
