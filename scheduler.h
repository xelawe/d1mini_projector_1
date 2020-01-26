#include <Ticker.h>

Ticker tick_sched;
const byte sched_anz = 3;
int sched_cnt[3];
int sched_intrvl[] = {5, 1, 5 };
boolean sched_do[3];


void sched_inc(int iv_schednbr) {
  sched_cnt[iv_schednbr]++;
  if (sched_cnt[iv_schednbr] >= sched_intrvl[iv_schednbr]) {
    sched_cnt[iv_schednbr] = 0;
    sched_do[iv_schednbr] = true;
  }
}

void do_sched_tick() {
  for (int i = 0; i < sched_anz; i++) {
    sched_inc(i);
  }
}

void init_sched() {
  for (int i = 0; i < sched_anz; i++) {
    sched_cnt[i] = 0;
    sched_do[i] = true;
  }
  tick_sched.attach(1, do_sched_tick);
}

void check_sched(){
  
  if (sched_do[0] == true) {
    if ( !gv_mqtt_conn_ok ) {
      ESP.restart();
    }
    sched_do[0] = false;
  }


  if (sched_do[2] == true) {
    sched_intrvl[2] = check_led(sched_intrvl[2]);
    sched_do[2] = false;
  }
  
}
