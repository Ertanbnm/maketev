#include <LiquidCrystal_I2C_AvrI2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
LiquidCrystal_I2C_AvrI2C lcd (0x27, 16, 2);
Servo myservomotor;
SoftwareSerial akiiliev(0, 1);
//////////////////////////////////////////////////
char deger;
int role = 2;
int trig = 13;
int echo = 12;
int buzzer = 3;
int ledkirmizi = 4;
int ledyesil = 5;
int  sure  = 0;
int  mesafe = 0;
///////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  myservomotor.attach(6);
  akiiliev.begin(9600);
  myservomotor.write(54);
  digitalWrite(role, 1);
  digitalWrite(ledkirmizi,1);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(role, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledkirmizi, OUTPUT);
  pinMode(ledyesil, OUTPUT);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Hosgeldiniz!");
  lcd.setCursor(0, 1);
  lcd.print("Akilli Ev (Beta)");
  
}

void loop() {

  if (deger == '5') {
    akiiliev.println("Alarm Kuruldu!");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Hosgeldiniz!");
    lcd.setCursor(1, 1);
    lcd.print("Alarm Kuruldu!");
    myservomotor.write(54);
    digitalWrite(ledkirmizi,1);
    digitalWrite(ledyesil,0);
    Serial.println(mesafe);

    if ( mesafe > 27)
      digitalWrite(3, 1);
    myservomotor.write(54);
    delay(1500);

  }

  digitalWrite(trig , 1);
  delayMicroseconds(1000);
  digitalWrite(trig, 0);

  sure = pulseIn(echo , 1);
  mesafe = (sure / 2) / 28.5;


  if (akiiliev.available())
  {
    deger = akiiliev.read();

    if (deger == '1' ) {
      akiiliev.println("Kapi Acildi");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(1, 1);
      lcd.print("Kapi Acildi!");
      digitalWrite(ledkirmizi,0);
      digitalWrite(ledyesil,1);
      myservomotor.write(73);
    }

    if (deger == '2') {
      akiiliev.println("Kapi Kapandi");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(1, 1);
      lcd.print("Kapi Kapandi!");
      digitalWrite(ledkirmizi,1);
      digitalWrite(ledyesil,0);
      myservomotor.write(54);
    }

    if (deger == '6') {
      akiiliev.println("Alarm Kapandi!");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(1, 1);
      lcd.print("Alarm Kapandi!");
      digitalWrite(3, 0);
    }

    if (deger == '7') {
      akiiliev.println("Havalandırma Acildi!");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(0, 1);
      lcd.print("Hvlndrma Acildi");
      digitalWrite(role, 0);
    }

    if (deger == '8') {
      akiiliev.println("Hvlndrma Kapandi");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(0, 1);
      lcd.print("Hvlndrma Kapandi");
      digitalWrite(role, 1);
    }
  }

  delay(100);
}
