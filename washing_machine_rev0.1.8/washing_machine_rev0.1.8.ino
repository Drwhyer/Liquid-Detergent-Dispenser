// Washing Machine Soap Despensor
// Whyer
//10-16-19
//
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x3f,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int ledPin = 13;         // pin for led
int inPin1 = 9;          // pin for button 1
int inPin2 = 10;         // pin for button 2
int inPin3 = 11;         // pin for button 3
int inPin4 = 16;         // pin for button 4
int relPin = 15;         // pin for relay
int sbutton = 0;         // value for button 1 pin status
int mbutton = 0;         // value for button 2 pin status
int lbutton = 0;         // value far button 3 pin status
int rbutton = 0;         // value far button 4 pin status
int stmr = 16000;        // value for timer sm load
int mtmr = 22000;        // value for timer med load
int ltmr = 28000;        // value for timer lg load
int scnt = 0;            // counter for small loads
int mcnt = 0;            // counter for medium loads
int lcnt = 0;            // counter for large loads
int total = 0;           // total for loads

void setup () 
{
  Serial.begin (9600);
  //while (!Serial)
  pinMode(ledPin, OUTPUT);
  pinMode (ledPin, OUTPUT);          // set pinmode for led pin
  pinMode (relPin, OUTPUT);          // set pinmode for relay 
  pinMode (inPin1, INPUT);           // set pinmode for button 1
  pinMode (inPin2, INPUT);           // set pinmode for button 2
  pinMode (inPin3, INPUT);           // set pinmode for button 3
  pinMode (inPin4, INPUT);           // set pinmode for button 4
  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);
  scnt = EEPROM.read (0);
  mcnt = EEPROM.read (1);
  lcnt = EEPROM.read (2);
  rbutton = digitalRead (inPin4);    // read input value for button
  
if (rbutton == HIGH)
  {
  zerocounter();
  }
}

void loop ()
{
  digitalWrite (ledPin,HIGH);        // turn on led
  Serial.println ("Running");        // send debug message
  lcd.clear();
  lcd.setCursor (0,0);
  lcd.print ("S=");
  lcd.setCursor (2,0);
  lcd.print (scnt);
  lcd.setCursor (5,0);
  lcd.print ("M=");
  lcd.setCursor (7,0);
  lcd.print (mcnt);
  lcd.setCursor (10,0);
  lcd.print ("L=");
  lcd.setCursor (12,0);
  lcd.print (lcnt);
  lcd.setCursor (0,1);
  lcd.print ("Total Loads=");
  lcd.setCursor (13,1);
  lcd.print (scnt+mcnt+lcnt);
  Serial.print ("Small Loads=");
  Serial.println (scnt);
  Serial.print ("Medium Loads=");
  Serial.println (mcnt);
  Serial.print ("Large Loads=");
  Serial.println (lcnt);
  Serial.print ("Total Loads=");
  Serial.println (scnt+mcnt+lcnt);
  EEPROM.update (0,scnt);
  EEPROM.update (1,mcnt);
  EEPROM.update (2,lcnt);
  sbutton = digitalRead (inPin1);    // read input value for button
  mbutton = digitalRead (inPin2);    // read input value for button
  lbutton = digitalRead (inPin3);    // read input value for button
  rbutton = digitalRead (inPin4);    // read input value for button
if (sbutton == HIGH) 
{               // check to see if button is pressed (HIGH)
  scnt = (scnt+1);                   // add 1 to small load counter
  digitalWrite (relPin,HIGH);        // pull relay pin low
  delay (stmr);                      // timer based on pot
  digitalWrite (relPin,LOW);         // pull relay pin high
}
else if (mbutton == HIGH) 
{          // check to see if button is pressed (HIGH)
  mcnt = (mcnt+1);                   // add 1 to medium load counter
  digitalWrite (relPin,HIGH);        // pull relay pin low
  delay (mtmr);                      // timer based on pot
  digitalWrite (relPin,LOW);         // pull relay pin high  
}
else if (lbutton == HIGH) 
{          // check to see if button is pressed (HIGH)
  lcnt = (lcnt+1);                   // add 1 to large load counter
  digitalWrite (relPin,HIGH);        // pull relay pin low
  delay (ltmr);                      // timer based on pot
  digitalWrite (relPin,LOW);         // pull relay pin high  
}
else 
{
digitalWrite (ledPin,LOW);      // do nothing
delay (50);                          // delay 50 ms
}
}

void zerocounter()
{
  scnt = (0);                   // add 1 to large load counter
  mcnt = (0);                   // add 1 to large load counter
  lcnt = (0);                   // add 1 to large load counter
  lcd.clear();
  delay (1000);
}
