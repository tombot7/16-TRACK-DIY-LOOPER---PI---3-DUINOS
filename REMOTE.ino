// VALUES COMING FROM SERIAL

int incoming = 0; 
int pd = 300;

// GOING OUT TO SERIAL

int button = 0;

// LIGHT STATES

int BLUE=0;
int GREEN=0;
int RED=0;
int WHITE=0;
int YELLOW=0;


// These get the actual arduino reads from the pins: 
int RedPress = 0;  // send 241 to pure data (pure data uses this to trigger "RECORD"
int BluePress = 0; // send 242
int GreenPress = 0; // send 243
int WhitePress = 0; // send 244
int YellowPress = 0; // sends a 245 
int TrackPress = 0; // sends a 246  

// flags make sure button presses are sent only once... 
int redflag = 0;
int blueflag=0;
int greenflag=0;
int whiteflag=0;
int yellowflag=0; 
int trackflag=0; 

// track combos
int TRACKnREDflag = 0; // 247
int TRACKnGREENflag=0; // 249
int TRACKnBLUEflag=0; // 248
int TRACKnWHITEflag=0; // 250
int TRACKnYELLOWflag=0; // 251

// FADER INPUTS
int Fader1 =1;
int F1_send = 1;
int Fader2 =1;
int F2_send = 1;
int Fader3 =1;
int F3_send = 1;
int Fader4 =1;
int F4_send = 1;


// POT INPUTS
int Pot1 =1;
int P1_send = 1;
int Pot2 =1;
int P2_send = 1;
int Pot3 =1;
int P3_send = 1;
int Pot4 =1;
int P4_send = 1;
int Pot5 =1;
int P5_send = 1;

int pedal = 0; // use for outgoing pedal value converted into bytes 


#define T_button A0

#define pot1 A1
#define pot2 A2
#define pot3 A3
#define pot4 A4
#define pot5 A5

#define fader1 A11
#define fader2 A12
#define fader3 A13
#define fader4 A14

#define W_light 4
#define R_light 2
#define B_light 3
#define G_light 6
#define Y_light 5

#define W_button 26
#define R_button 28
#define B_button 30
#define G_button 11
#define Y_button 24


void setup() {
  
// pinMode (pot, INPUT); 


pinMode (W_light, OUTPUT); 
pinMode (R_light, OUTPUT); 
pinMode (B_light, OUTPUT); 
pinMode (G_light, OUTPUT); 
pinMode (Y_light, OUTPUT); 

pinMode (W_button, INPUT_PULLUP); 
pinMode (R_button, INPUT_PULLUP);
pinMode (B_button, INPUT_PULLUP);
pinMode (G_button, INPUT_PULLUP);
pinMode (Y_button, INPUT_PULLUP);

pinMode (T_button, INPUT_PULLUP);


Serial.begin(9600);  // should this be my serial? 
  while ( !Serial ) { delay(1); }  // for nrf52840 with native usb  
  
  // Think about some button you can push when you first pulug in thingy... 


}

