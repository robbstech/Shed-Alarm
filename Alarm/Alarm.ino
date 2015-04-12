#include <UniversalInput.h>
#include <UniversalButtons.h>
#include <LiquidCrystal.h>

UniversalButtons buttons;
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);  // Tell LCD to use analog pins

// Outputs
#define GREEN_LED_PIN 2
#define YELLOW_LED_PIN 3
#define RED_LED_PIN 4
#define BUZZER_PIN 9
#define SIREN_PIN 6

// IDs for buttons
enum ButtonID { SET_ALARM, REED };

int setAlarmSwState = HIGH;
int reedSwState = HIGH;

bool prevArmed = false;
bool sirenOn = false;

void setup() {
  lcd.begin(16, 2);  // set up the LCD's number of rows and columns:

  buttons.setDefaultButtonConfig(1, 1);

  buttons.addButton(SET_ALARM, 8);
  buttons.addButton(REED, 5);

  buttons.setStateCycleCallback(&buttonHandler);

  pinMode(GREEN_LED_PIN, OUTPUT);   // Set Green LED to Output
  pinMode(YELLOW_LED_PIN, OUTPUT);  // Set Green LED to Output
  pinMode(RED_LED_PIN, OUTPUT);     // Set Green LED to Output
  pinMode(BUZZER_PIN, OUTPUT);      // Set buzzer as output
  pinMode(SIREN_PIN, OUTPUT);       // Set SIREN_PIN to output

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

void SirenOn(bool on) {
  if (on) {
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
  if (buttons.getButtonState(SET_ALARM)) {
    prevArmed = false;
    lcd.clear();
    lcd.print("Disarmed!");
  } else {
    Block1B();
  }
}

void Block1B() {
  if (buttons.getButtonState(REED)) {
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
  if (buttons.getButtonState(SET_ALARM))
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

void buttonHandler(buttonid_t id, uint32_t time) {}

void loop() {
  buttons.poll();

  if (prevArmed) {
    Block1A();
  } else {
    Block2A();
  }
}
