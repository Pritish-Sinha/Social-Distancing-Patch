//Created by Pritish SInha for College Project 2021
//MIT License

//Copyright (c) 2021 Pritish Sinha

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#define buzzer 8
#define PIN 7
#define haha 10
#define trig_pin 6
#define echo_pin 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(60, PIN, NEO_GRB + NEO_KHZ800);

int t = 0;
long duration;
float cm;

void setup() {
  Serial.begin(115200);
  pinMode(buzzer,OUTPUT);
  pinMode(haha,INPUT);
  pinMode(trig_pin, OUTPUT); 
  pinMode(echo_pin, INPUT); 
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    duration = pulseIn(echo_pin, HIGH);
    cm = duration * 0.034 /2;
    digitalWrite(haha,HIGH);
    int montion = digitalRead(haha);
    delay(1000);
  if (cm < 100) {
    Serial.print(cm);
    if(montion == 1){
          Serial.print("Danger");
          tone(buzzer,800,40);
          while(1){
          colorWipe(strip.Color(255, 0, 0), 800); // Red
          break;
          }
    }
    Serial.print("Reading");
    colorWipe(strip.Color(0, 255, 0), 1); // Green
    }
    else if(cm >=100 && cm <300){
        Serial.print(cm);
         while(montion == 1){
          Serial.print("Reading");
          theaterChase(strip.Color(255, 255, 0), 800); // White
          break;
          }
          Serial.print("Safe");
          colorWipe(strip.Color(0, 255, 0), 1); // Green
          }
   else{
    Serial.print(cm);
    Serial.print("Safe");
    colorWipe(strip.Color(0, 255, 0), 1); // Green
    }           

}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j=0; j<10; j++) {  //do 10 cycles of chasing
    for (int q=0; q < 3; q++) {
      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, c);    //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}
