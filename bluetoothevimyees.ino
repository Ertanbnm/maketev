#include <LiquidCrystal_I2C_AvrI2C.h>
#include <SoftwareSerial.h>
#include <Servo.h>
LiquidCrystal_I2C_AvrI2C lcd (0x27, 16, 2);
Servo myservomotor;
SoftwareSerial myBluetooth(0, 1);
char deger;
int role = 2;

void setup() {
  Serial.begin(9600);
  myservomotor.attach(6);
  myBluetooth.begin(9600);
  myservomotor.write(54);
  digitalWrite(role, 1);
  pinMode(role, OUTPUT);
  lcd.begin();
  lcd.setCursor(0, 0);
  lcd.print("Hosgeldiniz!");
  lcd.setCursor(0, 1);
  lcd.print("Akilli Ev (Beta)");
}

void loop() {

  if (myBluetooth.available())
  {
    deger = myBluetooth.read();

    if (deger == '1') {
      myBluetooth.println("Kapi Acildi");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(1, 1);
      lcd.print("Kapi Acildi!");
      myservomotor.write(81);
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

    if (deger == '7') {
      myBluetooth.println("Havalandırma Acildi!");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(0, 1);
      lcd.print("Hvlndmra Acildi");
      digitalWrite(role, 0);
    }

    if (deger == '8') {
      myBluetooth.println("Kapi Kapandi");
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Hosgeldiniz!");
      lcd.setCursor(0, 1);
      lcd.print("Hvlndmra Kapandi");
      digitalWrite(role, 1);
    }
  }
  delay(100);
}
