void patroon4() {
  for (int i = 0; i < NUM_LEDS; i++) {
    //    CRGB c1 = CHSV(t / 40      , 255, max(0, sin8(t / 26 + pos[i][2]) - 170) * 3);
    //    CRGB c2 = CHSV(t / 40 +  85, 255, max(0, sin8(t / 30 + pos[i][2]) - 170) * 3);
    //    CRGB c3 = CHSV(t / 40 + 170, 255, max(0, sin8(t / 35 + pos[i][2]) - 170) * 3);

    CRGB c1 = CHSV(t / 40      , 255, max(0, sin8(sin16(t * 5 / 2) / 150 + pos[i][2]) - 170) * 3);
    CRGB c2 = CHSV(t / 40 +  85, 255, max(0, sin8(sin16(t * 6 / 2) / 150 + pos[i][2]) - 170) * 3);
    CRGB c3 = CHSV(t / 40 + 170, 255, max(0, sin8(sin16(t * 7 / 2) / 150 + pos[i][2]) - 170) * 3);

    leds[i].r = min(255, c1.r + c2.r + c3.r);
    leds[i].g = min(255, c1.g + c2.g + c3.g);
    leds[i].b = min(255, c1.b + c2.b + c3.b);
  }
}

byte P5_fadeComplete = 0;
byte P5_fadeGoal = 0;
byte P5_hue = 0;
byte P5_inc = 40;
byte P5_treshold = 120;

void patroon5() {
  if (patternInit == 1) {
    col0 = CRGB(255, 0, 0);
    col1 = CRGB(0, 255, 0);
    for (byte i = 0; i < NUM_LEDS; i++) {
      mem[i][0] = 0;
    }
    P5_fadeGoal = 0;
  }

    if (P5_fadeComplete) {
      P5_fadeGoal = 255 - P5_fadeGoal;
      byte rnd = random(0, NUM_LEDS);
      P5_hue += random(50, 200);

      if (P5_fadeGoal == 0) {
        mem[rnd][0] = 254;
        col0 = CHSV(P5_hue, 255, 255);
      }
      if (P5_fadeGoal == 255) {
        mem[rnd][0] = 1;
        col1 = CHSV(P5_hue, 255, 255);
      }
    }

    P5_fadeComplete = 1;
    for (byte i = 0; i < NUM_LEDS; i++) {
      if (mem[i][0] != P5_fadeGoal)
        P5_fadeComplete = 0;

      fadeLed(i, col0, col1, mem[i][0]);

      if (mem[i][0] > 0 && (mem[i][0] < 255)) {
        if (mem[i][0] < P5_fadeGoal) {
          mem[i][0] = min(mem[i][0] + P5_inc, 255);

          if (mem[i][0] > P5_treshold) {
            byte n = (i + 1) % NUM_LEDS;
            if (mem[n][0] == 0)
              mem[n][0] = 1;

            n = (NUM_LEDS + i - 1) % NUM_LEDS;
            if (mem[n][0] == 0)
              mem[n][0] = 1;
          }

        }
        if (mem[i][0] > P5_fadeGoal) {
          mem[i][0] = max(mem[i][0] - P5_inc, 0);

          if (mem[i][0] < 255 - P5_treshold) {
            byte n = (i + 1) % NUM_LEDS;
            if (mem[n][0] == 255)
              mem[n][0] = 254;

            n = (NUM_LEDS + i - 1) % NUM_LEDS;
            if (mem[n][0] == 255)
              mem[n][0] = 254;
          }
        }
      }
    }
}

void patroon6() {
  if (patternInit == 1) {
    CRGB randC = CHSV(0, 255, 0);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds0[i] = randC;
      mem[i][0] = 0;
    }
  }

  CRGB fadeC = CHSV(t / 50, 255, 255);

  frameCount++;
  if (frameCount > 3) {
    fadeToBlackBy( leds0, NUM_LEDS, 10);
    for (byte i = 0; i < NUM_LEDS; i++) {
      mem[i][0] = inc(mem[i][0], -5);
    }
    frameCount = 0;
  }

  for (byte i = 0; i < NUM_LEDS; i++) {
    byte value = min(255, max(0, sin8(dir * t / 30 + pos[i][2]) - 242) * 30);
    CRGB spot = CHSV(0, 0, value);

    if (value > 200) {
      leds0[i] = fadeC;
      mem[i][0] = 255;
    }

    leds[i].r = min(255, spot.r + leds0[i].r);
    leds[i].g = min(255, spot.g + leds0[i].g);
    leds[i].b = min(255, spot.b + leds0[i].b);
  }

  //Glitter effect:
  for (byte i = 0; i < 5; i++) {
    byte rnd = random(0, NUM_LEDS);
    byte value0 = max(0, mem[rnd][0] - 150);
    if (value0 < 50)value0 = 0;
    leds[rnd].r = min(255, leds[rnd].r + value0);
    leds[rnd].g = min(255, leds[rnd].g + value0);
    leds[rnd].b = min(255, leds[rnd].b + value0);
  }
}

//Links rechts gespiegeld
void patroon7() {
  //Links
  for (byte i = 10; i < 42; i++) {
    byte sig = t / 100 + sin16(t * 6) / 100 + pos[i][2] * 4;
    byte sig2 = t / 100 / 2 + sin16(t * 6) / 100 / 2 + pos[i][2] * 2 - 30;
    byte sat = 255 - min(255, max(0, sin8(sig) - 204) * 8);
    leds[i] = CHSV(t / 60 + 127 * (sig2 > 127), sat, 255 - sat / 7); //Geinverteerde kleuren
    //leds[i] = CHSV(t / 60, sat*(sig2 > 127), min(255,255-sat + 255*(sig2 > 127)));  //Eén vlak gekleurd, de andere zwart
    //leds[i] = CHSV(t / 60+127*(sig2 > 127),255, 255);
  }
  //Rechtsr
  for (byte i = 42; i < 74; i++) {
    leds[i % 64] = leds[41 - (i - 42)];
  }
}



