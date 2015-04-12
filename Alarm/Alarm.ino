// include the library code:
#include <LiquidCrystal.h>  //Include the LCD Library

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);  // Tell LCD to use analog pins

// Outputs
int GREEN_LED_PIN = 2;
int YELLOW_LED_PIN = 3;
int RED_LED_PIN = 4;
int BUZZER_PIN = 9;
int SIREN_PIN = 6;

// Inputs
int SET_ALARM_SW_PIN = 8;
int REED_SW_PIN = 5;

bool prevArmed = false;
bool sirenOn = false;

void setup() {
  lcd.begin(16, 2);  // set up the LCD's number of rows and columns:
  pinMode(GREEN_LED_PIN, OUTPUT);  // Set Green LED to Output
  pinMode(YELLOW_LED_PIN, OUTPUT);  // Set Green LED to Output
  pinMode(RED_LED_PIN, OUTPUT);  // Set Green LED to Output
  pinMode(SET_ALARM_SW_PIN, INPUT_PULLUP);  // Set Alarm Button as INPUT
  pinMode(BUZZER_PIN, OUTPUT);  // Set buzzer as output
  pinMode(SIREN_PIN, OUTPUT);  // Set SIREN_PIN to output
  pinMode(REED_SW_PIN, INPUT_PULLUP);  // Set Reed switch to input
  lcd.print("Security System!");  // Print a message to the LCD.
  delay(1000);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  delay(100);
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  lcd.setCursor(0, 1);
  lcd.print("Scan Tag To Arm!");
  digitalWrite(GREEN_LED_PIN, HIGH);
}

bool WantArmed() {
  if (digitalRead(SET_ALARM_SW_PIN) == 0)
    return true;
  else
    return false;
}

bool ReedTrip() {
  if (digitalRead(REED_SW_PIN) == HIGH)
    return true;
  else
    return false;
}

void SirenOn(bool boOn) {
  if (boOn) {
    digitalWrite(SIREN_PIN, HIGH);
    sirenOn = true;
  } else {
    digitalWrite(SIREN_PIN, LOW);
  }
}

void entryDelay() {  // Code for entry delay goes here
}

void exitDelay() {  // code for exit delay goes here
}

void Block1A() {
  if (WantArmed()) {
    prevArmed = false;
    lcd.clear();
    lcd.print("Disarmed!");
  } else {
    Block1B();
  }
}

void Block1B() {
  if (ReedTrip()) {
    Block1C;
  } else {
    prevArmed = true;
  }
}

void Block1C() {
  entryDelay();
  sirenOn = true;
  lcd.clear();
  lcd.print("Intruder!");
  lcd.setCursor(0, 1);
  lcd.print("Scan Tag To Reset");
  prevArmed = false;
}

void Block2A() {
  if (WantArmed())
    Block2B();
  else
    prevArmed = false;
}

void Block2B() {
  lcd.clear();
  lcd.print("Arming Alarm!");
  lcd.setCursor(0, 1);
  lcd.print("Please Exit!");
  digitalWrite(RED_LED_PIN, HIGH);
  prevArmed = true;
}

void loop() {
  if (prevArmed) {
    Block1A();
  } else {
    Block2A();
  }
}
