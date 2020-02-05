//Ada_remoteFXTrigger_RX_NeoPixel
//Remote Effects Trigger Box Receiver
//by John Park & Erin St Blaine
//Modified by Jeffrey Brice for Rex Putnam High School Drumline in the 2020 winter show
//MIT License
#include <FastLED.h>
#include <SPI.h>
#include <RH_RF69.h>
#include <Wire.h>

CRGBArray<NUM_LEDS> leds;

#define NUM_LEDS    128
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define MAX_BRIGHTNESS 255
#define LED 13
#define FASTLED_ALLOW_INTERRUPTS 1
#define FASTLED_INTERRUPT_RETRY_COUNT 4

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

// if (! rf69.recv(buf, &len)) {Serial.println("Receive failed");return;}

    char radiopacket[20] = "Button #";//prep reply message to send

    switch(buf[0]){
      case 'A':
        ledMode(0);
        radiopacket[8] = 'A';
        break;
      case 'B':
        ledMode(1);
        radiopacket[8] = 'B';
        break;
      case 'C':
        ledMode(2);
        radiopacket[8] = 'C';
        break;
      case 'D':
        ledMode(3);
        radiopacket[8] = 'D';
        break;
      case 'E':
        ledMode(4);
        radiopacket[8] = 'E';
        break;
      case 'F':
        ledMode(5);
        radiopacket[8] = 'F';
        break;
      case 'G':
        ledMode(6);
        radiopacket[8] = 'G';
        break;
      case 'H':
        ledMode(7);
        radiopacket[8] = 'H';
        break;
      case 'I':
        ledMode(8);
        radiopacket[8] = 'I';
        break;
      case 'J':
        ledMode(9);
        radiopacket[8] = 'J';
        break;
      case 'K':
        ledMode(10);
        radiopacket[8] = 'K';
        break;
      case 'L':
        ledMode(11);
        radiopacket[8] = 'L'';
        break;
      case 'M':
        ledMode(12);
        radiopacket[8] = 'M';
        break;
      case 'N':
        ledMode(13);
        radiopacket[8] = 'N';
        break;
      case 'O':
        ledMode(14);
        radiopacket[8] = 'O';
        break;
      case 'P':
        ledMode(15);
        radiopacket[8] = 'P';
        break;
      case 'Q':
        ledMode(16);
        radiopacket[8] = 'Q';
        break;
      case 'R':
        ledMode(17);
        radiopacket[8] = 'R';
        break;
      case 'S':
        ledMode(18);
        radiopacket[8] = 'S';
        break;
      case 'T':
        ledMode(19);
        radiopacket[8] = 'T';
        break;
      case 'U':
        ledMode(20);
        radiopacket[8] = 'U';
        break;
      case 'V':
        ledMode(21);
        radiopacket[8] = 'V';
        break;
      case 'W':
        ledMode(22);
        radiopacket[8] = 'W';
        break;
      case 'X':
        ledMode(23);
        radiopacket[8] = 'X';
        break;
      case 'Y':
        ledMode(24);
        radiopacket[8] = 'Y';
        break;
      case 'Z':
        ledMode(25);
        radiopacket[8] = 'Z';
        break;
      default:
        ledMode(0);
        radiopacket[8] = 'A';
        break;
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
void PowerOnBlink() {
  Solid(0,255,200);delay(100);
  Solid(0,0,200);delay(100);
  Solid(0,255,200); delay(100);
  Solid(0,0,0);delay(100);
  Solid(400,255,200); delay(100);
  Solid(0,0,0);
}

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
