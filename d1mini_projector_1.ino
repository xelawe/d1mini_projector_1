#include <cy_serdebug.h>
#include <cy_serial.h>

const char *gc_hostname = "d1mproj1";

#include "cy_wifi.h"
#include "cy_ota.h"
#include "cy_mqtt.h"

#include "led_tools.h"
#include "rf_tools.h"

#include "scheduler.h"

//const char* mqtt_pubtopic = "ATSH28/AUSSEN/WATERLEVEL/1/value";


void setup() {
  cy_serial::start(__FILE__);

  init_led();

  wifi_init(gc_hostname);

  init_ota(gv_clientname);

  init_mqtt(gv_clientname);

  delay(1000);
  check_mqtt();
  delay(1000);

  //send_pub_vals();

  init_sched();
}

void loop()
{

  check_mqtt();

  check_sched();

  check_ota();

  delay(20);

}

// OTA: On Upload switch all LEDs off!!!!!

