#include <cy_serdebug.h>
#include <cy_serial.h>

const char *gc_hostname = "SnowFall";

#include "cy_wifi.h"
#include "cy_ota.h"
#include <Ticker.h>


Ticker TickerLED[8];
int PinLED[] = {15, 13, 12, 14, 4, 5, 2, 16 };


void toggleLED(int iv_LEDnbr) {
  int lv_LEDstat;

  TickerLED[iv_LEDnbr].detach();

  lv_LEDstat = digitalRead(PinLED[iv_LEDnbr]);
  DebugPrint("LED ");
  DebugPrint(iv_LEDnbr);
  DebugPrint(" Pin ");
  DebugPrint(PinLED[iv_LEDnbr]);
  DebugPrint(" Status ");
  DebugPrint(lv_LEDstat);

  if (lv_LEDstat == HIGH) {
    digitalWrite(PinLED[iv_LEDnbr], LOW);
    int lv_timeWait = random(2, 30);
    DebugPrint(" --> 0, ");
    DebugPrint(lv_timeWait);
    TickerLED[iv_LEDnbr].attach( lv_timeWait, toggleLED, iv_LEDnbr);
  } else {
    digitalWrite(PinLED[iv_LEDnbr], HIGH);
    DebugPrint(" --> 1, ");
    DebugPrint(1);
    TickerLED[iv_LEDnbr].attach(1, toggleLED, iv_LEDnbr);
  }
  DebugPrintln(" ");
}

void init_LED() {
  for (int i = 0; i < 8; i++) {
    DebugPrint("LED ");
    DebugPrintln(i);
    pinMode(PinLED[i], OUTPUT);
    toggleLED(i);
    delay(50);
  }
}

void setup() {
  cy_serial::start(__FILE__);

  wifi_init(gc_hostname);

  init_ota(gv_clientname);

  init_LED();
}

void loop() {
  // put your main code here, to run repeatedly:

  check_ota();

  delay(500);
}
