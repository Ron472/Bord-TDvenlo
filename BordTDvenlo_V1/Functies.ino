byte inc(int val, int add) {
  return min(max(0, val + add), 255);
}

void fadeLed(byte n, byte a, byte b, byte fade) {
  leds[n].r = map_8(fade, 0, 255, leds[a].r, leds[b].r);
  leds[n].g = map_8(fade, 0, 255, leds[a].g, leds[b].g);
  leds[n].b = map_8(fade, 0, 255, leds[a].b, leds[b].b);
}

void fadeLed(byte n, CRGB a, CRGB b, byte fade) {
  leds[n].r = map_8(fade, 0, 255, a.r, b.r);
  leds[n].g = map_8(fade, 0, 255, a.g, b.g);
  leds[n].b = map_8(fade, 0, 255, a.b, b.b);
}

void fadeLedToWhite(byte n, byte fade) {
  byte value = 150;
  leds[n].r = map_8(fade, 0, 255, leds[n].r, value);
  leds[n].g = map_8(fade, 0, 255, leds[n].g, value);
  leds[n].b = map_8(fade, 0, 255, leds[n].b, value);
}

byte map_8(byte x, byte in_min, byte in_max, byte out_min, byte out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int sign(int x) {
  if (x < 0)
    return -1;
  else
    return 1;
}



