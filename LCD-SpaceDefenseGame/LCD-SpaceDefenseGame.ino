#include "pitches.h"
#include <LiquidCrystal.h> 
LiquidCrystal lcd(1, 2, 4, 5, 6, 7);
int ledPin1 = 14;    // choose the input pin (for led)
int ledPin2 = 15;    // choose the input pin (for led)
int ledPin3 = 16;    // choose the input pin (for led)
int inizq = 9;   // choose the input pin (for a pushbutton)
int inder = 8;   // choose the input pin (for a pushbutton)
int indisp = 10; 
int val = 0;     // variable for reading the pin status
int nave = 2;
int disp1 = -1;
int disp2 = -1;
int disp3 = -1;
int disp4 = -1;
int meteorito = 0;
int me1 = 17;
int me2 = 17;
int me3 = 17;
int me4 = 17;
int puntos = 0;
int vida = 0;
int v1 = 0;
int v2 = 0;
int v3 = 0;

byte n1[8] = {
 B11000, 
 B11111, 
 B11000,  
 B00000,   
 B00000, 
 B00000, 
 B00000,
 B00000 
};
byte n2[8] = {
 B00000, 
 B00000, 
 B00000,  
 B00000,   
 B00000, 
 B11000,   
 B11111,
 B11000, 
};
byte laser1[8] = {
 B00000,  
 B11111, 
 B00000,   
 B00000,   
 B00000, 
 B00000, 
 B00000,
 B00000 
};
byte laser2[8] = {
 B00000, 
 B00000, 
 B00000,  
 B00000,   
 B00000, 
 B00000,
 B11111,
 B00000,
};
byte met1[8] = {
 B01100, 
 B10010, 
 B01100,  
 B00000,   
 B00000, 
 B00000,
 B00000,
 B00000,
};
byte met2[8] = {
 B00000,   
 B00000, 
 B00000,
 B00000,
 B00000,
 B01100, 
 B10010, 
 B01100,
};
byte exp1[8] = {
 B10010,   
 B00000, 
 B10010,
 B00000,
 B00000,
 B00000, 
 B00000, 
 B00000,
};
byte exp2[8] = {
 B00000,
 B00000,
 B00000, 
 B00000, 
 B00000,
 B10010,   
 B00000, 
 B10010,
};
int melody[] = {
  NOTE_A3, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
  
int melodybeginning[]={NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};
int noteDurations[]={4, 8, 8, 4, 4, 4, 4, 4};

#include "SevSeg.h"
SevSeg sevseg; //Initiate a seven segment controller object


void setup() { 

byte leds = 0;

byte numDigits = 4;

byte digitPins[] = {42, 43, 44, 45};

byte segmentPins[] = {46, 47, 48, 49, 50, 51, 52, 53};


sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins);

sevseg.setBrightness(90);


lcd.begin(16,2); 
pinMode(inizq, INPUT);    // declare pushbutton as input
pinMode(inder, INPUT);    // declare pushbutton as input
pinMode(indisp, INPUT);    // declare pushbutton as input
pinMode(ledPin1, OUTPUT);    // declare LED as output
pinMode(ledPin2, OUTPUT);    // declare LED as output
pinMode(ledPin3, OUTPUT);    // declare LED as output
lcd.createChar(0,n1);
lcd.createChar(1,n2);
lcd.createChar(2,laser1);
lcd.createChar(3,laser2);
lcd.createChar(4,met1);
lcd.createChar(5,met2);
lcd.createChar(6,exp1);
lcd.createChar(7,exp2);

randomSeed(analogRead(0));
}

//*********************************************************************************************************************
void loop() { 

if (vida < 1)
{

nave = 2;
disp1 = -1;
disp2 = -1;
disp3 = -1;
disp4 = -1;
me1 = 17;
me2 = 17;
me3 = 17;
me4 = 17;
lcd.setCursor(0,0);
lcd.print("   Press Shoot  "); 
lcd.setCursor(0,1);
lcd.print("     to play    "); 
lcd.setCursor(1,0);
lcd.write(byte(4));
lcd.setCursor(15,1);
lcd.write(byte(6));
lcd.setCursor(0,1);
lcd.write(byte(0));

}

do {
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(ledPin3, LOW);
  sevseg.refreshDisplay(); // Must run repeatedly   
  val = digitalRead(indisp);  
  if (val == HIGH && vida < 1) { 
  delay (1);
  val = digitalRead(indisp);
  if (val == LOW && vida < 1) {
  sevseg.blank();
  delay (1000); //Beginning tone
      for (int thisNote=0; thisNote <13; thisNote++){
      //to calculate the note duration, take one second. Divided by the note type
      int noteDuration = 1000 / noteDurations [thisNote];
      tone(13, melodybeginning [thisNote], noteDuration);
      //to distinguish the notes, set a minimum time between them
      //the note's duration +30% seems to work well
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
      //stop the tone playing
      noTone(13);
}
lcd.setCursor(0,0);
lcd.print("                "); 
lcd.setCursor(0,1);
lcd.print("                "); 
  vida = 3;  
  puntos = 0;
  sevseg.setNumber(puntos);
  sevseg.refreshDisplay(); // Must run repeatedly 
  }}
} while (vida < 1);

//VIDALOOP------------------------------------------------------------------------------- 
if (vida > 2) {
   v1 = 1;
   v2 = 1;
   v3 = 1;
} else {
if (vida > 1) {
   v1 = 1;
   v2 = 1;
   v3 = 0;
} else {
if (vida > 0) {
   v1 = 1;
   v2 = 0;
   v3 = 0;
}}}

if (v1 > 0) {
    digitalWrite(ledPin1, HIGH);
  } else {
    digitalWrite(ledPin1, LOW);
}

if (v2 > 0) {
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
}

if (v3 > 0) {
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin3, LOW);
}
//VIDALOOP------------------------------------------------------------------------------- 
 
