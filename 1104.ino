#include <LiquidCrystal_I2C_AvrI2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
LiquidCrystal_I2C_AvrI2C lcd (0x27, 16, 2);
Servo myservomotor;
SoftwareSerial myBluetooth(0, 1);
char deger;
int role = 2;
int trig = 13;
int echo = 12;
int buzzer = 3;
int  sure  = 0;
int  mesafe = 0;
void setup() {
  Serial.begin(9600);
  myservomotor.attach(6);
  myBluetooth.begin(9600);
  myservomotor.write(54);
  digitalWrite(role, 1);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(role, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Hosgeldiniz!");
  lcd.setCursor(0, 1);
  lcd.print("Akilli Ev (Beta)");
}

void loop() {

  if (deger == '5') {
    myBluetooth.println("Alarm Kuruldu!");
    lcd.clear();
    lcd.setCursor(1, 0);
    lcd.print("Hosgeldiniz!");
    lcd.setCursor(1, 1);
    lcd.print("Alarm Kuruldu!");
    myservomotor.write(54);
    Serial.println(mesafe);

    if ( mesafe <= 20)
      digitalWrite(3, 1);
    myservomotor.write(54);
    delay(1500);

  }

  digitalWrite(trig , HIGH);
  delayMicroseconds(1000);
  digitalWrite(trig, LOW);

  sure = pulseIn(echo , HIGH);
  mesafe = (sure / 2) / 28.5;


  if (myBluetooth.available())
  {
    deger = myBluetooth.read();

    if (deger == '1' ) {
      myBluetooth.println("Kapi Acildi");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(1, 1);
      lcd.print("Kapi Acildi!");
      myservomotor.write(73);
    }

    if (deger == '2') {
      myBluetooth.println("Kapi Kapandi");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(1, 1);
      lcd.print("Kapi Kapandi!");
      myservomotor.write(54);
    }

    if (deger == '6') {
      myBluetooth.println("Alarm Kapandi!");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(1, 1);
      lcd.print("Alarm Kapandi!");
      digitalWrite(3, 0);
    }

    if (deger == '7') {
      myBluetooth.println("Havalandırma Acildi!");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(0, 1);
      lcd.print("Hvlndrma Acildi");
      digitalWrite(role, 0);
    }

    if (deger == '8') {
      myBluetooth.println("Hvlndrma Kapandi");
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
