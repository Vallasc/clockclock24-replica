#include <Arduino.h>
#include <Wire.h>
#include <TimeLib.h>

#include "i2c.h"
#include "clock_state.h"
#include "clock_manager.h"
#include "digit.h"
#include "wifi_utils.h"
#include "web_server.h"
#include "clock_config.h"
#include "ntp.h"

const t_full_clock d_stop = {digit_null, digit_null, digit_null, digit_null};

int last_hour = -1;
int last_minute = -1;
bool is_stopped = false;

// Interfaccia che replica 

void stop()
{
  if(!is_stopped)
  {
    is_stopped = true;
    last_hour = -1;
    last_minute = -1;
    set_clock(d_stop);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("\nclockclock24 replica by Vallasc master v1.0");
  delay(3000);
  begin_config();

  Wire.begin();
  pinMode(LED_BUILTIN, OUTPUT);
  set_mode(LAZY);

  if(get_connection_mode() == HOTSPOT)
    wifi_create_AP();
  else
  {
    if( !wifi_connect(get_ssid(), get_password()) ){
      set_connection_mode(HOTSPOT);
      wifi_create_AP();
    }
  }
  server_start();

  begin_NTP();
  setSyncProvider(get_NTP_time);
  setSyncInterval(60 * 30);
}

void loop() {

  if(get_connection_mode() == HOTSPOT && is_time_changed_browser())
  {
    t_browser_time browser_time = get_browser_time();
    setTime(browser_time.hour, 
      browser_time.minute, 
      browser_time.second, 
      browser_time.day, 
      browser_time.month,  
      browser_time.year);
  }

  if(get_connection_mode() == EXT_CONN && get_timezone() != get_ntp_timezone())
  {
    set_ntp_timezone(get_timezone());
    setSyncProvider(get_NTP_time);
  }

  switch(get_clock_mode())
  {
    case LAZY:
    case FUN:
      {
        int day_week = (weekday() + 5) % 7;
        if(get_sleep_time(day_week, hour()))
          stop();
        else if(hour() != last_hour || minute() != last_minute)
        {
          is_stopped = false;
          last_hour = hour();
          last_minute = minute();
          digitalWrite(LED_BUILTIN, LOW);
          set_clock_time(last_hour, last_minute);
          digitalWrite(LED_BUILTIN, HIGH);
        }
      }
      break;
    case OFF:
      stop();
      break;
  }

  update_MDNS();
  handle_webclient();
}
