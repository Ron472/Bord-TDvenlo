//Arduino Leonardo

#include "FastLED.h"

FASTLED_USING_NAMESPACE

#if defined(FASTLED_VERSION) && (FASTLED_VERSION < 3001000)
#warning "Requires FastLED 3.1 or later; check github for latest code."
#endif

#define DATA_PIN    4
#define NUM_LEDS    64   //20 horizontaal   12 verticaal
#define BRIGHTNESS         255
#define FRAMES_PER_SECOND  30
CRGB leds[NUM_LEDS];

void setup() {
  delay(1000); //Tijd om te herprogrammeren (in case you fucked up)
  Serial.begin(9600);
  Serial.setTimeout(5); //Timeout van Serial.parseInt() functie
  
  //Welk bord wordt er gebruikt??
  pinMode(2, INPUT_PULLUP);
  delay(5);
  
  if (digitalRead(2)==HIGH) { 
    //Echte TD bord:
    Serial.println("Grote TD bord is verbonden");
    FastLED.addLeds<WS2811, DATA_PIN, BRG>(leds, NUM_LEDS + 3).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS); 
  } else { 
    //Mini TD bord: (Pin 2 aan GND)
    Serial.println("Mini TD bord is verbonden");
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS + 3).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(100);
  }
  FastLED.setDither(0);

  //ledTest(500); //De kleuren rood, groen en blauw doorlopen. Elk 500ms
}

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = {patroon0, patroon1, patroon2, patroon3, patroon4, patroon5, patroon6, patroon7, patroon8};
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gPreviousPatternNumber = 0;

//Geheugen voor overgang tussen de patronen:
byte gStage = 0;
byte gMem[NUM_LEDS];

unsigned long t = 0;
byte patternInit = 1; 
int dir=1; //Patroon richting (1 of -1)

unsigned long frameTsum=0;
int frameN=0;

void loop()
{
  t = millis(); //Tijdstip voor deze iteratie

  serialPatternSelection(); //Via serieel een patroon kiezen

  //Richting van het patroon veranderen bij initialisatie:
  if(patternInit==1){
    dir*=-1;
  }
  //Het huidige patroon uitvoeren:
  gPatterns[gCurrentPatternNumber]();
  patternInit = 0;

  //Start overgang naar nieuw patroon
  EVERY_N_SECONDS( 25 ) {
    startTransition();
  }

  //Overgang uitvoeren
  if (gStage > 0) {
    modeTransition();
  }

  //Leds updaten en frame rate beperken:
  FastLED.show();
  int tFrame=millis()-t;
  delay(max(0,1000/FRAMES_PER_SECOND-tFrame));

  /*/Frames per seconde berekenen:
  frameTsum+=millis()-t;
  frameN++;
  EVERY_N_SECONDS( 1) {
    if(Serial){
    Serial.println("FPS: "+String(1000/(frameTsum/float(frameN))));
    frameTsum=0;
    frameN=0;
    }
  }
  */
  
}




