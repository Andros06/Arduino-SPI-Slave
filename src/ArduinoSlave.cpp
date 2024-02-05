#include <Arduino.h>
#include <SPI.h>

char str[50];
volatile byte i;
volatile bool pin;

void setup() {

  Serial.begin(115200); //set "baud rate til 115200"
  Serial.println("Hello I'm SPI UNO Slave");
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  i = 0;
  pin = false;
  SPI.attachInterrupt();
}

void loop() {
  
  static int count;
  if (pin){
    pin = false;
    if(count++ < 5){
      Serial.print(count);
      Serial.println(" : ");

      Serial.println(str);
      if(count == 5){
        delay(1000);
        Serial.println("The end data");
      }
      delay(1000);
      i = 0; // reset to zero
    }
  }
}


ISR(SPI_STC_vect){
  char c = SPDR;
  if(i < sizeof(str)){
    str[i++] = c;
    if( (c == '\r') || (c == '\n') || (c=='\0') ){
      pin = true;
    } 
  }
}

