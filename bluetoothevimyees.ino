
#include <SPI.h>
#include <RFID.h>
#include <LiquidCrystal_I2C_AvrI2C.h>
LiquidCrystal_I2C_AvrI2C lcd(0x27, 16, 2);
#include <dht11.h>
#include <Servo.h>

int led1 = 2;
int led2 = 3;
int buzzerPin = 4;
int DHT11_pin = 5;
int ledev = 7;

dht11 DHT11_sensor;


RFID rfid(10, 9);

byte kart1[5] = {128, 124, 107, 43, 188};

Servo servoNesnesi;
boolean card1;

void setup()
{
  servoNesnesi.attach(6);  /* Servo motor 9 numarali pine baglandi */
  SPI.begin();
  rfid.init();
  lcd.begin();
  lcd.backlight();
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledev, OUTPUT);
  Serial.begin(9600);
  servoNesnesi.write(57);
}

void loop()
{
  int chk = DHT11_sensor.read(DHT11_pin);
  lcd.setCursor(2, 0);
  lcd.print("Karti okutun!"); //İlk satıra yazalım
  lcd.setCursor(0 , 1);
  lcd.print("(C):");
  lcd.println((float)DHT11_sensor.temperature, 2);
  lcd.setCursor(6 , 1);
  lcd.print("   ");
  lcd.setCursor(9 , 1);
  lcd.print("Nem%:");
  lcd.println((float)DHT11_sensor.humidity, 2);
  digitalWrite(led1, HIGH);

  if (rfid.isCard())
  {


    if (rfid.readCardSerial())
    {
      Serial.print("Kart Bulundu: ");
      Serial.print(rfid.serNum[0]);
      Serial.print(",");
      Serial.print(rfid.serNum[1]);
      Serial.print(",");
      Serial.print(rfid.serNum[2]);
      Serial.print(",");
      Serial.print(rfid.serNum[3]);
      Serial.print(",");
      Serial.println(rfid.serNum[4]);

    }
    for (int i = 1; i < 5; i++)
    {
      if (rfid.serNum[0] == kart1[0] && rfid.serNum[1] == kart1[1] && rfid.serNum[2] == kart1[2] && rfid.serNum[3] == kart1[3] && rfid.serNum[4] == kart1[4])
      {
        card1 = true;
      }
      else {
        card1 = false;
      }
    }
    if (card1 == true)
    {
      lcd.setCursor(2, 0);
      lcd.print("Kart Gecerli!");
      lcd.setCursor(0 , 1);
      lcd.print("(C):");
      lcd.println((float)DHT11_sensor.temperature, 2);
      lcd.setCursor(6 , 1);
      lcd.print("   ");
      lcd.setCursor(9 , 1);
      lcd.print("Nem%:");
      lcd.println((float)DHT11_sensor.humidity, 2);
      delay(800);
      digitalWrite(buzzerPin, HIGH);
      delay(300);
      digitalWrite(buzzerPin, LOW);
      lcd.clear();
      lcd.setCursor(2, 0);
      lcd.print("Onay verildi!");
      lcd.setCursor(0 , 1);
      lcd.print("(C):");
      lcd.println((float)DHT11_sensor.temperature, 2);
      lcd.setCursor(6 , 1);
      lcd.print("   ");
      lcd.setCursor(9 , 1);
      lcd.print("Nem%:");
      lcd.println((float)DHT11_sensor.humidity, 2);
      delay(800);
      lcd.setCursor(2, 0);
      lcd.print("Kapi acildi.");
      lcd.setCursor(0 , 1);
      lcd.print("(C):");
      lcd.println((float)DHT11_sensor.temperature, 2);
      lcd.setCursor(6 , 1);
      lcd.print("   ");
      lcd.setCursor(9 , 1);
      lcd.print("Nem%:");
      lcd.println((float)DHT11_sensor.humidity, 2);
      servoNesnesi.write(87);  /* Motorun mili 100. dereceye donuyor */
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      delay(5000);
      lcd.clear();
      lcd.setCursor(1, 0);
      lcd.print("Kapi kapaniyor.");
      lcd.setCursor(0 , 1);
      lcd.print("(C):");
      lcd.println((float)DHT11_sensor.temperature, 2);
      lcd.setCursor(6 , 1);
      lcd.print("   ");
      lcd.setCursor(9 , 1);
      lcd.print("Nem%:");
      lcd.println((float)DHT11_sensor.humidity, 2);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(500);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(500);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(500);
      digitalWrite(led2, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(500);
      digitalWrite(led2, LOW);
      digitalWrite(buzzerPin, HIGH);
      delay(650);
      digitalWrite(buzzerPin, LOW);
      lcd.clear();
      int chk = DHT11_sensor.read(DHT11_pin);
      lcd.setCursor(2, 0);
      lcd.print("Karti okutun!"); //İlk satıra yazalım
      lcd.setCursor(0 , 1);
      lcd.print("(C):");
      lcd.println((float)DHT11_sensor.temperature, 2);
      lcd.setCursor(6 , 1);
      lcd.print("   ");
      lcd.setCursor(9 , 1);
      lcd.print("Nem%:");
      lcd.println((float)DHT11_sensor.humidity, 2);
      digitalWrite(led1, HIGH);
      servoNesnesi.write(57);
      digitalWrite(ledev, LOW);
    }
    else
    {
      lcd.setCursor(1, 0);
      lcd.print("Kart Gecersiz!");
      digitalWrite(led1, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(led1, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(200);
      digitalWrite(led1, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(200);
      digitalWrite(led1, LOW);
      digitalWrite(buzzerPin, LOW);
      delay(200);
      digitalWrite(led1, HIGH);
      digitalWrite(buzzerPin, HIGH);
      delay(1000);
      digitalWrite(led1, LOW);
      digitalWrite(buzzerPin, LOW);
      lcd.clear();

    }
    rfid.halt();
  }

}
