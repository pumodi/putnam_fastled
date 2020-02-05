//Ada_remoteFXTrigger_RX_NeoPixel
//Remote Effects Trigger Box Receiver
//by John Park & Erin St Blaine
//Modified by Jeffrey Brice for Rex Putnam High School Drumline in the 2020 winter show

//MIT License
#define FASTLED_ALLOW_INTERRUPTS 1
#define FASTLED_INTERRUPT_RETRY_COUNT 4

#include <FastLED.h>

#define NUM_LEDS    128
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define MAX_BRIGHTNESS 255

CRGBArray<NUM_LEDS> leds;

#include <SPI.h>
#include <RH_RF69.h>
#include <Wire.h>

#define LED 13

/********** NeoPixel Setup *************/

#define UPDATES_PER_SECOND 1000
CRGBPalette16 currentPalette( CRGB::Black);
CRGBPalette16 targetPalette( PartyColors_p );
TBlendType    currentBlending;

int HUE = 200;    // starting color
int SATURATION = 255;
int BRIGHTNESS = 200;

/*************Variables for Loop Aniamtions*****************/

int fade_k = 255;
int breath_i = 0;
int breath_z = 2;
int BreathBrightness = 0;
unsigned long time_now = 0;

/************ Radio Setup ***************/

// Change to 434.0 or other frequency, must match RX's freq!
#define RF69_FREQ 915.0

  #define RFM69_CS      8
  #define RFM69_INT     3
  #define RFM69_RST     4

uint8_t buf[RH_RF69_MAX_MESSAGE_LEN];

// Singleton instance of the radio driver
RH_RF69 rf69(RFM69_CS, RFM69_INT);

bool oldState = HIGH;

