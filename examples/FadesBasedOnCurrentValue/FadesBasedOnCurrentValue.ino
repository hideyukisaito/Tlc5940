#include "Tlc5940.h"
#include "tlc_fades.h"

void setup()
{
  Serial.begin(9600);
  Tlc.init();
}

void loop()
{
  if (Serial.available() > 0) {
    if ('a' == Serial.read()) {
      for (int ch = 0; ch < NUM_TLCS * 16; ++ch) {
        int16_t currentValue = tlc_getCurrentValue(ch);
        uint32_t startMillis = millis() + 50;
        uint32_t endMillis = startMillis + 2000;
        if (4095 >= currentValue + 2) currentValue += 2;
        tlc_addFade(ch, currentValue, random(0, 2048), startMillis, endMillis);
      }
    }
  }
  tlc_updateFades();
}
