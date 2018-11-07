void patroon8() {
  int sig0 = sin8(t / 25) * 3 - 384 + 128; //Sinusgolf gecentreerd op 128
  byte sig1 = min(255, max(0, sig0))/2;    //Sinusgolf beperken tussen 0 en 255
  byte shift = (cos8(sig1) + 1) / 4;       //Verschuiving van 64 (90 graden)

  //Serial.println("t\t" + String(t) + "\ts0\t" + String(sig0) + "\ts1\t" + String(sig1) + "\ts2\t" + String(sig2) + "\ts3\t" + String(sig3));
  for (byte i = 0; i < NUM_LEDS; i++) {
    byte section = (pos[i][3] + shift) / 64 % 2;
    CRGB c = CHSV(section * 127 + t / 60, 255, 255);

    
    byte deltaMax = 25;
    int delta = 0;
    if (leds[i].r != c.r) {
      delta = min(deltaMax, max(-deltaMax, c.r - leds[i].r));
      leds[i].r = inc(leds[i].r, delta);
    }
    if (leds[i].g != c.g) {
      delta = min(deltaMax, max(-deltaMax, c.g - leds[i].g));
      leds[i].g = inc(leds[i].g, delta);
    }
    if (leds[i].b != c.b) {
      delta = min(deltaMax, max(-deltaMax, c.b - leds[i].b));
      leds[i].b = inc(leds[i].b, delta);
    }
  }
}