void loop() {

// TESTING SHIT

/*

Serial.println ("POTS:");
 Serial.println ();
 Serial.println (analogRead(pot1));
 Serial.println (analogRead(pot2));
 Serial.println (analogRead(pot3));
 Serial.println (analogRead(pot4));
 Serial.println (analogRead(pot5));
  Serial.println ("**************");

 Serial.println ("FADERS:");
 Serial.println ();
 Serial.println (analogRead(fader1));
 Serial.println (analogRead(fader2)); // SOME KIND OF ELECTRICAL ISSUE 
 Serial.println (analogRead(fader3));
 Serial.println (analogRead(fader4));
 Serial.println ("**************");
 
 delay(2000);

 if (digitalRead(T_button)  == LOW) {Serial.println ("TRACK BUTTON PUSHED!");}
 if (digitalRead(W_button)  == LOW) { Serial.println ("WHITE BUTTON PUSHED!") ;}
 if (digitalRead(R_button)  == LOW) { Serial.println ("RED BUTTON PUSHED!") ;}
 if (digitalRead(B_button)  == LOW) { Serial.println ("BLUE BUTTON PUSHED!") ;}
 if (digitalRead(G_button)  == LOW) { Serial.println ("GREEN BUTTON PUSHED!") ;}
 if (digitalRead(Y_button)  == LOW) { Serial.println ("YELLOW BUTTON PUSHED!") ;}

  digitalWrite (W_light, HIGH);
 digitalWrite (R_light, HIGH);
 digitalWrite (B_light, HIGH);
 digitalWrite (G_light, HIGH);
 digitalWrite (Y_light, HIGH);

 delay(500);

 digitalWrite (W_light, LOW);
digitalWrite (R_light, LOW);
digitalWrite (B_light, LOW);
digitalWrite (G_light, LOW);
digitalWrite (Y_light, LOW);

*/ 

// END TEST CODE


// START OF ACTUAL CODE

 if (Serial.available() > 0) 
  {
//  INCOMING DATA PROCESSING
     incoming = int(Serial.read());
 if ((incoming >= 0) && (incoming < 256))
 {
  pd=incoming; 

}

// LIGHTS, BUTTONS
// 
// RED -->  LIGHTS ON: 1 OFF: 2, BUTTON OUT: 241
// BLUE 3, 4, 242
// GREEN 5, 6, 243
// WHITE 7, 8, 244
// YELLOW 9, 10, 245
// TRACK 246

// STARTING SEND BYTE FOR POTS & SLIDERS
//
// TRACK 1, POT 230, SLIDER 231
// TRACK 2: 232, 233
// TRACK 3 234, 235 
// TRACK 4 236, 237
// POT 5 239


// LIGHTS ON AND OFF

  if (pd==11){RED=1;pd=300;}  
  if (pd==21){RED=0; pd=300;}
 if (pd==12){GREEN=1;pd=300;}
 if (pd==22){GREEN=0;pd=300;}
 if (pd==3){BLUE=1;pd=300;}
 if (pd==4){BLUE=0;pd=300;}
  if (pd==7){WHITE=1; pd=300;}
 if (pd==8){WHITE=0; pd=300;}
 if (pd==9){YELLOW=1;pd=300;}
  if (pd==10){YELLOW=0;pd=300;}

  // FADE AMOUNT FOR GREEN LIGHT

// PD 30 = fade in
// PD 31 = fade out
// PD 32 = done fading
// PD 




// TURN LIGHTS ON OR OFF 

 if (RED==1){digitalWrite(R_light, HIGH);}
 if (RED==0){digitalWrite(R_light, LOW);}
 if (GREEN==1){digitalWrite(G_light, HIGH);}
 if (GREEN==0){digitalWrite(G_light, LOW);}
  if (BLUE==1){digitalWrite(B_light, HIGH);}
 if (BLUE==0){digitalWrite(B_light, LOW);}
 if (YELLOW==1){digitalWrite(Y_light, HIGH);}
 if (YELLOW==0){digitalWrite(Y_light, LOW);}
 if (WHITE==1){digitalWrite(W_light, HIGH);}
 if (WHITE==0){digitalWrite(W_light, LOW);}
 
}

// USER INPUT PROCESSING

RedPress=digitalRead(R_button);
GreenPress=digitalRead(G_button);
BluePress=digitalRead(B_button);
YellowPress=digitalRead(Y_button);
WhitePress=digitalRead(W_button);
TrackPress=digitalRead(T_button);

Fader1=analogRead(fader1);
Fader2=analogRead(fader2);
Fader3=analogRead(fader3);
Fader4=analogRead(fader4);

Pot1=analogRead(pot1);
Pot2=analogRead(pot2);
Pot3=analogRead(pot3);
Pot4=analogRead(pot4);
Pot5=analogRead(pot5);
  
 
button=0;

// FADERS AND POTS

if ((Fader1>(F1_send+20)) || (Fader1<(F1_send-20))){
F1_send=Fader1;
 pedal=((F1_send) / 10); // Sends 0-100.  But it'll never actually go to zero...  Will go to something like 5 in theory. And the faders don't go that low so 
 byte data=byte(pedal);
 Serial.write(231);  // first send start byte for pure data
 Serial.write(data); // then fader value 
 delay(75);
 pedal=0;
 
 }

if ((Fader2>(F2_send+20)) || (Fader2<(F2_send-20))){
F2_send=Fader2;
 pedal=((F2_send) / 10); 
 byte data=byte(pedal);
 Serial.write(233);  
 Serial.write(data); 
 delay(75);
 pedal=0;
 
 }


if ((Fader3>(F3_send+20)) || (Fader3<(F3_send-20))){
F3_send=Fader3;
 pedal=((F3_send) / 10); 
 byte data=byte(pedal);
 Serial.write(235);  
 Serial.write(data); 
 delay(75);
 pedal=0;
 
 }
 
if ((Fader4>(F4_send+20)) || (Fader4<(F4_send-20))){
F4_send=Fader4;
 pedal=((F4_send) / 10); 
 byte data=byte(pedal);
 Serial.write(237);  
 Serial.write(data); 
 delay(75);
 pedal=0;
 
 }

if ((Pot1>(P1_send+20)) || (Pot1<(P1_send-20))){
P1_send=Pot1;
 pedal=((P1_send) / 10); 
 byte data=byte(pedal);
 Serial.write(230);  
 Serial.write(data); 
 delay(75);
 pedal=0;
 
 }

if ((Pot2>(P2_send+20)) || (Pot2<(P2_send-20))){
P2_send=Pot2;
 pedal=((P2_send) / 10); 
 byte data=byte(pedal);
 Serial.write(232);  
 Serial.write(data); 
 delay(75);
 pedal=0;
 
 }

if ((Pot3>(P3_send+20)) || (Pot3<(P3_send-20))){
P3_send=Pot3;
 pedal=((P3_send) / 10); 
 byte data=byte(pedal);
 Serial.write(234);  
 Serial.write(data); 
 delay(75);
 pedal=0;

}

if ((Pot4>(P4_send+20)) || (Pot4<(P4_send-20))){
P4_send=Pot4;
 pedal=((P4_send) / 10); 
 byte data=byte(pedal);
 Serial.write(236);  
 Serial.write(data); 
 delay(75);
 pedal=0;
 
 }



if ((Pot5>(P5_send+20)) || (Pot5<(P5_send-20))){
P5_send=Pot5;
 pedal=((P5_send) / 10); 
 byte data=byte(pedal);
 Serial.write(239);  
 Serial.write(data); 
 delay(75);
 pedal=0;
}

// BUTTONS AND COMBOS



if (RedPress==LOW&&redflag==0){
   button=241;
   redflag=1;
 }

 if (BluePress==LOW&&blueflag==0){
   button=242;
   blueflag=1;
 }


if (GreenPress==LOW&&greenflag==0){        // CLEAR IS SUPER SIMPLE NOW
    button=243;
    greenflag=1;
 }


if (WhitePress==LOW&&whiteflag==0){
   button=244;
   whiteflag=1;
 }
  
if (YellowPress==LOW && yellowflag==0){
   button=245;
   yellowflag=1;
   }

if (TrackPress==LOW && trackflag==0){   
     button=246;
   trackflag=1;
   }




// TRACK COMBOS

 

if (RedPress==LOW&&TrackPress==LOW&&TRACKnREDflag==0){
   button=247;
   TRACKnREDflag=1;
 }

if (BluePress==LOW&&TrackPress==LOW&&TRACKnBLUEflag==0){
   button=248;
   TRACKnBLUEflag=1;
 }


if (GreenPress==LOW&&TrackPress==LOW&&TRACKnGREENflag==0){
   button=249;
   TRACKnGREENflag=1;
 }

if (WhitePress==LOW&&TrackPress==LOW&&TRACKnWHITEflag==0){
   button=250;
   TRACKnWHITEflag=1;
 }

if (YellowPress==LOW&&TrackPress==LOW&&TRACKnYELLOWflag==0){
   button=251;
   TRACKnYELLOWflag=1;
 }

// RESET FLAGS IF BUTTONS BACK
   
if (RedPress==HIGH)redflag=0;
if (BluePress==HIGH)blueflag=0;
if (GreenPress==HIGH)greenflag=0;
if (WhitePress==HIGH)whiteflag=0;
if (YellowPress==HIGH)yellowflag=0;
if (TrackPress==HIGH)trackflag=0;


if (TrackPress==HIGH&&RedPress==HIGH)TRACKnREDflag=0;
if (TrackPress==HIGH&&BluePress==HIGH)TRACKnBLUEflag=0;
if (TrackPress==HIGH&&GreenPress==HIGH)TRACKnGREENflag=0;
if (TrackPress==HIGH&&YellowPress==HIGH)TRACKnYELLOWflag=0;
if (TrackPress==HIGH&&WhitePress==HIGH)TRACKnWHITEflag=0;


if (button>0) {
 byte data=byte(button);
 Serial.write(data);
 delay(150);
 button=0;
 }



}
