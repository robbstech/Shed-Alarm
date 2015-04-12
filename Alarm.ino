// include the library code:
#include <LiquidCrystal.h> //Include the LCD Library

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5); //Tell LCD to use analog pins
//Outputs
int ledGreen = 2;
int ledYellow = 3;
int ledRed = 4;
int buzz = 9;
int Siren = 6;

//Inputs
int setAlarm = 8;
int reed = 5;


void setup() {
  lcd.begin(16, 2); // set up the LCD's number of rows and columns: 
  pinMode(ledGreen, OUTPUT); //Set Green LED to Output
  pinMode(ledYellow, OUTPUT); //Set Green LED to Output
  pinMode(ledRed, OUTPUT); //Set Green LED to Output
  pinMode(setAlarm, INPUT_PULLUP); //Set Alarm Button as INPUT
  pinMode(buzz, OUTPUT); //Set buzzer as output
  pinMode(Siren, OUTPUT); //Set Siren to output
  pinMode(reed, INPUT_PULLUP); //Set Reed switch to input
  lcd.print("Security System!"); //Print a message to the LCD.
  delay(1000);
  digitalWrite(buzz, HIGH);
  delay(100);
  digitalWrite(buzz, LOW);
  delay(100);
  digitalWrite(buzz, HIGH);
  delay(100);
  digitalWrite(buzz, LOW);
  lcd.setCursor(0,1);
  lcd.print("Scan Tag To Arm!");
  digitalWrite(ledGreen, HIGH);
  boolean SirenOn(false); 
}

boolean prevArmed;

boolean WantArmed(){
if (digitalRead(setAlarm)==0)
            return true; else return false;
}

boolean ReedTrip(){
if (digitalRead(reed)==HIGH)
            return true; else return false;
}

void SirenOn(boolean boOn){
if (boOn) {digitalWrite(Siren,HIGH);
           boolean SirenOn=true;
          }
      else{digitalWrite(Siren,LOW);}
}

void entryDelay(){ //Code for entry delay goes here
  
}

void exitDelay(){ //code for exit delay goes here
  
}

void Block1A(){
   if(WantArmed()) {prevArmed=false;} else {Block1B();}
}

void Block1B(){
  if(ReedTrip()) {Block1C;} else {prevArmed=true;}
}

void Block1C(){
  entryDelay();
  boolean SirenOn=true;
  lcd.clear;
  lcd.print("Intruder!");
  lcd.setCursor(0,1);
  lcd.print("Scan Tag To Reset");
}

void Block2A(){
  if(WantArmed()) Block2B(); else prevArmed=false;
}

void Block2B(){
  lcd.clear;
  lcd.print("Arming Alarm!");
  lcd.setCursor(0,1);
  lcd.print("Please Exit!");
  exitDelay();
  digitalWrite(ledRed, HIGH);
  prevArmed=true;
 
}

void loop(){
  
  if (prevArmed) {Block1A();} else {Block2A();}
  
}

