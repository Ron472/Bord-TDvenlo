void serialPatternSelection(){
  if (Serial.available() > 0) {
    byte newPatternNumber = Serial.parseInt();

    //Kijken of het nieuwe patroonnummer toegelaten wordt:
    if (newPatternNumber < ARRAY_SIZE(gPatterns)) {
      gCurrentPatternNumber = newPatternNumber;
      patternInit = 1;
    }else{
      Serial.println("Ongeldig patroon!");
      //gCurrentPatternNumber = random(0, ARRAY_SIZE(gPatterns));
      //patternInit = 1;
    }
    Serial.println("Patroon: " + String(gCurrentPatternNumber));
  }
}

void ledTest(int del) {
  //Rood:
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(255, 0, 0);
  }
  FastLED.show();
  delay(del);

  //Groen:
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 255, 0);
  }
  FastLED.show();
  delay(del);

  //Blauw:
  for (byte i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 255);
  }
  FastLED.show();
  delay(del);
}

void startTransition(){
  gStage = 1;
}

void modeTransition() {
  byte offValue = 4; //Hoeveelheid stappen tussen aan en uit

  if (gStage == 3) {
    byte sumON  = 0;
    byte sumOFF = 0;
    for (byte i = 0; i < NUM_LEDS; i++) {
      if (gMem[i] > 0 && gMem[i] < offValue) gMem[i]--;
      if (gMem[i] == offValue) sumOFF++;
      if (gMem[i] == 0) sumON++;
    }
    if (sumOFF > 0) {
      byte rnd = 0;
      while (true) {
        rnd = random(0, NUM_LEDS);
        if (gMem[rnd] == offValue) break;
      }
      gMem[rnd]--;
    }
    //Serial.println("St:" + String(gStage) + "\tON: " + String(sumON) + "\tOFF: " + String(sumOFF));
    if (sumON == NUM_LEDS) gStage = 0;
  }

  if (gStage == 2) {
    nextPattern();
    gStage = 3;
  }

  if (gStage == 1) {
    byte sumON  = 0;
    byte sumOFF = 0;
    for (byte i = 0; i < NUM_LEDS; i++) {
      if (gMem[i] > 0 && gMem[i] < offValue) gMem[i]++;
      if (gMem[i] == offValue) sumOFF++;
      if (gMem[i] == 0) sumON++;
    }
    for(byte n = 0; n<3;n++){
      if (sumON > 0) {
        byte rnd = 0;
        while (true) {
          rnd = random(0, NUM_LEDS);
          if (gMem[rnd] == 0) break;
        }
        sumON--;
        gMem[rnd]++;
      }
    }
    //Serial.println("St:" + String(gStage) + "\tON: " + String(sumON) + "\tOFF: " + String(sumOFF));
    if (sumOFF == NUM_LEDS) gStage = 2;
  }

  for (byte i = 0; i < NUM_LEDS; i++) {
    if (gMem[i] > 0) {
      fadeLedToWhite(i, min(gMem[i] * (256/offValue), 255));
    }
  }
}

void nextPattern()
{
  //Incrementeel een nieuw patroon kiezen:
  //gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);

  //Willekeurig een nieuw patroon kiezen:
  byte newPattern = 0;
  while (true) {
    newPattern = random(0, ARRAY_SIZE( gPatterns));
    if (newPattern != gCurrentPatternNumber) {
      gCurrentPatternNumber = newPattern;
      break;
    }
  }

  Serial.println("Patroon: " + String(gCurrentPatternNumber));
  patternInit = 1; //Flag zodat patronen weten dat ze zojuist (opnieuw) gestart zijn
}
