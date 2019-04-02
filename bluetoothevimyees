#include <SoftwareSerial.h>
#include <Servo.h>

 Servo myservomotor; 
 SoftwareSerial myBluetooth(0, 1);
 char deger;

void setup() {
Serial.begin(9600);
myservomotor.attach(6);
myBluetooth.begin(9600);
}

void loop() {                  

   if (myBluetooth.available())
   {
deger=myBluetooth.read();

if(deger == '3'){
myBluetooth.println("Kapi Acildi");
     myservomotor.write(87);
        }
   }
if (deger == '4'){
myBluetooth.println("Kapi Kapandi");
myservomotor.write(57);
      }
   delay(100);
}
