#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(7, 8); // CE, CSN
int led=10;
const byte address[6] = "00001";
void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(led,OUTPUT);
}
void loop() {
  float esc_cord= analogRead(A0);
  radio.write(&esc_cord, sizeof(esc_cord));
  Serial.println(esc_cord);
  digitalWrite(led,HIGH);
  delay(250);
  radio.write(&esc_cord, sizeof(esc_cord));
  digitalWrite(led,LOW);
  delay(250);
}
