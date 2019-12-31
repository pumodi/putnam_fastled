//Ada_remoteFXTrigger_RX_NeoPixel
//Remote Effects Trigger Box Receiver
//by John Park & Erin St Blaine
//Edited by Jeffrey Brice
//
// Button box receiver with NeoPixels using FastLED
//
//
//MIT License
#define FASTLED_ALLOW_INTERRUPTS 1
#define FASTLED_INTERRUPT_RETRY_COUNT 4

#include <FastLED.h>

#define LED_PIN  12
#define NUM_LEDS    256    
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGBArray<NUM_LEDS> leds;

#include <SPI.h>
#include <RH_RF69.h>
#include <Wire.h>

#define LED 13

/********** NeoPixel Setup *************/

#define UPDATES_PER_SECOND 100
CRGBPalette16 currentPalette( CRGB::Black);
CRGBPalette16 targetPalette( PartyColors_p );
TBlendType    currentBlending;

int SPEEDO = 25;          
int STEPS = 20;         
int HUE = 200;    // starting color          
int SATURATION = 255;          
int BRIGHTNESS = 200; 
int CURRENTMODE = 0;

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
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
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
  if (rf69.waitAvailableTimeout(1000)) {
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
      radiopacket[8] = 'P';CURRENTMODE = 15;  
    }
         else if (buf[0]=='Q'){ //the letter sent from the button
      ledMode(16);
      radiopacket[8] = 'Q';CURRENTMODE = 16;
    }
         else if (buf[0]=='R'){ //the letter sent from the button
      ledMode(17);
      radiopacket[8] = 'R';CURRENTMODE = 17;
    }
      else if (buf[0]=='S'){ //the letter sent from the button
      ledMode(18);
      radiopacket[8] = 'S';CURRENTMODE = 18;
    }
         else if (buf[0]=='T'){ //the letter sent from the button
      ledMode(19);
      radiopacket[8] = 'T';CURRENTMODE = 19;
    }
         else if (buf[0]=='Z'){ //the letter sent from the button
      ledMode(20);
      radiopacket[8] = 'Z';CURRENTMODE = 20;
    }
    digitalWrite(LED, LOW);
  }
}


void ledMode(int i) {
  switch(i){
    case 0: HUE=0; SATURATION=255; BRIGHTNESS=200; Solid();    // red
            break;
    case 1: HUE=40; SATURATION=255; BRIGHTNESS=200; Solid();   // gold
            break;
    case 2: HUE=100; SATURATION=255; BRIGHTNESS=200; Solid();    // green
            break;
    case 3: HUE=140; SATURATION=255; BRIGHTNESS=200; Solid();   // Blue   
            break;
    case 4: HUE=180; SATURATION=255; BRIGHTNESS=200; Solid();    // purple
            break;
    case 5: HUE=220; SATURATION=255; BRIGHTNESS=200; Solid();     // pink
            break;
    case 6: HUE=0; SATURATION=0; BRIGHTNESS=200; Solid();     // white
            break;
    case 7: HUE=0; BRIGHTNESS=0; Solid();     // off
            break;
    case 8: HUE=0; SATURATION=255; BRIGHTNESS=200; Gradient();    // red
            break;
    case 9: HUE=40; SATURATION=255; BRIGHTNESS=200; Gradient();     // gold
            break;
    case 10: HUE=100; SATURATION=255; BRIGHTNESS=200; Gradient();    // green
            break;
    case 11: HUE=140; SATURATION=255; BRIGHTNESS=200; Gradient();   // blue
            break;
    case 12:HUE=180; SATURATION=255; BRIGHTNESS=200; Gradient();   // purple
            break;
    case 13:HUE=220; SATURATION=255; BRIGHTNESS=200; Gradient();     // pink
            break;
    case 14:HUE=160; SATURATION=50; BRIGHTNESS=200; Gradient();      // white
            break;
    case 15:Twinkle(0xff, 0, 0, 10, 100, false);// Twinkle
            break;
    case 16:Breath(0, 5);//Breath
            break;
    case 17:RunningLights(0xff,0xff,0x00, 50);//Running Lights
            break;
    case 20:HUE=0; BRIGHTNESS=0; Solid();   // off
            break;
  }
}

// GRADIENT --------------------------------------------------------------
void Gradient()
{
  SetupGradientPalette();

  static uint8_t startIndex = 0;
  startIndex = startIndex + 1;  // motion speed
  FillLEDsFromPaletteColors( startIndex);
  FastLED.show();
  FastLED.delay(SPEEDO);
}

// SOLID ----------------------------------------------------
void Solid()
{
   fill_solid(leds, NUM_LEDS, CHSV(HUE, SATURATION, BRIGHTNESS)); 
   FastLED.show(); 
}

// Animations --------------------------------------------------
void Twinkle(byte red, byte green, byte blue, int Count, int SpeedDelay, boolean OnlyOne) {
  setAll(0,0,0);
  
  for (int i=0; i<Count; i++) {
    if (CURRENTMODE !=15) break;
     setPixel(random(NUM_LEDS),red,green,blue);
     FastLED.show();
     delay(SpeedDelay);
     if(OnlyOne) { 
       setAll(0,0,0); 
     }
   }
  
  delay(SpeedDelay);
}

void Breath(int BreathBrightness, int z) { 
  for(int i = 0; i > -1; i = i+z){
    if (CURRENTMODE !=16) break;
    if(i == 250) {
      z = -2;
    }
    HUE=0; SATURATION=255; BRIGHTNESS=BreathBrightness; Solid(); 
    BreathBrightness = BreathBrightness + z;
  }
}

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  
  for(int j=0; j<NUM_LEDS*2; j++)
  {
     if (CURRENTMODE != 17) break;
     if (CURRENTMODE != 17) return;
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
      
      FastLED.show();
      if (CURRENTMODE != 17) break;
      if (CURRENTMODE != 17) return;
      delay(WaveDelay);
  }
}

void PowerOnBlink() {
  HUE=0; SATURATION=255; BRIGHTNESS=200; Solid(); 
  delay(150);
  HUE=0; BRIGHTNESS=0; Solid();
  delay(150);
  HUE=200; SATURATION=255; BRIGHTNESS=200; Solid(); 
  delay(150);
  HUE=0; BRIGHTNESS=0; Solid();
  delay(150);
  HUE=400; SATURATION=255; BRIGHTNESS=200; Solid(); 
  delay(150);
  HUE=0; BRIGHTNESS=0; Solid();
}

// Utility Functions

void SetupGradientPalette()
{
  CRGB light = CHSV( HUE + 25, SATURATION - 20, BRIGHTNESS);
  CRGB dark  = CHSV( HUE, SATURATION - 15, BRIGHTNESS);
  CRGB medium = CHSV ( HUE - 25, SATURATION, BRIGHTNESS);
  
  currentPalette = CRGBPalette16( 
    light,  light,  light,  light,
    medium, medium, medium,  medium,
    dark,  dark,  dark,  dark,
    medium, medium, medium,  medium );
}

void FillLEDsFromPaletteColors( uint8_t colorIndex)
{
  uint8_t brightness = BRIGHTNESS;
  
  for( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette( currentPalette, colorIndex, brightness, currentBlending);
    colorIndex += STEPS;
  }
}

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

void setAll(byte red, byte green, byte blue) {
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  FastLED.show();
}