sevseg.refreshDisplay(); // Must run repeatedly   
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (me1 > 0) {
if (me1 < 17) {
  lcd.setCursor(me1+1,0);
  lcd.print(" ");  
  lcd.setCursor(me1,0);
  lcd.write(byte(4));
  me1 -= 1;
}
} else {
  tone(13, NOTE_B0, 2001); //Dead
  vida -= 1;
  me1 = 17;
}
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (me2 > 0) {
if (me2 < 17) {
  lcd.setCursor(me2+1,0);
  lcd.print(" ");  
  lcd.setCursor(me2,0);
  lcd.write(byte(5));
  me2 -= 1;
}
} else {
  tone(13, NOTE_B0, 2001); //Dead
  vida -= 1;
  me2 = 17;
}
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (me3 > 0) {
if (me3 < 17) {
  lcd.setCursor(me3+1,1);
  lcd.print(" ");  
  lcd.setCursor(me3,1);
  lcd.write(byte(4));
  me3 -= 1;
}
} else {
  tone(13, NOTE_B0, 2001); //Dead
  vida -= 1;
  me3 = 17;
}
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (me4 > 0) {
if (me4 < 17) {
  lcd.setCursor(me4+1,1);
  lcd.print(" ");  
  lcd.setCursor(me4,1);
  lcd.write(byte(5));
  me4 -= 1;
}
} else {
  tone(13, NOTE_B0, 2001); //Dead
  vida -= 1;
  me4 = 17;
}
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (nave > 4) 
{
  nave = 4;
} else {
if (nave < 1) 
{
  nave = 1;
}
}
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (disp1 > 0) {
  if (disp1 == 17) {
    disp1 -= 18;
    } else {
  lcd.setCursor(disp1-1,0);
  lcd.print(" ");  
  lcd.setCursor(disp1,0);
  lcd.write(byte(2));
  disp1 += 1;
}
} 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (disp2 > 0) {
  if (disp2 == 17) {
    disp2 -= 18;
    } else {
  lcd.setCursor(disp2-1,0);
  lcd.print(" ");  
  lcd.setCursor(disp2,0);
  lcd.write(byte(3));
  disp2 += 1;
}
} 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly  
sevseg.refreshDisplay(); // Must run repeatedly 
if (disp3 > 0) {
  if (disp3 == 17) {
    disp3 -= 18;
    } else {
  lcd.setCursor(disp3-1,1);
  lcd.print(" ");  
  lcd.setCursor(disp3,1);
  lcd.write(byte(2));
  disp3 += 1;
}
}
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (disp4 > 0) {
  if (disp4 == 17) {
    disp4 -= 18;
    } else {
  lcd.setCursor(disp4-1,1);
  lcd.print(" ");  
  lcd.setCursor(disp4,1);
  lcd.write(byte(3));
  disp4 += 1;
}
}
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
sevseg.refreshDisplay(); // Must run repeatedly 
if (nave == 1)
{
lcd.setCursor(0,1);
lcd.print(" ");  
lcd.setCursor(0,0);
lcd.write(byte(0));
} else {
if (nave == 2)
{
lcd.setCursor(0,1);
lcd.print(" "); 
lcd.setCursor(0,0);
lcd.write(byte(1));  
} else {
if (nave == 3)
{
lcd.setCursor(0,0);
lcd.print(" "); 
lcd.setCursor(0,1);
lcd.write(byte(0));  
} else {
if (nave == 4)
{
lcd.setCursor(0,0);
lcd.print(" ");
lcd.setCursor(0,1);
lcd.write(byte(1));  
}
}
}
}

sevseg.refreshDisplay(); // Must run repeatedly 
//MAXIMUMDELAY**********************************************
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
delay(2); 
sevseg.refreshDisplay(); // Must run repeatedly 
//MAXIMUMDELAY**********************************************


