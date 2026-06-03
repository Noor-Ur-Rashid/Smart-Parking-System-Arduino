#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// ---------- LCD ----------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- RFID ----------
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);

// ---------- SERVO ----------
Servo gateServo;
const int servoPin = 6;

// ---------- ULTRASONIC ----------
const int trig1 = 2;
const int echo1 = 3;

const int trig2 = 4;
const int echo2 = 5;

// ---------- LED ----------
const int s1Green = 7;
const int s1Red = 8;

const int s2Green = A0;
const int s2Red = A1;

// ---------- RFID UID ----------
byte authorizedUID[] = {0x63, 0x41, 0xFB, 0x03};
const byte uidLength = 4;

// ---------- VARIABLES ----------
float dist1, dist2;
bool slot1Free, slot2Free;

// ---------- SETUP ----------
void setup() {
  Serial.begin(9600);

  SPI.begin();
  rfid.PCD_Init();

  // LCD
  lcd.init();
  lcd.backlight();

  // Servo
  gateServo.attach(servoPin);
  gateServo.write(0);

  // Pins
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  pinMode(s1Green, OUTPUT);
  pinMode(s1Red, OUTPUT);
  pinMode(s2Green, OUTPUT);
  pinMode(s2Red, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Smart Parking");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  lcd.clear();
}

// ---------- LOOP ----------
void loop() {

  // Read distances
  dist1 = getDistance(trig1, echo1);
  dist2 = getDistance(trig2, echo2);

  // Slot logic
  slot1Free = (dist1 > 10);
  slot2Free = (dist2 > 10);

  // LED control
  digitalWrite(s1Green, slot1Free);
  digitalWrite(s1Red, !slot1Free);

  digitalWrite(s2Green, slot2Free);
  digitalWrite(s2Red, !slot2Free);

  int availableSlots = slot1Free + slot2Free;

  // LCD display
  lcd.setCursor(0, 0);
  lcd.print("S1:");
  lcd.print(slot1Free ? "E" : "F");
  lcd.print(" S2:");
  lcd.print(slot2Free ? "E" : "F");
  lcd.print(" ");

  lcd.setCursor(0, 1);
  lcd.print("Avail:");
  lcd.print(availableSlots);
  lcd.print("   ");

  // ---------- RFID CHECK ----------
  if (!rfid.PICC_IsNewCardPresent()) return;
  if (!rfid.PICC_ReadCardSerial()) return;

  Serial.println("Card Scanned");
  Serial.print("UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(rfid.uid.uidByte[i], HEX);
    Serial.print(" ");
  }
  Serial.println();

  if (isAuthorized(rfid.uid.uidByte, rfid.uid.size)) {

    if (availableSlots > 0) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Access Granted");
      lcd.setCursor(0, 1);
      lcd.print("Opening Gate");

      openGate();
    } else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Parking FULL");
      lcd.setCursor(0, 1);
      lcd.print("Access Denied");
      delay(2000);
    }

  } else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Invalid Card");
    lcd.setCursor(0, 1);
    lcd.print("Access Denied");
    delay(2000);
  }

  lcd.clear();

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// ---------- FUNCTIONS ----------

float getDistance(int trig, int echo) {
  long duration;
  float distance;

  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH, 30000);

  if (duration == 0) return 999;

  distance = duration * 0.034 / 2;
  return distance;
}

bool isAuthorized(byte *uid, byte size) {
  if (size != uidLength) return false;

  for (byte i = 0; i < uidLength; i++) {
    if (uid[i] != authorizedUID[i]) return false;
  }
  return true;
}

void openGate() {
  gateServo.write(90);
  delay(4000);
  gateServo.write(0);
}