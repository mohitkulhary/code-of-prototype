#include <Wire.h>
#include <SPI.h>
#include <RF24.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define green 2
#define green1 3
#define blue 4
#define blue1 5
#define buzz 6
#define buzzn 7
int btn = A0;
float data;
int e = 100;
RF24 radio(9, 10);
//const byte address[6] = "00002";
int q=1;

void setup() {
  pinMode(green, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(blue1, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(buzzn, OUTPUT);
  pinMode(btn, INPUT);

  digitalWrite(green1, LOW);
  digitalWrite(blue1, LOW);
  digitalWrite(buzzn, LOW);


  Serial.begin(9600);

  radio.begin();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("  Toxic Gasses");
  lcd.setCursor(0, 1);
  lcd.print("Monitring System");
  delay(3000);
}
struct SensorData {
    float mq4a;
    float mq135a;
    float mq136a;
    // Add more sensor variables as needed
};

SensorData obj;

void loop() {
  radio.write(&q, sizeof(q));
  btn = analogRead(A0);
  if (btn > 950) {
    lcd.clear();
    lcd.print("SIGNAL SENDED");
    radio.openWritingPipe(0xF0F0F0F0E1LL);
    radio.stopListening();
    radio.write(&e, sizeof(e));
    Serial.println(e);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(50);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(50);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(50);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(50);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(50);
    digitalWrite(buzz, HIGH);
    delay(100);
    digitalWrite(buzz, LOW);
    delay(50);
    radio.startListening();
    radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  }
  else {

    radio.startListening();
    while (!radio.available()) {
      lcd.clear();
      lcd.print("SIGNAL LOST");
      digitalWrite(blue, LOW);
      digitalWrite(green, LOW);
      delay(200);
    }


    radio.read(&obj, sizeof(obj));
    float mq4a = obj.mq4a;
    float mq135a= obj.mq135a;
    float mq136a= obj.mq136a;
    Serial.println(mq4a);
    Serial.println(mq135a);
    Serial.println(mq136a);
    
    
    lcd.clear();
    lcd.print(data);
     if ((mq4a > 20) || (mq135a > 20) || (mq136a > 20)) {
        digitalWrite(buzz, HIGH);
        digitalWrite(blue, HIGH);
        digitalWrite(green, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Enviournment");
        lcd.setCursor(0, 1);
        lcd.print("  Not Suitable");
        delay(1000);
      }
      else {
        digitalWrite(buzz, LOW);
        digitalWrite(blue, LOW);
        digitalWrite(green, HIGH);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("  Enviournment");
        lcd.setCursor(0, 1);
        lcd.print("    Suitable");
        delay(1000);
      }
  }
}
