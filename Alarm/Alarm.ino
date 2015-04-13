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

bool armed = false;

void setup() {
  Serial.begin(115200);
  lcd.begin(16, 2);  // set up the LCD's number of rows and columns:

  buttons.setDefaultButtonConfig(1, 1);

  buttons.addButton(SET_ALARM, 8);
  buttons.addButton(REED, 5, 1, 0);

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

void entryDelay() {
  Serial.println("Entry delay");
  for (int i = 0; i < 15; i++) {
    digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
    delay(1000);
  }
  digitalWrite(BUZZER_PIN, LOW);
}

void exitDelay() {
  Serial.println("Exit delay");
  for (int i = 0; i < 15; i++) {
    digitalWrite(BUZZER_PIN, !digitalRead(BUZZER_PIN));
    delay(1000);
  }
  digitalWrite(BUZZER_PIN, LOW);
}

void soundAlarm() {
  entryDelay();
  Serial.println("Sound alarm");
  digitalWrite(SIREN_PIN, HIGH);
  lcd.clear();
  lcd.print("Intruder!");
  lcd.setCursor(0, 1);
  lcd.print("Scan Tag To Reset");
  armed = false;
}

void arm(bool a) {
  armed = a;
  Serial.print("Armed: ");
  Serial.println(armed);
  if (armed) {
    lcd.clear();
    lcd.print("Arming Alarm!");
    lcd.setCursor(0, 1);
    lcd.print("Please Exit!");
    digitalWrite(RED_LED_PIN, HIGH);
    exitDelay();
  } else {
    lcd.clear();
    lcd.print("Disarmed!");
  }
}

void buttonHandler(buttonid_t id, uint32_t time) {
  if (id == SET_ALARM) arm(!armed);
}

void loop() {
  buttons.poll();

  if (armed && buttons.getButtonState(REED)) {
    soundAlarm();
  }
}
