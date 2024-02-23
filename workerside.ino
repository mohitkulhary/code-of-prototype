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
float mq135d = A0;
float mq135a = A1;
float mq4a = A2;
float mq4d = A3;
float mq136a = A6;
float mq136d = A7;

RF24 radio(9, 10);
//const byte address[6] = "00002";

void setup() {
  pinMode(green, OUTPUT);
  pinMode(green1, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(blue1, OUTPUT);
  pinMode(buzz, OUTPUT);
  pinMode(mq4d, INPUT);
  pinMode(mq4a, INPUT);
  pinMode(mq135d, INPUT);
  pinMode(mq135a, INPUT);
  pinMode(mq136d, INPUT);
  pinMode(mq136a, INPUT);


  digitalWrite(green1, LOW);
  digitalWrite(blue1, LOW);


  Serial.begin(9600);

  radio.begin();
  //radio.openWritingPipe(0xF0F0F0F0E1LL);
  //radio.stopListening();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  radio.startListening();
  radio.setPALevel(RF24_PA_MAX);

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
  int p;
  radio.stopListening();
  radio.openReadingPipe(1, 0xF0F0F0F0E1LL);
  radio.startListening();
  if(radio.available()){
    radio.read(&p,sizeof(p));
    if((p==100)||(p==1)){
      lcd.clear();
      lcd.print("evacuate");
   
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
    radio.openWritingPipe(0xF0F0F0F0E1LL);
 radio.stopListening();
      delay(1000);
      radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.stopListening();
    }
  }
  else{
    radio.openWritingPipe(0xF0F0F0F0E1LL);
  radio.stopListening();
    
    mq135d = digitalRead(A0);
    mq135a = analogRead(A1);
    
    mq4a = analogRead(A2);
    
    mq4d = digitalRead(A3);
    mq136a = analogRead(A6);
   
    mq136d = digitalRead(A7);

      float voltage4a = mq4a * (5.0 / 1024.0) * 5.0;
      float voltage5a = mq135a * (5.0 / 1024.0) * 5.0;
      float voltage6a = mq136a * (5.0 / 1024.0) * 5.0;
       obj.mq4a = (voltage4a - 0.4) * 2.0;
       obj.mq135a = (voltage5a - 0.4) * 2.0;
       obj.mq136a = (voltage6a - 0.4) * 2.0;
       mq4a = (voltage4a - 0.4) * 2.0;
       mq135a = (voltage5a - 0.4) * 2.0;
       mq136a = (voltage6a - 0.4) * 2.0;
      Serial.println(mq4a);
      Serial.println(mq135a);
      Serial.println(mq136a);
   

    //transmitt data
    radio.write(&obj, sizeof(obj));
    //radio.write(&mq135a, sizeof(mq135a));
    //radio.write(&mq136a, sizeof(mq136a));

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
