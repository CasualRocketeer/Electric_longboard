#include <RF24_config.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(7, 8); // CE, CSN
float olddata=1500;
int buzzer=5;
const byte address[6] = "00001";
unsigned long previousMillis = 0;
Servo esc;
void setup() {
  Serial.begin(9600);
  esc.attach(4,1000,2000);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_HIGH);
  radio.startListening();
}
void loop() {
  float esc_cord;
  if (radio.available()) {
    radio.read(&esc_cord, sizeof(esc_cord));
    esc_cord=map(esc_cord,0,1023,2000,1000);
     while(olddata<esc_cord){
       olddata+=10;
       Serial.println(olddata);
       Serial.print(  "prva");
       esc.write(olddata);
        delay(70);
     }
   while(olddata>esc_cord){
       olddata-=10;
       Serial.println(olddata);
       Serial.print(  "druga");
       esc.write(olddata);
        delay(70);
       }
   olddata=esc_cord;
   delay(100);
  }
}
