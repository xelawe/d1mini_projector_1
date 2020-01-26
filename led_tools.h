#include <Ticker.h>

const int PinLED[] = {D1, D2, D5, D6 };
const byte anzLED = 4;
byte gv_act_led;
byte gv_next_led;

byte gv_led_prog;
boolean gv_fade_active;
int gv_act_led_pwm;
Ticker fade_tick;

byte inc_LED( byte iv_LED) {
  byte lv_led = iv_LED;
  lv_led++;
  if (lv_led >= anzLED) {
    lv_led = 0;
  }
  return lv_led;
}

void set_LED(byte LEDnbr, byte state) {
  digitalWrite(PinLED[LEDnbr], state);
  DebugPrint("LED ");
  DebugPrint(LEDnbr);
  DebugPrint(" Pin ");
  DebugPrint(PinLED[LEDnbr]);
  DebugPrint(" Status ");
  DebugPrint(state);
  DebugPrintln(" ");
}

void do_fadetick() {
  gv_act_led_pwm = gv_act_led_pwm - 102;

  if (gv_act_led_pwm <= 0) {
    fade_tick.detach();
    set_LED(gv_act_led, 0);
    gv_act_led = gv_next_led;
    set_LED(gv_act_led, 1);
    gv_fade_active = false;
    return;
  }

  analogWrite(PinLED[gv_act_led], gv_act_led_pwm);
  int lv_next_led_pwm = 1024 - gv_act_led_pwm;
  analogWrite(PinLED[gv_next_led], lv_next_led_pwm);
}


void init_led( ) {
  for (int i = 0; i < anzLED; i++) {
    pinMode(PinLED[i], OUTPUT);
    set_LED(i, 0);
  }
  gv_led_prog = 2;
  gv_fade_active = false;
}

void step_LED( ) {
  set_LED(gv_act_led, 0);
  gv_act_led = inc_LED(gv_act_led);
  set_LED(gv_act_led, 1);
}


int fade_next_LED(int iv_intrvl) {

  if (gv_fade_active) {
    return iv_intrvl;
  }

  gv_fade_active = true;
  int rnd = random(1,4); 
  gv_next_led = gv_act_led;
  for (int i=0; i<rnd;i++){
    gv_next_led = inc_LED(gv_next_led);
  }
  gv_act_led_pwm = 1024;
  fade_tick.attach_ms(100, do_fadetick);
  return random(2, 15);
}

int check_led(int iv_intrvl) {
  switch  (gv_led_prog) {
    case 1:
      step_LED( );
      return iv_intrvl;
      break;
    case 2:
      return fade_next_LED( iv_intrvl );
      break;
  }
}

