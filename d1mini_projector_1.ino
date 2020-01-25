#include <cy_serdebug.h>
#include <cy_serial.h>

const char *gc_hostname = "d1mproj1";

#include "cy_wifi.h"
#include "cy_ota.h"
#include "cy_mqtt.h"

#include <Ticker.h>

#include "led_tools.h"
#include "rf_tools.h"

//const char* mqtt_pubtopic = "ATSH28/AUSSEN/WATERLEVEL/1/value";

Ticker senstick;
boolean gv_senstick;


void do_senstick() {
  gv_senstick = true;
}

void setup() {
  cy_serial::start(__FILE__);

  init_led();

  wifi_init(gc_hostname);

  init_ota(gv_clientname);

  init_mqtt(gv_clientname);

  delay(1000);
  check_mqtt();
  delay(1000);


  check_led();

  //send_pub_vals();
  gv_senstick = false;
  senstick.attach(5, do_senstick);
}

void loop()
{

  check_mqtt();

  if (gv_senstick == true) {
    if ( !gv_mqtt_conn_ok ) {
      ESP.restart();
    }

    check_led();


    // send_pub_vals();

    gv_senstick = false;
  }

  check_ota();


  delay(500);

}

// OTA: On Upload switch all LEDs off!!!!!