void setup() {
  delay( 1000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, 12, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, 11, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, 10, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, 9, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.addLeds<LED_TYPE, 13, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );
  pinMode(LED, OUTPUT);

  pinMode(RFM69_RST, OUTPUT);
  digitalWrite(RFM69_RST, LOW);

  Serial.println("Feather RFM69 RX/TX Test!");

  // manual reset
  digitalWrite(RFM69_RST, HIGH);
  delay(10);
  digitalWrite(RFM69_RST, LOW);
  delay(10);

  if (!rf69.init()) {
    Serial.println("RFM69 radio init failed");
    while (1);
  }
  Serial.println("RFM69 radio init OK!");

  if (!rf69.setFrequency(RF69_FREQ)) {
    Serial.println("setFrequency failed");
  }

  rf69.setTxPower(14, true);

  // The encryption key has to be the same as the one in the server
  uint8_t key[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08,
                    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
  rf69.setEncryptionKey(key);

  pinMode(LED, OUTPUT);

  Serial.print("RFM69 radio @");  Serial.print((int)RF69_FREQ);  Serial.println(" MHz");

  PowerOnBlink();  //So the lights come on upon startup, even if the trigger box is off

}

void loop(){
  time_now = millis();
  if (rf69.waitAvailableTimeout(1)) {
    // Should be a message for us now
    uint8_t len = sizeof(buf);

    if (! rf69.recv(buf, &len)) {
      Serial.println("Receive failed");
      return;
    }

    char radiopacket[20] = "Button #";//prep reply message to send

    if (buf[0]=='A'){ //the letter sent from the button
      ledMode(0);
      radiopacket[8] = 'A';
    }
     else if (buf[0]=='B'){ //the letter sent from the button
      ledMode(1);
      radiopacket[8] = 'B';
    }
     else if (buf[0]=='C'){ //the letter sent from the button
      ledMode(2);
       radiopacket[8] = 'C';
    }
     else if (buf[0]=='D'){ //the letter sent from the button
      ledMode(3);
      radiopacket[8] = 'D';
    }
     else if (buf[0]=='E'){ //the letter sent from the button
      ledMode(4);
      radiopacket[8] = 'E';
    }
     else if (buf[0]=='F'){ //the letter sent from the button
      ledMode(5);
       radiopacket[8] = 'F';
    }
     else if (buf[0]=='G'){ //the letter sent from the button
      ledMode(6);
      radiopacket[8] = 'G';
    }
     else if (buf[0]=='H'){ //the letter sent from the button
      ledMode(7);
      radiopacket[8] = 'H';
    }
     else if (buf[0]=='I'){ //the letter sent from the button
      ledMode(8);
       radiopacket[8] = 'I';
    }
     else if (buf[0]=='J'){ //the letter sent from the button
      ledMode(9);
      radiopacket[8] = 'J';
    }
     else if (buf[0]=='K'){ //the letter sent from the button
      ledMode(10);
      radiopacket[8] = 'K';
    }
     else if (buf[0]=='L'){ //the letter sent from the button
      ledMode(11);
       radiopacket[8] = 'L';
    }
     else if (buf[0]=='M'){ //the letter sent from the button
      ledMode(12);
      radiopacket[8] = 'M';
    }
     else if (buf[0]=='N'){ //the letter sent from the button
      ledMode(13);
      radiopacket[8] = 'N';
    }
     else if (buf[0]=='O'){ //the letter sent from the button
      ledMode(14);
      radiopacket[8] = 'O';
    }
     else if (buf[0]=='P'){ //the letter sent from the button
      ledMode(15);
      radiopacket[8] = 'P';
    }
     else if (buf[0]=='Q'){ //the letter sent from the button
      ledMode(16);
      radiopacket[8] = 'Q';
    }
     else if (buf[0]=='R'){ //the letter sent from the button
      ledMode(17);
      radiopacket[8] = 'R';
    }
      else if (buf[0]=='S'){ //the letter sent from the button
      ledMode(18);
      radiopacket[8] = 'S';
    }
     else if (buf[0]=='T'){ //the letter sent from the button
      ledMode(19);
      radiopacket[8] = 'T';
    }
     else if (buf[0]=='U'){ //the letter sent from the button
      ledMode(20);
      radiopacket[8] = 'U';
    }
     else if (buf[0]=='V'){ //the letter sent from the button
      ledMode(21);
      radiopacket[8] = 'V';
    }
     else if (buf[0]=='W'){ //the letter sent from the button
      ledMode(22);
      radiopacket[8] = 'W';
    }
     else if (buf[0]=='X'){ //the letter sent from the button
      ledMode(23);
      radiopacket[8] = 'X';
    }
  }
}

void ledMode(int i) {
  switch(i){
    // Solids
    case 0: Solid(0,255,200);break;// red
    case 1: Solid(40,255,200);break;// gold
    case 2: Solid(100,255,200);break;// green
    case 3: Solid(140,255,200);break;// Blue
    case 4: Solid(180,255,200);break;// purple
    case 5: Solid(220,255,200);break;// pink
    case 6: Solid(0,0,200);break;// white
    case 7: Solid(0,0,0);break;// off

    // Show Events
    case 8: Solid(0,0,0);break;// Show Start. Lights Off
    case 9: FadeIn(0xFF,0xFF,0xFF,50,10);break;// Monolith Powers On
    case 10:Breath();break;// Monolith Pulse and Dim
    case 11:Solid(0,0,0);break; // Snare Solo MS115
    case 12:// Monolith Dim to Increase
    case 13:// Monolith Red Pulse
    case 14:// Monolith Red Sparkle
    case 15:// Monolith Purple Theater Chase
    case 16:Solid(140,255,200);break;// Monolith Solid Blue
    case 17:Solid(100,255,200);break;// Monolith and Snares, Solid Green
    case 18:Solid(100,255,200);break;// Add Basses, remove snares
    case 19:Solid(100,255,200);break;// Add Quads, snares return
    case 20:Solid(40,255,200);break;break;  // Gold on all
    case 21:break;  // n/a
    case 22:Solid(0,0,200);break;// SOLID WHITE
    case 23:Solid(0,0,0);break;// ALL OFF
  }
}

// SOLID ----------------------------------------------------
void Solid(int k_hue, int k_saturation, int k_brightness) {
  HUE = k_hue;
  SATURATION = k_saturation;
  BRIGHTNESS = k_brightness;
   fill_solid(leds, NUM_LEDS, CHSV(HUE, SATURATION, BRIGHTNESS));
   FastLED.show();
}

// Animations --------------------------------------------------
void FadeIn(byte red, byte green, byte blue,delayTime, fade_interval){
  fill_solid(leds, NUM_LEDS, CHSV(0, 255, 255));
  if (BRIGHTNESS < 255) {
    BRIGHTNESS = BRIGHTNESS + fade_interval;
    FastLED.show();
    while(millis() < time_now + delayTime){}
  }
}

void FadeOut(byte red, byte green, byte blue, int delayTime, int fade_interval){
  float r, g, b;
  r = (fade_k/256.0)*red;
  g = (fade_k/256.0)*green;
  b = (fade_k/256.0)*blue;
  setAll(r,g,b);
  showStrip();
  while(millis() < time_now + delayTime){}
}

void Breath(int k_hue, int k_saturation, int delayTime) {
  if (breath_i < 250) {
    BreathBrightness = BreathBrightness + 5;
    breath_i = breath_i + 5;
  }
  else if (breath_i > 250) {
    BreathBrightness = BreathBrightness - breath_z;
    if (BreathBrightness = 0) {
      breath_i = 0;
    }
  }
  Solid(0,255,BreathBrightness);
  while(millis() < time_now + delayTime){}
}

void PowerOnBlink() {
  Solid(0,255,200);delay(100);
  Solid(0,0,200);delay(100);
  Solid(0,255,200); delay(100);
  Solid(0,0,0);delay(100);
  Solid(400,255,200); delay(100);
  Solid(0,0,0);
}

// Utility Functions
void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   showStrip();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}