sevseg.refreshDisplay(); // Must run repeatedly 
meteorito = random (1,10);
if (meteorito == 1) {
  if (me1 == 17 && (me2 == 17 || me2 < 15)) {
  me1 -= 1;
} else {
  lcd.setCursor(me1+1,0);
  lcd.print(" ");  
  lcd.setCursor(me1,0);
  lcd.write(byte(4));
  me1 -= 0;
} 
} else {
if (meteorito == 2) {
  if (me2 == 17 && (me1 == 17 || me1 < 15)) {
  me2 -= 1;
} else {
  lcd.setCursor(me2+1,0);
  lcd.print(" ");  
  lcd.setCursor(me2,0);
  lcd.write(byte(5));
  me2 -= 0;
} 
} else {
if (meteorito == 3) {
  if (me3 == 17 && (me4 == 17 || me4 < 15)) {
  me3 -= 1;
} else {
  lcd.setCursor(me3+1,1);
  lcd.print(" ");  
  lcd.setCursor(me3,1);
  lcd.write(byte(4));
  me3 -= 0;
} 
} else {
if (meteorito == 4) {
  if (me4 == 17 && (me3 == 17 || me3 < 15)) {
  me4 -= 1;
} else {
  lcd.setCursor(me4+1,1);
  lcd.print(" ");  
  lcd.setCursor(me4,1);
  lcd.write(byte(5));
  me4 -= 0;
} 
}
}
}
}

sevseg.refreshDisplay(); // Must run repeatedly 
val = digitalRead(inizq);  
if (val == LOW) {        
nave = nave+1; 
} else {
val = digitalRead(inder);  
if (val == LOW) {       
nave = nave-1;
} else {
val = digitalRead(indisp);  
if (val == LOW) {       
if (nave == 1 && disp1 == -1) {   
tone(13, NOTE_D5, 100);   
tone(13, NOTE_C6, 57);  
disp1 = 1;
lcd.setCursor(1,0);
lcd.write(byte(2));
} else {
if (nave == 2 && disp2 == -1) { 
tone(13, NOTE_D5, 100); 
tone(13, NOTE_C6, 57);  
disp2 = 1;
lcd.setCursor(1,0);
lcd.write(byte(3));
} else {
if (nave == 3 && disp3 == -1) {  
tone(13, NOTE_D5, 100);
tone(13, NOTE_C6, 57);  
disp3 = 1;
lcd.setCursor(1,1);
lcd.write(byte(2));
} else {
if (nave == 4 && disp4 == -1) {  
tone(13, NOTE_D5, 100); 
tone(13, NOTE_C6, 57); 
disp4 = 1;
lcd.setCursor(1,1);
lcd.write(byte(3));
}
}
}
}
}
}
}
sevseg.refreshDisplay(); // Must run repeatedly 
if (me1 == disp1) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me1-1,0);
 lcd.print(" ");
 lcd.setCursor(me1+1,0);
 lcd.print(" ");
 lcd.setCursor(me1,0);
 lcd.write(byte(6));
 me1 = 17;
 disp1 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
} else {
if (me1 == disp1-1) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me1+1,0);
 lcd.print(" ");
 lcd.setCursor(me1,0);
 lcd.write(byte(6));
 me1 = 17;
 disp1 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
} 
}

if (me2 == disp2) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me2-1,0);
 lcd.print(" ");
 lcd.setCursor(me2+1,0);
 lcd.print(" ");
 lcd.setCursor(me2,0);
 lcd.write(byte(7));
 me2 = 17;
 disp2 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
} else { 
if (me2 == disp2-1) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me2+1,0);
 lcd.print(" ");
 lcd.setCursor(me2,0);
 lcd.write(byte(7));
 me2 = 17;
 disp2 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
} 
}

if (me3 == disp3) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me3-1,1);
 lcd.print(" ");
 lcd.setCursor(me3+1,1);
 lcd.print(" ");
 lcd.setCursor(me3,1);
 lcd.write(byte(6));
 me3 = 17;
 disp3 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
} else { 
if (me3 == disp3-1) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me3+1,1);
 lcd.print(" ");
 lcd.setCursor(me3,1);
 lcd.write(byte(6));
 me3 = 17;
 disp3 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
} 
}

if (me4 == disp4) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me4-1,1);
 lcd.print(" ");
 lcd.setCursor(me4+1,1);
 lcd.print(" ");
 lcd.setCursor(me4,1);
 lcd.write(byte(7));
 me4 = 17;
 disp4 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
} else { 
if (me4 == disp4-1) {
 tone(13, NOTE_A3, 100); 
 lcd.setCursor(me4+1,1);
 lcd.print(" ");
 lcd.setCursor(me4,1);
 lcd.write(byte(7));
 me4 = 17;
 disp4 = -1;
 puntos += 10;
 sevseg.setNumber(puntos);
 sevseg.refreshDisplay(); // Must run repeatedly 
}
}
sevseg.refreshDisplay(); // Must run repeatedly 
}
