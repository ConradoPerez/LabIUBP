#include <Servo.h>
#include <SoftwareSerial.h>

Servo servo_2;
Servo servo_3;

int cuenta_2 = 0;
int pulsact_2 = 0;
int pulsant_2 = 0;

int cuenta_3 = 0;
int pulsact_3 = 0;
int pulsant_3 = 0;

int relay=13;

const byte rxPin = 11;
const byte txPin = 13;

SoftwareSerial miBT(10,11); 

void setup()
{
  Serial.begin(9600); // comunicacion de monitor serial a 9600 bps
  Serial.println("Listo"); // escribe Listo en el monitor
  miBT.begin(9600); // comunicacion serie entre Arduino y el modulo a 9600 bps
  pinMode(relay, OUTPUT);
  servo_2.attach(2, 500, 2500);//comunicación con los servos
  servo_3.attach(3, 500, 2500);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(9600);
  servo_2.write(0);
  servo_3.write(0);

}

void loop()
{
  digitalWrite(relay, HIGH); //encender relé
  if (miBT.available()) // si hay informacion disponible desde modulo
  Serial.write(miBT.read()); // lee Bluetooth y envia a monitor serial de Arduino
  pulsact_2 = digitalRead(4);
  if ((pulsact_2 == 1) && (pulsant_2 == 0)) {
    cuenta_2 = cuenta_2 + 1;
  }
  pulsant_2 = pulsact_2;

  if (cuenta_2 == 1) {
    servo_2.write(90);
    //digitalWrite(8,HIGH);
    delay(2500); 
    servo_2.write(0);
    cuenta_2 = 0; 
    //digitalWrite(8,LOW);
  }
  
  pulsact_3 = digitalRead(5);
  if ((pulsact_3 == 1) && (pulsant_3 == 0)) {
    cuenta_3 = cuenta_3 + 1;
  }
  pulsant_3 = pulsact_3;

  if (cuenta_3 == 1) {
    servo_3.write(90); 
    //digitalWrite(9,HIGH);
    delay(2500);
    servo_3.write(0); 
    //digitalWrite(9,LOW);
    cuenta_3 = 0;
  }

}
