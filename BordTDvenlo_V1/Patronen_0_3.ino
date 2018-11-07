//2D array met positie en rotatie van alle leds: {x,y,rotatie1,rotatie2}
byte pos[][4] = {{12, 0, 0, 0}, {24, 0, 4, 3}, {36, 0, 8, 6}, {48, 0, 12, 10}, {60, 0, 16, 13}, {72, 0, 20, 16}, {84, 0, 24, 19}, {96, 0, 28, 22}, {108, 0, 32, 26}, {120, 0, 36, 29}, {132, 0, 40, 32}, {144, 0, 44, 35}, {156, 0, 48, 38}, {168, 0, 52, 42}, {180, 0, 56, 45}, {192, 0, 60, 48}, {204, 0, 64, 51}, {216, 0, 68, 54}, {228, 0, 72, 58}, {240, 0, 76, 61}, {252, 24, 80, 64}, {252, 36, 84, 69}, {252, 48, 88, 75}, {252, 60, 92, 80}, {252, 72, 96, 85}, {252, 84, 100, 91}, {252, 96, 104, 96}, {252, 108, 108, 101}, {252, 120, 112, 107}, {252, 132, 116, 112}, {252, 144, 120, 117}, {252, 156, 124, 123}, {240, 180, 128, 128}, {228, 180, 132, 131}, {216, 180, 136, 134}, {204, 180, 140, 138}, {192, 180, 144, 141}, {180, 180, 148, 144}, {168, 180, 152, 147}, {156, 180, 156, 150}, {144, 180, 160, 154}, {132, 180, 164, 157}, {120, 180, 168, 160}, {108, 180, 172, 163}, {96, 180, 176, 166}, {84, 180, 180, 170}, {72, 180, 184, 173}, {60, 180, 188, 176}, {48, 180, 192, 179}, {36, 180, 196, 182}, {24, 180, 200, 186}, {12, 180, 204, 189}, {0, 156, 208, 192}, {0, 144, 212, 197}, {0, 132, 216, 203}, {0, 120, 220, 208}, {0, 108, 224, 213}, {0, 96, 228, 219}, {0, 84, 232, 224}, {0, 72, 236, 229}, {0, 60, 240, 235}, {0, 48, 244, 240}, {0, 36, 248, 245}, {0, 24, 252, 251}};
//pos[i][0]: X positie van de led gespreid over een bereik van 0 tot 255
//pos[i][1]: Y positie van de led gespreid over een bereik van 0 tot 255
//pos[i][2]: Rotatie gespreid over een bereik van 0 tot 255
//           led 0 : 0
//           led 63: 255
//pos[i][3]: Rotatie waarbij elke zijde gespreid is over een bereik van 0 tot 64 (een kwart rotatie)
//           Zijde 0 (Beneden):   0 t/m  63 
//           Zijde 1 (Links)  :  64 t/m 127
//           Zijde 2 (Boven)  : 128 t/m 191
//           Zijde 3 (Rechts) : 192 t/m 255            


//Algemeen herbruikbaar geheugen voor de patronen's:
byte mem[NUM_LEDS][1];
CRGB leds0[NUM_LEDS];
CRGB col0;
CRGB col1;
int frameCount = 0;

void patroon0() {
  for (int i = 0; i < NUM_LEDS; i++) {
    byte sig = sin16(t * 3) / 128 + pos[i][2];

    byte r = leds[i].r;
    byte g = leds[i].g;
    byte b = leds[i].b;

    byte a = 30;

    if (sig >= 0 && sig < 85) {
      r = inc(r, a);
      g = inc(g, -a);
      b = inc(b, -a);
    } else if (sig >= 85 && sig < 170) {
      r = inc(r, -a);
      g = inc(g, a);
      b = inc(b, -a);
    } else if (sig >= 170) {
      r = inc(r, -a);
      g = inc(g, -a);
      b = inc(b, a);
    }

    leds[i] = CRGB(r, g, b);
  }
}

void patroon1() {
  for (int i = 0; i < NUM_LEDS; i++) {
    byte sig = t / 25 + pos[i][1] * sin(t / 5000.0) / 2 + pos[i][0] * cos(t / 5000.0) / 2;
    byte r = leds[i].r;
    byte g = leds[i].g;
    byte b = leds[i].b;

    byte a = 20;

    if (sig >= 0 && sig < 85) {
      r = inc(r, a);
      g = inc(g, -a);
      b = inc(b, -a);
    } else if (sig >= 85 && sig < 170) {
      r = inc(r, -a);
      g = inc(g, a);
      b = inc(b, -a);
    } else if (sig >= 170) {
      r = inc(r, -a);
      g = inc(g, -a);
      b = inc(b, a);
    }

    leds[i] = CRGB(r, g, b);
  }
}

void patroon2() {
  for (int i = 0; i < NUM_LEDS; i++) {
    byte sig = t / 25 + (pos[i][1] * sin(t / 3000.0) + pos[i][0] * cos(t / 3000.0)) * 3 / 2;
    byte sat = 255 - min(255, max(0, sin8(sig) - 200) * 8);
    leds[i] = CHSV(t / 60, sat, 255 - sat / 4);
  }
}

void patroon3() {
  for (int i = 0; i < NUM_LEDS; i++) {
    byte sig = dir * t / 10 + pos[i][2] * 4;
    byte sig2 = dir * t / 20 + pos[i][2] * 2 - 30;
    byte sat = 255 - min(255, max(0, sin8(sig) - 204) * 8);
    leds[i] = CHSV(t / 60 + 127 * (sig2 > 127), sat, 255 - sat / 5);
  }
}



